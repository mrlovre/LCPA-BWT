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

class Alphabet {
private:
	map<char, int> charToInt = map<char, int>();
	map<int, char> intToChar = map<int, char>();
public:
	Alphabet(const string&);
	int operator[](const char &);
	char operator[](const int &);
};

#endif /* SRC_ALPHABET_H_ */
