/**
 * @Time : 2024/7/4-11:06 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1426D 思维题 前缀和
 */
 /*
  * 要找和为0的子数组 可以使用前缀和
  * s[i1] == s[j] 就说明sum[i1 + 1, j]为0
  * s[i2] == s[j] 就说明sum[i2 + 1, j]为0
  * i1 > i2
  * 如果在j-1这个位置插入一个无穷大的数 就能立马将这两个子数组的和为0进行破坏
  * 而后续数组但凡只要包括了这个插入的无穷大的数 子数组和一定不为0
  * 这就向一堆墙 所以插入后的前缀和重新从j开始计算
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
ll T, n, nums[N];

void solve() {
    set<ll> set;
    set.insert(0);
    int cnt = 0;
    for(ll i = 1, sum = 0; i <= n; i++) {
        sum += nums[i];
        if(set.count(sum)) {
            cnt++;
            sum = nums[i], set.clear(), set.insert(0);
        }
        set.insert(sum);
    }
    cout << cnt;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> nums[i];
    solve();
};