/*
 * Alphabet.h
 *
 *  Created on: Oct 30, 2016
 *      Author: frka
 */

#ifndef SRC_ALPHABET_H_
#define SRC_ALPHABET_H_

#include <vector>
#include <map>

using namespace std;

using bitvector = vector<bool>;

class Alphabet {
 public:
    Alphabet(const string&, int = 0);
    Alphabet(Alphabet&&);
    int operator[](char) const;
    char operator[](int) const;
    int length() const;
    operator const string() const;
 private:
    map<char, int> charToInt_;
    map<int, char> intToChar_;
    const int length_;
    string sorted_alphabet_;
};

string show_bitvector(bitvector);

#endif /* SRC_ALPHABET_H_ */
