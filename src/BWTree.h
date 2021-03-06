/*
 * Bwt.h
 *
 *  Created on: Oct 30, 2016
 *      Author: frka
 */

#ifndef SRC_BWTREE_H
#define SRC_BWTREE_H

using namespace std;

#include <vector>
#include <unordered_map>

#include "Alphabet.h"

class BWTree {
 public:
    BWTree(const string&, const Alphabet&);
    string show() const;
    int get_symbol_count(char) const;
    const bitvector &get_bitvector_for_index(int) const;
    int rank_func(int, int, int) const;
 private:
    const Alphabet &alphabet_;
    vector<bitvector> array_;
    vector<vector<int>> cumulative_sum_array_;
    unordered_map<char, int> symbol_occurrences_;
};

#endif
