#include <iostream>
#include "Alphabet.h"
#include "algorithms.h"
#include "BWTree.h"

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
    string s = "nle_pl$nnlleee_eaae";
    Alphabet a(s, true);
    BWTree bwt(s, a);
    cout << bwt.show() << endl;
    cout << "Symbols count:" << endl;
    for (auto const c : (string) a) {
        cout << c << " " << bwt.get_symbol_count(c) << endl;
    }
}

void test3() {
    Alphabet a("alenp_$");
    BWTree bwt("nle_pl$nnlleee_eaae", a);

    interval ij(1, 19);
    std::vector<interval> lista = getIntervals(a, bwt, ij);
    for (auto i = 0u; i < lista.size(); i++) {
        std::cout << "[" << lista[i].first << " .. " << lista[i].second << "]" << std::endl;
    }
}

int main() {
    test3();
    return 0;
}
