/**
 * @Time : 2024/9/26-9:07 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1883E 贪心 + 数学
 */
 /*
  * 贪心是显然的 重点是怎么在不溢出的情况下计算 可以存储每个数需要乘2的次数
  * 然后根据两个数本身的倍数关系及前一个数乘了多少次2来确定当前数需要乘多少次2
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n, nums[N];
vector<int> pows;
int init = []() -> int {
    for(int i = 0, a = 1; i < 32; i++) {
        pows.push_back(a);
        a *= 2;
    }
    return 0;
}();
// 计算1要乘多少次2才能 >= num
int mul_cnt(int num) {
    return lower_bound(pows.begin(), pows.end(), num) - pows.begin();
}
// 计算num2是num1的几倍
int cal(int num1, int num2) {
    if(num1 > num2) swap(num2, num1);
    return num2 % num1 == 0 ? num2 / num1 : num2 / num1 + 1;
}

void solve() {
    ll ans = 0, pre = 0; // pre记录上一个数乘了多少个2
    for(int i = 2; i <= n; i++) {
        int num = cal(nums[i - 1], nums[i]);
        int cnt = mul_cnt(num);
        if(nums[i] >= nums[i - 1]) {
            if(nums[i - 1] * pows[cnt] > nums[i]) cnt--;
            pre = max(pre - cnt, 0ll);
        }
        else pre = pre + cnt;
        ans += pre;
    }
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