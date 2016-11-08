//
// Created by ante on 10/28/16.
//
#include "algorithms.h"
#include <iostream>
#include <bits/stl_queue.h>

/**
 * Function for initialize interval defined with [start, end].
 * @param start: int that represent index of start interval. (included)
 * @param end: int that represent index of end interval. (excluded)
 * @return: interval defined with [start, end>
 * */
interval setInterval(int start, int end) {
    interval in(start, end);
    return in;
}


/**
 * Function compute number of occurrences letters smaller than 'c' from alphabet defined at 'bigSigma'.
 * @param c: letter for searching number of all occurrances letters that are before 'c' in ordered alphaber 'bigSigma'
 * @return: int that represent number of occurrances
 * */
int computeNumberOfOccurrencesLetterSmallerThenC(Alphabet &a, Bwt &bwt, char c) {
    int index = a[c]; // index of char c
    int sum = 0;
    for (int i = 0; i < index; ++i)
        sum += bwt.get_symbol_count(a[i]); //number of occurrences letter bigSigma[i] in string S
    return sum;
}

/**
 * Fucntion that crete bitvector of string defined in current node of the tree. Last two params are references on
 * left and right substring that we set as string of left and right child node.
 * @param bwt: represent bwt of current node that we want to split on 2 sides, left (i.e. bitvect == 0) and right
 * (i.e. bitvect(i) == 1).
 * @param l: start index from which we start to crete bitVector (included)
 * @param m: end index till which we create bitvector (included)
 * @return bitvector of current bwt.
 * */
std::vector<bool> createBitVector(std::vector<char> &bwt, int l, int m) {
    std::vector<bool> bitVec(bwt.size());
    for (unsigned long i = 0, len = bwt.size(); i < len; ++i) {
        int index = 0;//lut[c].first;
        if (l <= index && m >= index) {
            bitVec[i] = 0;
        } else {
            bitVec[i] = 1;
        }
    }
    return bitVec;
}

/**
 * Function return number of occurrances bool value 'identity' in 'bitVec' in interval [start, end>.
 * @param identity: bool that represent value that we count in bitVector. It can be false(0) or true(1).
 * @param bitVec: indicator vector that tell us whatever char c goes in left or right subtree
 * @return: value that represents number of 'identity' value in bitVector
 * */
int rankFun(bool identity, std::vector<bool> &bitVec, int start, int end) {
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
void getIntervalsRec(Alphabet &a, Bwt &bwt, int indexOfNode, interval &ij, interval &lr, std::vector<interval> &list) {
    if (lr.first == lr.second) {
        char c = a[lr.first];
        int Cc = computeNumberOfOccurrencesLetterSmallerThenC(a, bwt, c);
        list.push_back(setInterval(Cc + ij.first, Cc + ij.second));
    } else {
        int m = (lr.first + lr.second) / 2;

        bitvector bitVec = bwt.get_bitvector_for_index(indexOfNode);

        int a0 = rankFun(0, bitVec, 0, ij.first - 1);
        int b0 = a0 + rankFun(0, bitVec, ij.first - 1, ij.second);

        int a1 = ij.first - 1 - a0;
        int b1 = ij.second - b0;

        if (b0 > a0) {
            interval int1 = setInterval(a0 + 1, b0);
            interval int2 = setInterval(lr.first, m);
            getIntervalsRec(a, bwt, indexOfNode * 2, int1, int2, list);
        }
        if (b1 > a1) {
            interval int1 = setInterval(a1 + 1, b1);
            interval int2 = setInterval(m + 1, lr.second);
            getIntervalsRec(a, bwt, indexOfNode * 2 + 1, int1, int2, list);
        }
    }
}

/**
 * Function that accept interval ij as argument and retunr all c-omega intervals.
 * @param ij: interval form which we want to get all c-omega subintervals
 * @return: all c-omega intervals
 * */
std::vector<interval> getIntervals(Alphabet &a, Bwt &bwt, interval ij) {
    std::vector<interval> list;
    interval alp = setInterval(0, a.length());

    // func that compute all subinterval
    getIntervalsRec(a, bwt, 1, ij, alp, list);
    return list;
}

vector<int> calculate_lcp(string s) {
    Alphabet a(s);
    Bwt bwt(s, a);
    auto n = s.length();
    vector<interval> list;
    const int bottom = -2;
    vector<int> lcp(n + 1, bottom);
    lcp[0] = -1;
    lcp[n] = -1;
    queue<pair<interval, int>> q;
    q.push(make_pair(make_pair(1, n), 0));
    for (; !q.empty(); q.pop()) {
        auto dq = q.front();
        list = getIntervals(a, bwt, dq.first);
        for (auto i : list) {
            if (lcp[i.second + 1] == bottom) {
                q.push(make_pair(i, dq.second + 1));
                lcp[i.second + 1] = dq.second;
            }
        }
    }
}