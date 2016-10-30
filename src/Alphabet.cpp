/*
 * Alphabet.cpp
 *
 *  Created on: Oct 30, 2016
 *      Author: frka
 */

#include "Alphabet.h"

#include <map>
#include <utility>
#include <algorithm>

Alphabet::Alphabet(const string &s) {
	auto ms = string(s);
	sort(ms.begin(), ms.end());
	auto i = 0;
	for (const auto &c : ms) {
		charToInt.insert(make_pair(c, i));
		intToChar.insert(make_pair(i, c));
		i++;
	}
}

int Alphabet::operator[](const char &c) {
	auto it = charToInt.find(c);
	if (it == charToInt.end()) {
		return -1;
	} else {
		return it->second;
	}
}

char Alphabet::operator[](const int &i) {
	auto it = intToChar.find(i);
	if (it == intToChar.end()) {
		return '\0';
	} else {
		return it->second;
	}
}
