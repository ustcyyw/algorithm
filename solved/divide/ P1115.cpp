/**
 * @Time : 2024/9/10-9:49 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : P1115 分治算法
 */
#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
int n, nums[N];

int dfs(int l, int r) {
    if(l == r) return nums[l];
    int mid = (l + r) >> 1;
    int t1 = dfs(l, mid), t2 = dfs(mid + 1, r);
    int s1 = INT_MIN, s2 = INT_MIN;
    for(int i = mid, temp = 0; i >= l; i--) {
        temp += nums[i];
        s1 = max(s1, temp);
    }
    for(int i = mid + 1, temp = 0; i <= r; i++) {
        temp += nums[i];
        s2 = max(s2, temp);
    }
    return max({t1, t2, s1 + s2});
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> nums[i];
    cout << dfs(1, n);
};