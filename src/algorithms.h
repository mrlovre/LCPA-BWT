//
// Created by ante on 10/28/16.
//

#ifndef LCPA_BWT_ALGORITHMS_H
#define LCPA_BWT_ALGORITHMS_H

#include "Alphabet.h"
#include "BWTree.h"

using interval = std::pair<int, int>;
using index_occInS = std::pair<int, int>;

std::vector<interval> getIntervals(Alphabet &a, BWTree &bwt, interval ij);

std::string bw_transformation(std::string S);

std::vector<int> calculate_lcp(std::string s);

#endif //LCPA_BWT_ALGORITHMS_H
