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
 private:
    const Alphabet &alphabet_;
    vector<bitvector> array_;
};

#endif //SRC_BWT_H
