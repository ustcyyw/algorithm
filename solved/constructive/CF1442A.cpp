/**
 * @Time : 2025/1/13-10:37 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1442A 1800 构造算法
 */
/*
  * nums[i] > nums[i + 1] 那么删右边子数组指望不上
  * 只能选择删左边了 至少得减少到 nums[i + 1]的值 但是不能让左边有任何数 < 0
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e5 + 5, mod = 998244353;
int T, n, nums[N];

bool solve() {
    for(int i = n - 1, reduce = 0; i >= 1; i--) {
        if(nums[i] - reduce < 0) return false;
        nums[i] -= reduce;
        if(nums[i] > nums[i + 1]) {
            reduce += nums[i] - nums[i + 1];
            nums[i] = nums[i + 1];
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while (T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        cout << (solve() ? "YES" : "NO") << "\n";
    }
};