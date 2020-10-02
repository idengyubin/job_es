#include <iostream>
using namespace std;

#define N 100005

string x, y;

int a[N],b[N],c[N],la,lb,lc;

int main(int argc, char* argv[]) {
    cin >> x >> y;
    la = x.length();
    lb = y.length();

    if(la < lb || la == lb && x < y) {
        swap(x, y); 
        swap(la, lb);
        cout << '-';
    }
    
    lc = la;

    for(int i = 0; i < la; i++) 
        a[la - i] = x[i] - '0';
    for(int i = 0; i < lb; i++)
        b[lb - i] = y[i] - '0';

    for(int i = 1; i <= lc; i++) {
        if(a[i] < b[i]) {
            c[i] = a[i] - b[i] + 10;
            a[i+1]--;
        } else {
            c[i]  = a[i] - b[i];
        }
    }
        
    while(c[lc] == 0 && lc > 1) lc--;

    for(int i = lc; i >= 1; i--)
        cout << c[i];


    return 0;
}
