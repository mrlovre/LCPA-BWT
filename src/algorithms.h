//
// Created by ante on 10/28/16.
//

#ifndef LCPA_BWT_ALGORITHMS_H
#define LCPA_BWT_ALGORITHMS_H

#include "Alphabet.h"
#include "BWTree.h"

#include <iostream>

using namespace std;

using interval = pair<int, int>;
using index_occInS = pair<int, int>;

vector<interval> getIntervals(const Alphabet &a, const BWTree &bwt, interval ij);

string bw_transformation(string S);

vector<int> calculate_lcp(string s);

template<class T> void pretty_print(vector<T> lista) {
    cout << "[" << lista[0];
    for (auto i = 1u; i < lista.size(); i++) {
        cout << "," << lista[i];
    }
    cout << "]" << endl;
}

#endif //LCPA_BWT_ALGORITHMS_H
