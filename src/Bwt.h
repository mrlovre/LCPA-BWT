/*
 * Bwt.h
 *
 *  Created on: Oct 30, 2016
 *      Author: frka
 */

#ifndef SRC_BWT_H
#define SRC_BWT_H

using namespace std;

#include <vector>

#include "Alphabet.h"

class Bwt {
 public:
    Bwt(const string&, const Alphabet&);
    string show();

    int get_symbol_count(char);
 private:
    const Alphabet &alphabet_;
    vector<bitvector> array_;
    map<char, int> symbol_occurrences_;
};

#endif //SRC_BWT_H
