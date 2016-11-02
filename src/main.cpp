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
    Alphabet a("alenp_$");
    Bwt bwt("nle_pl$nnlleee_eaae", a);
    cout << bwt.show() << endl;
}

int main() {
	test2();
	return 0;
}
