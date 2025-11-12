/**
 * @Time : 2024/9/5-10:45 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1833D 贪心 暴力枚举
 */
 /*
  * 最大值在最前面的情况 不管如何操作一次 最大值都不会在开头
那只能考虑次大值放在开头的情况
最大值不在最前面 要通过一次操作将最大值放在开头
因此假设要放在最前面的值的索引是idx
所以要翻转的区间 r = [idx - 1]
另外特殊地 如果目标值idx = n - 1
可以将[idx,idx]翻转 然后将[1, idx-1]放置在末尾
  */
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, nums[N];
// 由于至少操作一次 如果最大值在开头 就没法将最大值放到开头 那只能将次大值放在开头
int find(int val) {
    for(int i = 0; i < n; i++)
        if(nums[i] == val) return i;
    return -1;
}

// 翻转[l,r], [0,l-1]和[r+1,n-1]交换
vector<int> format(int l, int r) {
    vector<int> ans;
    for(int i = r + 1; i < n; i++)
        ans.push_back(nums[i]);
    for(int i = r; i >= l; i--)
        ans.push_back(nums[i]);
    for(int i = 0; i < l; i++)
        ans.push_back(nums[i]);
    return ans;
}

void solve() {
    if(n == 1) {
        cout << 1;
        return;
    }
    int idx = find(n);
    if(idx == 0) idx = find(n - 1);
    vector<int> ans(n, -1);
    for(int l = 0; l < idx; l++) {
        vector<int> temp = format(l, idx - 1);
        if(temp > ans) ans = temp;
    }
    if(idx == n - 1) {
        vector<int> temp = format(idx, idx);
        if(temp > ans) ans = temp;
    }
    for(int num : ans)
        cout << num << " ";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        for(int i = 0; i < n; i++)
            cin >> nums[i];
        solve();
        cout << "\n";
    }
};