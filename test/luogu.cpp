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
typedef long double ld;
const int N = 505, mod = 1e9 + 7;
ll T, n, nums[N];

int init = []() -> int {
    for(int i = 2; i < N; i++)
        nums[i] = i * (i - 1) / 2;
    return 0;
}();

void solve() {
    vector<vector<int>> points;
    int layer = 0, x = 0;
    while(n > 0) {
        int idx = upper_bound(nums, nums + 500, n) - nums - 1;
        int cnt = nums[idx];
        n -= cnt;
        for(int i = 0; i < idx; i++)
            points.push_back({layer, x++});
        layer++;
    }
    cout << points.size() << "\n";
    for(auto& p : points)
        cout << p[0] << " " << p[1] << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        solve();
    }
}