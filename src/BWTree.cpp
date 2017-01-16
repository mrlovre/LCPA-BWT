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
#include <unordered_map>
#include <iostream>

#include "algorithms.h"

using namespace std;

BWTree::BWTree(const string &s, const Alphabet &a)
        : alphabet_(a),
          array_(vector<bitvector>(1 << (int) ceil(log2(a.length())), bitvector())) {
    unordered_map<char, bitvector> symbols_mapping;

    auto const upper_bound = 1 << (int) ceil(log2(a.length()));
    auto const redundancy = upper_bound - a.length();

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

    for (auto const &c : s) {
        symbol_occurrences_[c]++;
        auto mapping = symbols_mapping[c];
        auto index = 1;
        for (auto const b : mapping) {
            array_[index].push_back(b);
            index = 2 * index + b;
        }
    }

    for (auto i = 0u; i < array_.size(); i++) {
        auto const &a = array_[i];
        cumulative_sum_array_.push_back(vector<int>(a.size() + 1, 0));
        auto &c = cumulative_sum_array_[i];
        int prev = 0;

        for (auto j = 0u; j < a.size(); j++) {
            c[j + 1] = prev + (a[j] == 0);
            prev = c[j + 1];
        }
    }

}

const bitvector& BWTree::get_bitvector_for_index(int index) const {
    return (const bitvector &&) array_[index];
}

int BWTree::rank_func(int node_index, int start, int end) const {
    auto const &c = cumulative_sum_array_[node_index];
    return c[end] - c[start];
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
