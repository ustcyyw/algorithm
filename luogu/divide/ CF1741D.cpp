/**
 * @Time : 2024/8/5-3:40 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1741D 分治
 */

#include<bits/stdc++.h>

using namespace std;
const int N = 3e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, m, nums[N];

int dfs(int l, int r) {
    if(l == r) return 0;
    int mid = (l + r) / 2;
    int t1 = dfs(l, mid), t2 = dfs(mid + 1, r);
    if(t1 == -1 || t2 == -1) return -1;
    int cnt = t1 + t2;
    if(abs(nums[l] - nums[mid + 1]) > 1) return -1;
    if(nums[l] > nums[mid + 1]) cnt++, swap(nums[l], nums[mid + 1]);
    nums[l] = (nums[l] + 1) / 2;
    return cnt;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        cout << dfs(1, n) << "\n";
    }
};