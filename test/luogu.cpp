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
const int N = 2e5 + 5;
ll T, n, k, ans[N];

bool solve() {
    if(n < 63 && pow(2ll, n - 1) < k) return false;
    int lo = 1, hi = n, num = 1;
    while(num <= n) {
        int m = hi - lo + 1; // 表示还有多少个空位没有安排
        if(m >= 63 || pow(2ll, m - 2) >= k)  ans[lo++] = num;
        else {
            ans[hi--] = num;
            k -= pow(2ll, m - 2);
        }
        num++;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cin >> n >> k;
        if(!solve()) cout << -1;
        else {
            for(int i = 1; i <= n; i++)
                cout << ans[i] << " ";
        }
        cout << "\n";
    }
};