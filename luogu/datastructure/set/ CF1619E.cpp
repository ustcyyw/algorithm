/**
 * @Time : 2024/7/24-12:57 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1619E set + 贪心
 */
 /*
  * mex = 0 要将所有0都干掉
  * mex = 1 0可以保留 所有1都干掉
  * mex = 2 0和1可以保留 而且必须要有 2得干掉
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, cnt[N];

void solve() {
    multiset<int> set;
    ll sum = 0;
    for(int i = 0, flag = 0; i <= n; i++) {
        if(flag) {
            cout << "-1 ";
            continue;
        }
        cout << sum + cnt[i] << " ";
        if(cnt[i] > 0) {
            for(int j = 0; j < cnt[i] - 1; j++)
                set.insert(i);
        } else {
            if(set.empty()) flag = 1;
            else {
                auto it = --set.upper_bound(i);
                sum += i - *it;
                set.erase(it);
            }
        }
    }
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        fill(cnt, cnt + n + 1, 0);
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            cnt[num]++;
        }
        solve();
    }
};