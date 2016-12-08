#include <iostream>
#include "Alphabet.h"
#include "algorithms.h"
#include "divsufsort.h"
#include <string.h>
#include <malloc.h>

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

    std::vector<interval> lista = getIntervals(a, bwt, make_pair(1, 1));
    for (auto i = 0u; i < lista.size(); i++) {
        std::cout << "[" << lista[i].first << " .. " << lista[i].second << "]" << std::endl;
    }
}

void test4() {
    // intput data
    char *Text = (char *) "abracadabra";
    int n = (int) strlen(Text);
    int i, j;

    // allocate
    int *SA = (int *) malloc(n * sizeof(int));

    // sort
    divsufsort((unsigned char *) Text, SA, n, 1);

    // output
    for (i = 0; i < n; ++i) {
        printf("SA[%2d] = %2d: ", i, SA[i]);
        for (j = SA[i]; j < n; ++j) {
            printf("%c", Text[j]);
        }
        printf("$\n");
    }

    // deallocate
    free(SA);
}

void test5() {
    // intput data
    char *S = (char *) "el_anele_lepanelen$";
    int n = (int) strlen(S);

    // allocate
    int *SA = (int *) malloc(n * sizeof(int));

    // sort
    divsufsort((unsigned char *) S, SA, n, 0);

    char *BWTrans = (char *) malloc(n * sizeof(char));

    for (int i = 0, tmp = 0; i < n + 1; ++i) {
        tmp = SA[i];
        BWTrans[i] = tmp == 0 ? '$' : S[tmp - 1];
    }

    // output
    for (int i = 0; i < n; ++i) {
        printf("SA[%2d] = %2d: ", i, SA[i]);
        for (int j = SA[i]; j < n; ++j) {
            printf("%c", S[j]);
        }
        printf("$\n");
    }

    for (int i = 0; i < n; ++i) {
        printf("%c", BWTrans[i]);
    }

    // deallocate
    free(SA);
    free(BWTrans);
}

void test6() {
    // intput data
    string S("el_anele_lepanelen$");
    string BWTrans = bw_transformation(S);

    Alphabet a(string(S), true);
    BWTree bwt(string(BWTrans), a);

    std::vector<interval> lista = getIntervals(a, bwt, make_pair(1, 19));
    for (auto i = 0u; i < lista.size(); i++) {
        std::cout << "[" << lista[i].first << " .. " << lista[i].second << "]" << std::endl;
    }
}

void test7() {
    // intput data
    string S("el_anele_lepanelen$");

    std::vector<int> lista = calculate_lcp(S);
    std::cout << "[";
    for (auto i = 0u; i < lista.size(); i++) {
        std::cout << "  " << lista[i];
    }
    std::cout << "]" << std::endl;
    // deallocate
}

void test8() {
    string S("el_anele_lepanelen$");
    string BWTrans = bw_transformation(S);

    Alphabet a(string(S), true);
    BWTree bwt(string(BWTrans), a);

    std::vector<interval> lista = getIntervals(a, bwt, make_pair(1, 1));
    for (auto i = 0u; i < lista.size(); i++) {
        std::cout << "[" << lista[i].first << " .. " << lista[i].second << "]" << std::endl;
    }
}

void test9() {
    string S("el_anele_lepanelen$");
    string BWTrans = bw_transformation(S);

    Alphabet a(string(S), true);
    BWTree bwt(string(BWTrans), a);

    for (int i = 0; i < 4; ++i) {
        auto &bitVec = bwt.get_bitvector_for_index(2);
        std::cout << show_bitvector(bitVec) << std::endl;
        cout << "T" << endl;
    }
}

int main() {
    test7();
    return 0;
}
