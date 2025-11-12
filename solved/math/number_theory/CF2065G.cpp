/**
 * @Time : 2025/2/13-10:04 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2065G 数学 数论
 */
 /*
  * lcm = a * b / gcd(a, b)

任何一个数有3个及以上的质因子，它和任何一个数的lcm也一定有3个及以上的质因子
这个lcm就无法写成两个质数相乘的形式 因此第一步过滤有3个及以上质因子的数
剩下的数 要么是质数、要么就是两个质数的乘积

1. 两个质数 其lcm就是两个数相乘 所以符合要求
   质数和自身是不满足要求的
2. a 和 num2 = b * c，如果a不是b或者c，那么lcm = a * b * c 不符合要求
   就得满足a是 num2的一个因子
3. num1 = a * b, num2 = c * d, lcm = a * b * c * d / gcd(a * b, c * d)
    3.1 四个因子都不同 lcm = a * b * c * d 不符合要求
    3.2 有一个因子相同 设 num1 = a * b, num2 = a * c
    lcm = a * a * b * c / gcd(a * b, a * c) = a * b * c 不符合要求
    3.3 因此得有2个因子相同 num1 = a * b, num2 = a * b, lcm = a * b 满足
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n, nums[N];

vector<int> prime, isPrime;
int init = []() {
    isPrime.assign(N + 1, 1);
    for (int i = 2; i <= N; ++i) {
        if (isPrime[i] == 1) prime.push_back(i);
        for (int j = 0; j < prime.size() && i * prime[j] <= N; ++j) {
            isPrime[i * prime[j]] = 0;
            if (i % prime[j] == 0)
                break;
        }
    }
    return 0;
}();

vector<int> get_factors(int num) {
    vector<int> ans;
    for(int i = 0; i < prime.size() && num > 1; i++) {
        if(isPrime[num]) ans.push_back(num), num = 1;
        while (num % prime[i] == 0) ans.push_back(prime[i]), num /= prime[i];
        if(ans.size() > 2) return ans;
    }
    return ans;
}

void solve() {
    ll ans = 0, pc = 0;
    map<int, int> map;
    for(int i = 1; i <= n; i++) {
        int num = nums[i];
        if(isPrime[num]) {
            ans += pc - map[num];
            pc++;
        } else {
            vector<int> factors = get_factors(num);
            if(factors.size() == 2) {
                ans += map[num] + 1;
                ans += map[factors[0]];
                if(factors[1] != factors[0]) ans += map[factors[1]];
            }
        }
        map[num]++;
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    int t = 0;
    while(T--) {
        cin >> n;
        t++;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        sort(nums + 1, nums + n + 1);
        solve();
    }
};