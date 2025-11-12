/**
 * @Time : 2024/7/3-9:35 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1399C 暴力枚举
 */
 /*
  * 枚举可能的队伍和
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
typedef long long ll;
int T, n, nums[N];

int cal(int s) {
    int cnt = 0;
    unordered_map<int, int> map;
    for(int i = 1; i <= n; i++) {
        if(map[s - nums[i]] > 0) cnt++, map[s - nums[i]]--;
        else map[nums[i]]++;
    }
    return cnt;
}

void solve() {
    int ans = 0;
    for(int s = 2; s <= 100; s++)
        ans = max(ans, cal(s));
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        solve();
    }
};