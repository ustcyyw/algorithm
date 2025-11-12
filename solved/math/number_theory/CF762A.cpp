/**
 * @Time : 2025/2/20-10:38 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF762A 1400 数学 数论
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e5 + 5;
ll n, k;

ll solve() {
    if(n == 1) return k > 1 ? -1 : 1;
    vector<int> nums;
    for(int i = 1; i <= sqrt(n); i++)
        if(n % i == 0) nums.push_back(i);
    if(k <= nums.size()) return nums[k - 1];
    int total = nums.size() * 2;
    if((ll)sqrt(n) * sqrt(n) == n) {
        total--;
        nums.pop_back();
    }
    if(k > total) return -1;
    if((ll)sqrt(n) * sqrt(n) == n) k--; // 排除平方数的影响 剩下的因子都是成对出现了
    k -= nums.size();
    return n / nums[nums.size() - k];
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    cin >> n >> k;
    cout << solve();
};