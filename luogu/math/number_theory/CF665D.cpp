/**
 * @Time : 2025/2/15-10:10 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF665D 1800 数学 数论 分类讨论
 */
 /*
  * 两个偶数 如果选到一起 其和一定是个大于2的偶数 错误
  * 所以 集合中最多一个偶数
  *
  * 两个奇数 如果其中一个大于1 那么两个奇数的和一定是个大于2的偶数 错误
  * 所以集合中 如果有1个大于1的奇数 就不能再选奇数
  *
  * 1比较特殊 1不存在的情况下 集合最好的方式就是一个奇数 一个偶数（集合元素最多2个）
  * 存在1的情况下
  * 1. 1只有1个 就把它当普通奇数考虑即可
  * 2. 1有2个及以上 那么将所有1都选上 答案至少不会更差 可以再试图找一个偶数看是否相加为质数
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e6 + 5, mod = 1e9 + 7;
int T, n, one = 0;
vector<int> odd, even;

vector<int> prime, isPrime(N, 1);
int init = []() {
    for (int i = 2; i < N; ++i) {
        if (isPrime[i] == 1) prime.push_back(i);
        for (int j = 0; j < prime.size() && i * prime[j] < N; ++j) {
            isPrime[i * prime[j]] = 0;
            if (i % prime[j] == 0)
                break;
        }
    }
    return 0;
}();

void solve() {
    vector<int> ans;
    if(one >= 2) {
        while(one-- > 0)
            ans.push_back(1);
        for(int num : even) {
            if(isPrime[num + 1]) {
                ans.push_back(num);
                break;
            }
        }
    } else {
        for(int num1 : even) {
            for(int num2 : odd) {
                if(isPrime[num1 + num2]) {
                    ans.push_back(num1), ans.push_back(num2);
                    break;
                }
            }
            if(!ans.empty()) break;
        }
        if(ans.empty()) {
            if(!even.empty()) ans.push_back(even[0]);
            else ans.push_back(odd[0]);
        }
    }
    cout << ans.size() << "\n";
    for(int num : ans)
        cout << num << " ";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T--) {
        cin >> n;
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            if(num == 1) one++;
            if(num % 2 == 0) even.push_back(num);
            else odd.push_back(num);
        }
        solve();
    }
};