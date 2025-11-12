/**
 * @Time : 2024/5/9-4:50 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1144D 贪心
 */
 /*
  * 相邻元素 通过一次操作一定相等
  * 要让操作次数最少 就让大家都变成众数
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, T = 1e9 + 1;
int n, nums[N], cnt[N] = {0};

void solve() {
    int val = -1, num;
    for(int i = 0; i < N; i++) {
        if(cnt[i] > val)
            val = cnt[i], num = i;
    }
    int idx = -1;
    for(int i = 1; i <= n; i++) {
        if(nums[i] == num) {
            idx = i;
            break;
        }
    }
    cout << n - val << "\n";
    for(int i = idx; i < n; i++) {
        if(num != nums[i + 1])
            cout << (num > nums[i + 1] ? 1 : 2) << " " << i + 1 << " " << i << "\n";
    }
    for(int i = idx; i > 1; i--) {
        if(num != nums[i - 1])
            cout << (num > nums[i - 1] ? 1 : 2) << " " << i - 1 << " " << i << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> nums[i];
        cnt[nums[i]]++;
    }
    solve();
};