/*
 * Bwt.h
 *
 *  Created on: Oct 30, 2016
 *      Author: frka
 */

#ifndef SRC_BWT_H
#define SRC_BWT_H

using namespace std;

#include "Alphabet.h"

class Bwt {
private:
	const Alphabet& alphabet;
public:
	Bwt(const string&, Alphabet&);
};

#endif //SRC_BWT_H
