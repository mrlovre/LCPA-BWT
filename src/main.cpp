#include <iostream>
#include "Alphabet.h"
#include "Bwt.h"

using namespace std;

void test1() {
	cout << "Pozdrav, Zuzule!" << endl;
	Alphabet a("GFADBCE$");
	cout << a[2] << endl;
	cout << a[6] << endl;
	cout << a['G'] << endl;
	cout << a['F'] << endl;
	cout << a[-1] << endl;
	cout << a[8] << endl;
	cout << a['M'] << endl;
	string s = "ABBACDGA$";
	Bwt bwt(s, a);
}

int main() {
	test1();
	return 0;
}
