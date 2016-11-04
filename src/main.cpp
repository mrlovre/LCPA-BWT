#include <iostream>
#include "Alphabet.h"
#include "Bwt.h"
#include "algorithms.h"

using namespace std;

void test1() {
	Alphabet a("GFADBCE$");
	cout << a[2] << endl;
	cout << a[6] << endl;
	cout << a['G'] << endl;
	cout << a['F'] << endl;
	cout << a[-1] << endl;
	cout << a[8] << endl;
	cout << a['M'] << endl;
}

void test2() {
    Alphabet a("alenp_$");
    Bwt bwt("nle_pl$nnlleee_eaae", a);
    cout << bwt.show() << endl;
}

void test3() {
    Alphabet a("alenp_$");
    Bwt bwt("nle_pl$nnlleee_eaae", a);

    interval ij(6, 11);
    std::vector<interval> lista = getIntervals(a, bwt, ij);
    for (int i = 0; i < lista.size(); i++)
        std::cout << "[" << lista[i].first << " .. " << lista[i].second << "]" << std::endl;
}

int main() {
    test3();
	return 0;
}
