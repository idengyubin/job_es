#include <iostream>
#include <cstring>
using namespace std;

#define N 100005

int a[N], b[N], c[N], lc, n;

int main(int argc, char* argv[]) {
    cin >> n;
    a[1] = 1;
    b[1] = 2;
    lc = 1;

    for(int i = 3; i <= n; i++) {
        memset(c, 0, sizeof(c)); 
        for(int j = 1; j <= lc; j++) {
            c[j]  += a[j] + b[j];
            c[j+1] += c[j] / 10;
            c[j] %= 10;
        }

        if(c[lc+1] > 0) lc++;

        for(int j = 1 ; j <= lc; j++)
            a[j] = b[j];

        for(int j = 1; j <= lc; j++)
            b[j] = c[j];

    }

    for(int i = lc; i >= 1; i--)
        cout << c[i];
    
    return 0;
}
