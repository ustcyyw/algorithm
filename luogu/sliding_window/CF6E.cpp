/**
 * @Time : 2025/1/22-11:41 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF6E 1900 二分答案 滑动窗口
 */
 /*
  * 子数组越长 元素差就越可能超过k
  * 二分子数组长度找到最长长度使得存在子数组的元素差 <= k
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e5 + 5, mod = 998244353;
int T, n, k, nums[N];

vector<int> check(int mid, int flag) {
    vector<int> ans;
    multiset<int> st;
    for(int i = 1, j = 1; j <= n; j++) {
        st.insert(nums[j]);
        if(j - i + 1 > mid)
            st.erase(st.find(nums[i++]));
        if(j - i + 1 == mid && *st.rbegin() - *st.begin() <= k)
            ans.push_back(i);
        if(!ans.empty() && !flag) return ans;
    }
    return ans;
}

void solve() {
    int lo = 1, hi = n;
    while(lo < hi) {
        int mid = (lo + hi + 1) >> 1;
        if(check(mid, 0).size()) lo = mid;
        else hi = mid - 1;
    }
    vector<int> arr = check(lo, 1);
    cout << lo << " " << arr.size() << "\n";
    for(int i : arr)
        cout << i << " " << i + lo - 1 << "\n";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> n >> k;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        solve();
    }
};