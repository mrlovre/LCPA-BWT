/*
 * Bwt.cpp
 *
 *  Created on: Oct 30, 2016
 *      Author: frka
 */

#include <vector>
#include <bitset>
#include <algorithm>
#include <cmath>

#include "Bwt.h"
#include "Alphabet.h"

using namespace std;

Bwt::Bwt(const string &s, const Alphabet &a)
        : alphabet_(a),
          array_(vector<bitvector>(1 << (int) ceil(log2(a.length())), bitvector())) {
    map<char, bitvector> symbols_mapping;

    auto const max_length = a.length();
    for (auto const c : (const string) a) {
        auto current_length = max_length;
        auto current_index = a[c];
        do {
            symbols_mapping[c].push_back(current_index >= current_length / 2);
            current_index %= current_length / 2;
            current_length /= 2;
        } while (current_length > 1);
    }

    for (auto const &c : s) {
        auto mapping = symbols_mapping[c];
        auto index = 1;
        for (auto const b : mapping) {
            array_[index].push_back(b);
            index = 2 * index + b;
        }
    }
}

string indent(int index) {
    auto level = (int) floor(log2(index));
    return string(level, '-');
}

string Bwt::show() {
    auto s = string();
    for (auto index = 1; index < array_.size(); index++) {
        s += indent(index) + show_bitvector(array_[index]) + '\n';
    }
    return s;
}
