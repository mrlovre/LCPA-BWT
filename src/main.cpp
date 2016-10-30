#include <iostream>
#include "Alphabet.h"
#include "Bwt.h"

using namespace std;

int main() {
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
	return 0;
}
