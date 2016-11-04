/*
 * Alphabet.cpp
 *
 *  Created on: Oct 30, 2016
 *      Author: frka
 */

#include <map>
#include <algorithm>
#include <set>

#include "Alphabet.h"

Alphabet::Alphabet(const string &s, bool extract_from_string)
        : charToInt_(map<char, int>()),
          intToChar_(map<int, char>()) {
    auto ms = string(s);
    if (extract_from_string) {
        auto charset = set<char>(ms.begin(), ms.end());
        ms = string(charset.begin(), charset.end());
    }
    sorted_alphabet_ = move(ms);
    auto i = 0;
    for (const auto &c : sorted_alphabet_) {
        charToInt_.insert(make_pair(c, i));
        intToChar_.insert(make_pair(i, c));
        i++;
    }
}

int Alphabet::operator[](char c) const {
    auto it = charToInt_.find(c);
    if (it == charToInt_.end()) {
        return -1;
    }
    return it->second;
}

char Alphabet::operator[](int i) const {
    auto it = intToChar_.find(i);
    if (it == intToChar_.end()) {
        return '\0';
    }
    return it->second;
}

int Alphabet::length() const {
    return sorted_alphabet_.length();
}

Alphabet::operator const string() const {
    return sorted_alphabet_;
}

string show_bitvector(bitvector bv) {
    string s;
    for_each(bv.begin(), bv.end(), [&s](const bool &b) {s += '0' + (int)b;});
    return s;
}
