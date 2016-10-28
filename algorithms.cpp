//
// Created by ante on 10/28/16.
//
#include "algorithms.h"

using namespace std;

using interval = int[2];
using index_occInS = int[2];

// sigma is size of alphabet
int sigma = 10;
// bigSigma is ordered alphabet (list/ordered set)
list<char> bigSigma;
// lut table with pair char => index of char in bigSigma, number of occurrences characters in S which are < c
map<char, index_occInS> lut;
// BWT
vector<char> BWT;

interval setInterval(int start, int end) {
    interval in;
    in[0] = start;
    in[1] = end;
    return in;
}


list<auto> getIntervals(interval ij) {
    list<> list;
    interval alphabet = setInterval(1, sigma);

    // func that compute all subinterval
    getIntervalsRec(ij, alphabet, list);
    return list;
}

int computeNumberOfOccurrencesLetterSmallerThenC(char c) {
    int index = lut[c][0]; // index of char c
    int sum = 0;
    for (int i = 0; i < index; ++i) {
        sum += lut[bigSigma[i]][1];
    }
    return sum;
}

bool isBWT_i_inSubAlphabet(char c, int l, int r, int m) {
    bool ret = false;
    if (r - m - 1 > m - l) {
        for (int i = l; i < m; ++i)
            if (bigSigma[i] == c) {
                ret = false;
                break;
            }
        ret = true;
    } else {
        for (int i = m + 1; i < r; ++i)
            if (bigSigma[i] == c) {
                ret = true;
                break;
            }
    }
    return ret;
}

vector<bool> createBitVector(int l, int r, int m) {
    vector<bool> bitVec(r - l);
    for (int i = 0, j = l; j < r; ++i, ++j)
        bitVec[i] = isBWT_i_inSubAlphabet(BWT[j], l, r, m);
    return bitVec;
}

int rank(int identity, vector<bool> &bitVec, int start, int end) {
    int sum = 0;
    for (int i = start; i < end; ++i)
        sum += bitVec[i] == identity ? 1 : 0;
    return sum;
}

void getIntervalsRec(interval &ij, interval &lr, list <interval> &list) {
    if (lr[0] == lr[1]) {
        char c = bigSigma[lr[0]];
        int Cc = computeNumberOfOccurrencesLetterSmallerThenC(c);
        list.push_back(setInterval(Cc + ij[0], Cc + ij[1]));
    } else {
        int m = (lr[0] + lr[1]) / 2;
        vector<bool> bitVec = createBitVector(lr[0], lr[1], m);

        int a0 = rank(0, bitVec, 0, ij[0] - 1);
        int b0 = a0 + rank(0, bitVec, ij[0], ij[1]);

        int a1 = ij[0] - 1 - a0;
        int b1 = ij[1] - b0;

        if (b0 > a0)
            getIntervalsRec(setInterval(a0 + 1, b0), setInterval(lr[0], m), list);
        if (b1 > a1)
            getIntervalsRec(setInterval(a1 + 1, b1), setInterval(m + 1, lr[1]), list);
    }
}