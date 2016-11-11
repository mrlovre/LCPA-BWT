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

#include "Alphabet.h"

class BWTree {
 public:
    BWTree(const string&, const Alphabet&);
    string show() const;
    int get_symbol_count(char) const;
    bitvector &get_bitvector_for_index(int index);
 private:
    const Alphabet &alphabet_;
    vector<bitvector> array_;
    map<char, int> symbol_occurrences_;
};

#endif
