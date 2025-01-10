/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 50000 + 5, mod = 998244353;
int T, n;
// a -> b
bool check(int a, int b) {
    if(a > b) return false;
    for(int i = 29, j = 29; i >= 0; i--, j--) {
        while(i >= 0 && ((1 << i) & b) == 0)
            i--;
        if(i == -1) return true;
        j = min(j, i);
        while(j >= 0 && ((1 << j) & a) == 0)
            j--;
        if(j == -1) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> n;
        for(int i = 1, a, b; i <= n; i++) {
            cin >> a >> b;
            cout << (check(a, b) ? "YES" : "NO") << "\n";
        }
    }
};