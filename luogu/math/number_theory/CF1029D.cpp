/**
 * @Time : 2024/4/22-8:53 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 两个数拼接后的数 num = num1 * d + num2 d就是num2的数位
  * num % k = num1 * d % k + num2 % k
  * num % k = 0
  * 就相当于 num1 * d % k + num2 % k = k 或者 0
  * 因此可以统计num1 * d % k的值（d从1到10）出现了几次
  * 然后枚举num2
  */
#include<bits/stdc++.h>
using namespace std;
typedef __int128 ll;
const int N = 2e5 + 5;
int n, k, nums[N];
ll p[N];
unordered_map<int, int> mps[11];

int init = []() ->int {
    for(ll t = 10, i = 1; i < 11; i++, t *= 10)
        p[i] = t;
    return 0;
}();

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k;
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        nums[i] = num;
        for(ll j = 1, t = 10; j < 11; j++, t *= 10) {
            mps[j][(int)(t * num % k)]++;
        }
    }
    long long ans = 0;
    for(int i = 1; i <= n; i++) {
        int mod = nums[i] % k, d = to_string(nums[i]).size();
        if(mod == 0) ans += mps[d][0];
        else ans += mps[d][k - mod];
        ll t = mod * p[d] % k + mod;
        if(t == k || t == 0) ans--;
    }
    cout << ans;
};