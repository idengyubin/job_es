#include <cstdio>
#include <iostream>
using namespace std;

int a[100005],b[100005],c[100005],la,lb,lc;
string x,y;
int main(int argc, char* argv[]) {
    cin >> x >> y;
    la = x.length();
    lb = y.length();
    for(int i = 0; i < la; i++)
        a[la - i] = x[i] - '0';
    for(int i = 0; i < lb; i++)
        b[lb - i] = y[i] - '0';

    lc = max(la, lb);

    for(int i = 1; i <= lc; i++) {
        c[i]  += a[i] + b[i];
        c[i+1] = c[i] / 10;
        c[i] = c[i] % 10;
    }

    if(c[lc+1] > 0)
        lc++;
    for(int i = lc; i >= 1; i--)
        cout << c[i];
    cout << endl;
        
}
