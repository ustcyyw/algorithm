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
typedef unsigned long long ull;
const int N = 1e5 + 5, mod = 998244353, M = 31;
int T, n, nums[N];
vector<int> ans;

void check() {
    vector<int> suf(n + 1, -1);
    for(int i = n, j = n; i >= 1; i--) {
        if(nums[i] < nums[j]) j = i;
        suf[i] = j;
    }
    for(int i = 1, j = 1; i < n; i++) {
        if(nums[i] < nums[j]) j = i;
        if(nums[i] > nums[j] && nums[i] > nums[suf[i + 1]]) {
            ans = {j, i, suf[i + 1]};
        }
    }
}

void solve() {
    check();
    if(!ans.empty()) {
        cout << "3\n" << ans[0] << " " << ans[1] << " " << ans[2];
        return;
    }
    for(int i = 1; i <= n; i++)
        nums[i] *= -1;
    check();
    if(!ans.empty())
        cout << "3\n" << ans[0] << " " << ans[1] << " " << ans[2];
    else cout << 0;
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >>nums[i];
        solve();
    }
};