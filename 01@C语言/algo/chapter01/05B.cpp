#include <iostream>
using namespace std;

#define N 100005
int a[N], b[N], c[N], la, lb, lc,n;
string x, y;
int main(int argc, char* argv[]) {
    cin >> n;
    cin >> x >> y;

    la = x.length();
    lb = y.length();

    for(int i = 0; i < la; i++) {
        if(x[i] >= 'A' && x[i] <= 'Z') 
            a[la -i] = x[i] - 'A' + 10;
        else
            a[la -i] = x[i] - '0';
    }

    for(int i = 0; i < lb; i++) {
        if(y[i] >= 'A' && y[i] <= 'Z') 
            b[lb -i] = y[i] - 'A' + 10;
        else
            b[lb - i] = y[i] - '0';
    }

    lc = max(la, lb);

    for(int i = 1; i <= lc; i++) {
        c[i]  += a[i] + b[i];
        c[i+1] += c[i] / n;
        c[i] = c[i] % n;
    }

    if(c[lc+1] > 0) lc++;

    for(int i = lc; i >= 1; i--) {
        if(c[i] >= 10) 
            cout << char(c[i] - 10 + 'A');
        else
            cout << c[i];
    }

    return 0;
}
