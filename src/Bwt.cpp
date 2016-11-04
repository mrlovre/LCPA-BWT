/*
 * Bwt.cpp
 *
 *  Created on: Oct 30, 2016
 *      Author: frka
 */

#include <vector>
#include <bitset>
#include <cmath>

#include "Bwt.h"

using namespace std;

Bwt::Bwt(const string &s, const Alphabet &a)
        : alphabet_(a),
          array_(vector<bitvector>(1 << (int) ceil(log2(a.length())), bitvector())),
          symbol_occurrences_(map<char, int>()) {
    map<char, bitvector> symbols_mapping;

    auto const upper_bound = 1 << (int) ceil(log2(a.length()));
    auto const redundancy = upper_bound - a.length() - 1;
    for (auto const c : (const string) a) {
        auto current_length = upper_bound;
        auto current_index = a[c];
        auto has_redundancy = current_index > upper_bound - 2 * redundancy;
        while (current_length > 1 << has_redundancy) {
            symbols_mapping[c].push_back(current_index >= current_length / 2);
            current_index %= current_length / 2;
            current_length /= 2;
        }
    }

    for (auto const &c : s) {
        symbol_occurrences_[c]++;
        auto mapping = symbols_mapping[c];
        auto index = 1;
        for (auto const b : mapping) {
            array_[index].push_back(b);
            index = 2 * index + b;
        }
    }
}

bitvector &Bwt::get_bitvector_for_index(int index) {
    return array_[index];
}

string indent(int index) {
    auto level = (int) floor(log2(index));
    return string(level, '-');
}

string Bwt::show() const {
    auto s = string();
    for (auto index = 1u; index < array_.size(); index++) {
        s += indent(index) + show_bitvector(array_[index]) + '\n';
    }
    return s;
}

int Bwt::get_symbol_count(char c) const {
    return symbol_occurrences_.at(c);
}
