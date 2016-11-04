#include <iostream>
#include "Alphabet.h"
#include "Bwt.h"

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
    Bwt bwt(s, a);
    cout << bwt.show() << endl;
    cout << "Symbols count:" << endl;
    for (auto const c : (string) a) {
        cout << c << " " << bwt.get_symbol_count(c) << endl;
    }
}

int main() {
	test2();
	return 0;
}
