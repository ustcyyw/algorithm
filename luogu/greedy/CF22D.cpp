/**
 * @Time : 2025/1/27-1:40 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF22D 1900 贪心
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e5 + 5, mod = 998244353;
int T, n;
vector<vector<int>> arr;

void solve() {
    sort(arr.begin(), arr.end(), [](auto& a, auto& b) -> bool {return a[1] < b[1];});
    vector<int> ans;
    for(int i = 0; i < n; ) {
        int x = arr[i][1];
        ans.push_back(x);
        while(i < n && arr[i][0] <= x)
            i++;
    }
    cout << ans.size() << "\n";
    for(int x : ans)
        cout << x << " ";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> n;
        for(int i = 1, l, r; i <= n; i++) {
            cin >> l >> r;
            if(l > r) swap(l, r);
            arr.push_back({l, r});
        }
        solve();
    }
};