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
 * Computes number of occurrences of letters that are lexicographically smaller than given letter,
 * considering the given alphabet.
 * @param a: the alphabet,
 * @patam bwt: binary wavelet tree of the sequence,
 * @param c: letter to compute the number of occurrences of letters that are lexicographically smaller than it for
 * @return: number of occurrences
 * */
int letter_occurences(const Alphabet &a, const BWTree &bwt, char c) {
    int index = a[c];  // index of char c
    int sum = 0;
    for (int i = 0; i < index; ++i)
        sum += bwt.get_symbol_count(a[i]);  //number of occurrences letter bigSigma[i] in string S
    return sum;
}

/**
 * Recursive function that is needed to compute all c-omega intervals.
 * @param bwt: bwt form what we try to get all c-omega intervals
 * @param ij: interval of bwt that we give to function
 * @param lr: interval of subalphabet
 * @param list: list of all c-omega intervals of given bwt
 * */
void get_intervals_rec(const Alphabet &a, const BWTree &bwt, int indexOfNode, interval &ij, interval &lr,
                       vector<interval> &list) {
    if (lr.first == lr.second) {
        char c = a[lr.first];
        int Cc = letter_occurences(a, bwt, c);
        list.push_back(make_pair(Cc + ij.first, Cc + ij.second));
    } else {
        int m = (lr.first + lr.second) / 2;

        int a0 = bwt.rank_func(indexOfNode, 0, ij.first - 1);
        int b0 = a0 + bwt.rank_func(indexOfNode, ij.first - 1, ij.second);

        int a1 = ij.first - 1 - a0;
        int b1 = ij.second - b0;

        if (b0 > a0) {
            interval int1 = make_pair(a0 + 1, b0);
            interval int2 = make_pair(lr.first, m);
            get_intervals_rec(a, bwt, indexOfNode * 2, int1, int2, list);
        }
        if (b1 > a1) {
            interval int1 = make_pair(a1 + 1, b1);
            interval int2 = make_pair(m + 1, lr.second);
            get_intervals_rec(a, bwt, indexOfNode * 2 + 1, int1, int2, list);
        }
    }
}

/**
 * Function that accept interval ij as argument and retunr all c-omega intervals.
 * @param ij: interval form which we want to get all c-omega subintervals
 * @return: all c-omega intervals
 * */
vector<interval> getIntervals(const Alphabet &a, const BWTree &bwt, interval ij) {
    vector<interval> list;
    interval alp = make_pair(0, a.length() - 1);

    // func that computes all subintervals
    get_intervals_rec(a, bwt, 1, ij, alp, list);
    return list;
}

string bw_transformation(string S) {
    string BWTrans = string();
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
    for (; !q.empty(); q.pop()) {
        auto dq = q.front();
        auto list = move(getIntervals(a, bwt, dq.first));
        for (auto interv : list) {
            // NB: interval indices start from 1, but indexing in arrays starts from 0; hence we use interv.second not interv.second+1
            if (lcp[interv.second] == bottom) {
                q.push(make_pair(interv, dq.second + 1));
                lcp[interv.second] = dq.second;
            }
        }
    }
    return lcp;
}
