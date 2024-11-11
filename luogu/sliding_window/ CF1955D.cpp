/**
 * @Time : 2024/4/11-10:42 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N = 2e5 + 5;
int T, n, m, k, a[N];
map<int, int> cntB, cntC;

void solve() {
    int cnt = 0, ans = 0;
    for(int i = 1, j = 1; j <= n; j++) {
        int num1 = a[j];
        cntC[num1]++;
        if(cntC[num1] <= cntB[num1]) cnt++;
        if(j - i + 1 > m) {
            int num2 = a[i++];
            cntC[num2]--;
            if(cntC[num2] < cntB[num2]) cnt--;
        }
        if(j - i + 1 == m && cnt >= k) ans++;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m >> k;
        cntB.clear(), cntC.clear();
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        for(int i = 1, num; i <= m; i++) {
            cin >> num;
            cntB[num]++;
        }
        solve();
    }
};