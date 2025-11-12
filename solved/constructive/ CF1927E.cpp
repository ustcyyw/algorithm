/**
 * @Time : 2024/11/10-2:18 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1927E 构造
 */
 /*
  * 定长子数组和 用滑动窗口来形象思考
  * 相邻的两个子数组只有1个元素不同 就是上一个子数组的头元素和当前子数组的尾元素 这两个元素只能相差1
  * 并且要保证任何子数组的和相差不超过1 那么在窗口滑动的过程中 就不能只是加1 那样子数组和越来越大
  * 必须是+1和-1操作交替 所以在填数的时候某个序列是递增的 其相邻的序列就是递减的
  * 因为窗口滑动一次 两个子数组直接差值变化为1 所以这里子序列的间隔刚好就是窗口的长度
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, M = 4e2;
int T, n, k, nums[N];

void solve() {
    for(int i = 1, lo = 1, hi = n; i <= k; i++) {
        for(int j = i; j <= n; j += k) {
            nums[j] = i % 2 == 1 ? lo++ : hi--;
        }
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> k;
        solve();
        for(int i = 1; i <= n; i++)
            cout << nums[i] << " ";
        cout << "\n";
    }
};