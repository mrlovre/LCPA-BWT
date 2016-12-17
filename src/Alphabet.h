/*
 * Alphabet.h
 *
 *  Created on: Oct 30, 2016
 *      Author: frka
 */

#ifndef SRC_ALPHABET_H_
#define SRC_ALPHABET_H_

#include <vector>
#include <unordered_map>

using namespace std;

using bitvector = vector<char>;

class Alphabet {
 public:
    Alphabet(const string&, bool=false);
    Alphabet(Alphabet&&);
    int operator[](char) const;
    char operator[](int) const;
    int length() const;
    operator const string() const;
 private:
    unordered_map<char, int> charToInt_;
    vector<char> intToChar_;
    string sorted_alphabet_;
};

string show_bitvector(const bitvector&);

#endif /* SRC_ALPHABET_H_ */
