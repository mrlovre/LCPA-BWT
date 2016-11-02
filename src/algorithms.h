//
// Created by ante on 10/28/16.
//

#ifndef LCPA_BWT_ALGORITHMS_H
#define LCPA_BWT_ALGORITHMS_H

#include<vector>

using interval = std::pair<int, int>;
using index_occInS = std::pair<int, int>;

std::vector<interval> getIntervals(interval ij);

#endif //LCPA_BWT_ALGORITHMS_H
