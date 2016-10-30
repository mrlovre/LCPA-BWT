/*
 * Bwt.cpp
 *
 *  Created on: Oct 30, 2016
 *      Author: frka
 */

#include "Bwt.h"
#include "Alphabet.h"

#include <vector>
#include <bitset>

using namespace std;

Bwt::Bwt(const string &s, Alphabet &a) : alphabet(a) {
}
