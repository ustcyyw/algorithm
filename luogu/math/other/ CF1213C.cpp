/**
 * @Time : 2024/5/20-4:29 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1213C 数学
 */
 /*
  * 被某个数整除 这些数的末位数字周期性出现
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 2e5 + 5, D = 1e9;
ll T, n, m, sum, ans;
vector<int> nums;

ll solve() {
    if(n < m) return 0;
    ans = sum = 0;
    for(int i = 1; ; i++) {
        ll t = m * i;
        int last = t % 10;
        if(!nums.empty() && nums[0] == last) break;
        nums.push_back(last);
    }
    sum = accumulate(nums.begin(), nums.end(), 0ll);
    ll base = m * nums.size();
    ans += sum * (n / base);
    for(int i = 0; i < n % base / m; i++)
        ans += nums[i];
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> m;
        nums.clear();
        cout << solve() << "\n";
    }
};