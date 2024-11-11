/**
 * @Time : 2024/7/23-7:57 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1618D 贪心
 */
 /*
  * 肯定用小数 / 大数 这样两个数都消除了
  * 并且应该尽量选择大的数消除
  * 但是存在一个问题 大的数中有很多相同的数的时候 相除还会剩下1
  * 但是要换一个小一些的数吗？不用 因为换小一小的数 至少比当前这个数小1
  * 相除剩下的1 至少不差于将大的数换出去的代价 因此应该把最大的2k个数拿出来安排
  * 具体安排的时候 就是先规避相同的数相除
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 4e4 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, k, nums[N];

void solve() {
    sort(nums + 1, nums + n + 1);
    ll sum = 0;
    int maxCnt = 0;
    unordered_map<int, int> map;
    for(int i = n; i > n - 2 * k; i --) {
        map[nums[i]]++;
        maxCnt = max(maxCnt, map[nums[i]]);
    }
    if(maxCnt > k) sum += maxCnt - k;
    for(int i = 1; i <= n - 2 * k; i++)
        sum += nums[i];
    cout << sum << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> k;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        solve();
    }
};