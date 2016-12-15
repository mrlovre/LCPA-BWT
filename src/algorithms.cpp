//
// Created by ante on 10/28/16.
//
#include "algorithms.h"
#include <iostream>
#include <malloc.h>
#include <queue>
#include "divsufsort.h"

using namespace std;

/**
 * Function compute number of occurrences letters smaller than 'c' from alphabet defined at 'bigSigma'.
 * @param c: letter for searching number of all occurrances letters that are before 'c' in ordered alphaber 'bigSigma'
 * @return: int that represent number of occurrances
 * */
int computeNumberOfOccurrencesLetterSmallerThenC(const Alphabet &a, const BWTree &bwt, char c) {
    int index = a[c];  // index of char c
    int sum = 0;
    for (int i = 0; i < index; ++i)
        sum += bwt.get_symbol_count(a[i]);  //number of occurrences letter bigSigma[i] in string S
    return sum;
}

/**
 * Function return number of occurrances bool value 'identity' in 'bitVec' in interval [start, end>.
 * @param identity: bool that represent value that we count in bitVector. It can be false(0) or true(1).
 * @param bitVec: indicator vector that tell us whatever char c goes in left or right subtree
 * @return: value that represents number of 'identity' value in bitVector
 * */
int rankFun(bool identity, const bitvector &bitVec, int start, int end) {
    int sum = 0;
    for (int i = start; i < end; ++i)
        sum += bitVec[i] == identity ? 1 : 0;
    return sum;
}

/**
 * Recurisve function that we need to compute all c-omega intervals.
 * @param bwt: bwt form what we try to get all c-omega intervals
 * @param ij: interval of bwt that we give to function
 * @param lr: interval of subalphabet
 * @param list: list of all c-omega intervals of given bwt
 * */
void getIntervalsRec(const Alphabet &a, const BWTree &bwt, int indexOfNode, interval &ij, interval &lr,
                     std::vector<interval> &list) {
    if (lr.first == lr.second) {
        char c = a[lr.first];
        int Cc = computeNumberOfOccurrencesLetterSmallerThenC(a, bwt, c);
        list.push_back(make_pair(Cc + ij.first, Cc + ij.second));
    } else {
        int m = (lr.first + lr.second) / 2;

        auto &bitVec = bwt.get_bitvector_for_index(indexOfNode);

        int a0 = rankFun(0, bitVec, 0, ij.first - 1);
        int b0 = a0 + rankFun(0, bitVec, ij.first - 1, ij.second);

        int a1 = ij.first - 1 - a0;
        int b1 = ij.second - b0;

        if (b0 > a0) {
            interval int1 = make_pair(a0 + 1, b0);
            interval int2 = make_pair(lr.first, m);
            getIntervalsRec(a, bwt, indexOfNode * 2, int1, int2, list);
        }
        if (b1 > a1) {
            interval int1 = make_pair(a1 + 1, b1);
            interval int2 = make_pair(m + 1, lr.second);
            getIntervalsRec(a, bwt, indexOfNode * 2 + 1, int1, int2, list);
        }
    }
}

/**
 * Function that accept interval ij as argument and retunr all c-omega intervals.
 * @param ij: interval form which we want to get all c-omega subintervals
 * @return: all c-omega intervals
 * */
std::vector<interval> getIntervals(const Alphabet &a, const BWTree &bwt, interval ij) {
    std::vector<interval> list;
    interval alp = make_pair(0, a.length());

    // func that compute all subinterval
    getIntervalsRec(a, bwt, 1, ij, alp, list);
    return list;
}

std::string bw_transformation(std::string S) {
    std::string BWTrans = std::string();
    auto n = S.length();
    int *SA = (int *) malloc(n * sizeof(int));
    BWTrans.resize(n);

    // sort
    divsufsort((const unsigned char *) S.c_str(), SA, static_cast<int>(S.length()), 0);

    for (auto i = 0u, tmp = 0u; i < n; ++i) {
        tmp = SA[i];
        BWTrans[i] = tmp == 0 ? '$' : S[tmp - 1];
    }
    free(SA);
    return BWTrans;
}

vector<int> calculate_lcp(string s) {
    string BWTrans = bw_transformation(s);
    Alphabet a(s, true);
    BWTree bwt(BWTrans, a);
    auto n = s.length();
    const int bottom = -2;
    vector<int> lcp(n + 1, bottom);
    lcp[0] = lcp[n] = -1;
    queue<pair<interval, int>> q;
    q.push(make_pair(make_pair(1, n), 0));
    cout << "BWTrans:" << endl;
    cout << BWTrans << endl;
    cout << "BWTree:" << endl;
    cout << bwt.show() << endl;
    for (; !q.empty(); q.pop()) {
        auto dq = q.front();
        auto list = (vector<interval> &&) getIntervals(a, bwt, dq.first);
        for (auto interv : list) {
            // NB: interval indices start from 1, but indexing in arrays starts from 0; hence we use interv.second not interv.second+1
            if (lcp[interv.second] == bottom) {
                q.push(make_pair(interv, dq.second + 1));
                lcp[interv.second] = dq.second;
            }
        }
        pretty_print(lcp);
    }
    return lcp;
}
