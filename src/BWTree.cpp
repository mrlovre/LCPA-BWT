/*
 * Bwt.cpp
 *
 *  Created on: Oct 30, 2016
 *      Author: frka
 */

#include "BWTree.h"

#include <vector>
#include <bitset>
#include <cmath>

#include <iostream>

#include "algorithms.h"

using namespace std;

BWTree::BWTree(const string &s, const Alphabet &a)
        : alphabet_(a),
          array_(vector<bitvector>(1 << (int) ceil(log2(a.length())), bitvector())),
          symbol_occurrences_(map<char, int>()) {
    map<char, bitvector> symbols_mapping;

    auto const upper_bound = 1 << (int) ceil(log2(a.length()));
    auto const redundancy = upper_bound - a.length();
//    cout << redundancy << endl;
//    cout << upper_bound << endl;

    for (auto const c : (const string) a) {
        auto current_length = upper_bound;
        auto current_index = a[c];
        auto has_redundancy = current_index >= upper_bound - 2 * redundancy;
        if (has_redundancy) {
            current_index -= (a.length() - redundancy) / 2;
            current_length /= 2;
        }
        while (current_length > 1) {
            symbols_mapping[c].push_back(current_index >= current_length / 2);
            current_index %= current_length / 2;
            current_length /= 2;
        }
    }

//    for (auto c : (const string) a) {
//        cout << c << ": ";
//        pretty_print(symbols_mapping[c]);
//        cout << endl;
//    }

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

const bitvector& BWTree::get_bitvector_for_index(int index) const {
    return (const bitvector &&) array_[index];
}

string indent(int index) {
    auto level = (int) floor(log2(index));
    return string(level, '-');
}

string BWTree::show() const {
    auto s = string();
    for (auto index = 1u; index < array_.size(); index++) {
        s += indent(index) + show_bitvector(array_[index]) + '\n';
    }
    return s;
}

int BWTree::get_symbol_count(char c) const {
    return symbol_occurrences_.at(c);
}
