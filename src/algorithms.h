//
// Created by ante on 10/28/16.
//

#ifndef LCPA_BWT_ALGORITHMS_H
#define LCPA_BWT_ALGORITHMS_H

#include<vector>

using namespace std;

using interval = vector<int>;
using index_occInS = vector<int>;

vector<interval> getIntervals(interval ij);

#endif //LCPA_BWT_ALGORITHMS_H
