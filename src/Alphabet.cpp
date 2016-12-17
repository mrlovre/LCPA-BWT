/*
 * Alphabet.cpp
 *
 *  Created on: Oct 30, 2016
 *      Author: frka
 */

#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <set>

#include "Alphabet.h"

Alphabet::Alphabet(const string &s, bool extract_from_string) {
    auto ms = string(s);
    if (extract_from_string) {
        auto charset = set<char>(ms.begin(), ms.end());
        ms = string(charset.begin(), charset.end());
    }
    sorted_alphabet_ = move(ms);
    sort(sorted_alphabet_.begin(), sorted_alphabet_.end());
    intToChar_.resize(sorted_alphabet_.size());
    auto i = 0;
    for (const auto &c : sorted_alphabet_) {
        charToInt_.insert(make_pair(c, i));
        intToChar_[i] = c;
        i++;
    }
}

int Alphabet::operator[](char c) const {
    return charToInt_.at(c);
}

char Alphabet::operator[](int i) const {
    return intToChar_[i];
}

int Alphabet::length() const {
    return static_cast<int>(sorted_alphabet_.length());
}

Alphabet::operator const string() const {
    return sorted_alphabet_;
}

string show_bitvector(const bitvector &bv) {
    string s;
    for_each(bv.begin(), bv.end(), [&s](const bool &b) {s += '0' + (int)b;});
    return s;
}
