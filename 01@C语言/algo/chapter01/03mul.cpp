#include <iostream>
using namespace std;

#define N 100005

int a[N], b[N], c[N],la, lb, lc;
string x, y;

int main(int argc, char* argv[]) {
    cin >> x >> y;
    la = x.length();
    lb = y.length();

    lc = la + lb;

    for(int i =0; i < la; i++)
        a[la - i] = x[i] - '0';

    for(int i = 0; i < lb; i++)
        b[lb - i] = y[i] - '0';

    for(int i = 1; i <= la; i++) {
        for(int j = 1; j <= lb; j++) {
            c[i + j -1]  += a[i] * b[j];
            c[i + j] += c[i + j -1] / 10;
            c[i + j - 1] = c[i + j -1] % 10;
        }
    }
    while(c[lc] == 0 && lc > 1) lc--;

    for(int i = lc; i >= 1; i--)
        cout << c[i];


    return 0;
}
