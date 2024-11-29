/**
 * @Time : 2024/11/28-12:53 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1995C 1800 数学 贪心
 */
 /*
  * 后一项比前一项大 利用对数函数的性质求解不等式即可
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, l, nums[N];

ll cal(ll c, int a, int b) {
    if(a == 1) return 0;
    long double temp = log2(log2(a)) - log2(log2(b)) + c;
    return max(0ll, (ll)ceil(temp));
}

ll solve() {
    ll ans = 0, pre = 0;
    for(int i = 2; i <= n; i++) {
        if(nums[i] == 1 && nums[i - 1] != 1) return -1;
        pre = cal(pre, nums[i - 1], nums[i]);
        ans += pre;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        cout << solve() << "\n";
    };
};