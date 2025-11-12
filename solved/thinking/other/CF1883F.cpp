/**
 * @Time : 2024/9/25-5:22 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1883F 思维
 */
/*
  * 子数组作为子序列只出现一次
1. 子数组本身就是一个子序列 已经出现了一次了 所以相当于是说 这个序列不能有第二种构造方式
2. 如果子数组的开头元素在前面已经出现过 那么不管结尾元素选哪个
只要将开头的元素替换为前面出现的元素 这个子序列就用第二种方法构造出来了
所以开头元素必须是第一次出现
3. 同理 结尾元素必须是第一次出现
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T, n, m, nums[N], suf[N];

void solve() {
    set<int> st;
    for(int i = n; i >= 1; i--) {
        st.insert(nums[i]);
        suf[i] = st.size();
    }
    ll ans = 0;
    st = {};
    for(int i = 1; i <= n; i++) {
        if(!st.count(nums[i])) ans += suf[i];
        st.insert(nums[i]);
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