//
// Created by ante on 10/28/16.
//
#include "algorithms.h"
#include <map>
#include <iostream>

/**
 * sigma is size of alphabet
 */
int sigma = 10;
/**
 * bigSigma is ordered alphabet (list/ordered set)
 */
std::vector<char> bigSigma;
/**
 * lut table with pair char => index of char in bigSigma, number of occurrences characters in S which are < c
 * */
std::map<char, index_occInS> lut;
/**
 * BWT
 */
std::vector<char> BWT;

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
int computeNumberOfOccurrencesLetterSmallerThenC(char c) {
    int index = lut[c].first; // index of char c
    int sum = 0;
    for (int i = 0; i < index; ++i)
        sum += lut[bigSigma[i]].second; //number of occurrences letter bigSigma[i] in string S
    return sum;
}

/**
 * Fucntion that crete bitvector of string defined in current node of the tree. Last two params are references on
 * left and right substring that we set as string of left and right child node.
 * @param bwt: represent bwt of current node that we want to split on 2 sides, left (i.e. bitvect == 0) and right
 * (i.e. bitvect(i) == 1).
 * @param l: start index from which we start to crete bitVector (included)
 * @param m: end index till which we create bitvector (included)
 * @param bwtl: left substring of current bwt ( all characters that have bitvect(i) == 0 goes in this)
 * @param bwtr: right substring of current bwt ( all characters that have bitvect(i) == 1 goes in this)
 * @return bitvector of current bwt.
 * */
std::vector<bool>
createBitVector(std::vector<char> &bwt, int l, int m, std::vector<char> &bwtl, std::vector<char> &bwtr) {
    std::vector<bool> bitVec(bwt.size());
    for (unsigned long i = 0, len = bwt.size(); i < len; ++i) {
        char c = bwt[i];
        int index = lut[c].first;
        if (l <= index && m >= index) {
            bwtl.push_back(c);
            bitVec[i] = 0;
        } else {
            bwtr.push_back(c);
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
void getIntervalsRec(std::vector<char> &bwt, interval &ij, interval &lr, std::vector<interval> &list) {
    if (lr.first == lr.second) {
        char c = bigSigma[lr.first];
        int Cc = computeNumberOfOccurrencesLetterSmallerThenC(c);
        list.push_back(setInterval(Cc + ij.first, Cc + ij.second));
    } else {
        int m = (lr.first + lr.second) / 2;

        std::vector<char> bwtl, bwtr;
        std::vector<bool> bitVec = createBitVector(bwt, lr.first, m, bwtl, bwtr);

        int a0 = rankFun(0, bitVec, 0, ij.first - 1);
        int b0 = a0 + rankFun(0, bitVec, ij.first - 1, ij.second);

        int a1 = ij.first - 1 - a0;
        int b1 = ij.second - b0;

        if (b0 > a0) {
            interval int1 = setInterval(a0 + 1, b0);
            interval int2 = setInterval(lr.first, m);
            getIntervalsRec(bwtl, int1, int2, list);
        }
        if (b1 > a1) {
            interval int1 = setInterval(a1 + 1, b1);
            interval int2 = setInterval(m + 1, lr.second);
            getIntervalsRec(bwtr, int1, int2, list);
        }
    }
}

/**
 * Function that accept interval ij as argument and retunr all c-omega intervals.
 * @param ij: interval form which we want to get all c-omega subintervals
 * @return: all c-omega intervals
 * */
std::vector<interval> getIntervals(interval ij) {
    std::vector<interval> list;
    interval alphabet = setInterval(0, sigma);

    // func that compute all subinterval
    getIntervalsRec(BWT, ij, alphabet, list);
    return list;
}

int main2() {

    sigma = 7;

    bigSigma.push_back('$');
    bigSigma.push_back('_');
    bigSigma.push_back('a');
    bigSigma.push_back('e');
    bigSigma.push_back('l');
    bigSigma.push_back('n');
    bigSigma.push_back('p');

    lut['$'] = index_occInS{0, 1};
    lut['_'] = index_occInS{1, 2};
    lut['a'] = index_occInS{2, 2};
    lut['e'] = index_occInS{3, 6};
    lut['l'] = index_occInS{4, 4};
    lut['n'] = index_occInS{5, 3};
    lut['p'] = index_occInS{6, 1};

    BWT.push_back('n');
    BWT.push_back('l');
    BWT.push_back('e');
    BWT.push_back('_');
    BWT.push_back('p');
    BWT.push_back('l');
    BWT.push_back('$');
    BWT.push_back('n');
    BWT.push_back('n');
    BWT.push_back('l');
    BWT.push_back('l');
    BWT.push_back('e');
    BWT.push_back('e');
    BWT.push_back('e');
    BWT.push_back('_');
    BWT.push_back('e');
    BWT.push_back('a');
    BWT.push_back('a');
    BWT.push_back('e');

    std::vector<interval> lista = getIntervals(setInterval(6, 11));
    for (int i = 0; i < lista.size(); i++)
        std::cout << "[" << lista[i].first << " .. " << lista[i].second << "]" << std::endl;
    return 0;
}
