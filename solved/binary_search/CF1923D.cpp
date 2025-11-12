/**
 * @Time : 2024/12/4-10:21 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1923D 1800 二分答案 前缀和
 */
 /*
  * 假设i被吃的时间是t，那么一定是左边[i-t,i-1]或者[i+1,i+t]上的某一个将i吃的
  * 具有单调性 时间t内可以吃了i，那么时间t+1内一定可以吃了i，t-1内则不一定 因此可以二分答案
  * 要能吃掉nums[i], 首先要保证区间和 > nums[i]
  * 并且用于吃掉nums[i]的区间内所有的smile能合并，能合并的条件是区间存在不相同的值
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 3e5 + 5, mod = 1e9 + 7;
int T, n, nums[N], lb[N], rb[N];
ll sum[N] = {0};

bool check(int i, int len) {
    int l = max(1, i - len), r = min(i + len, n);
    if(sum[i - 1] - sum[l - 1] > nums[i] && lb[i - 1] > l)
        return true;
    if(sum[r] - sum[i] > nums[i] && rb[i + 1] < r)
        return true;
    return false;
}

int cal(int i) {
    if((i - 1 >= 1 && nums[i - 1] > nums[i]) || (i + 1 <= n && nums[i + 1] > nums[i]))
        return 1;
    int t = max(i - 1, n - i), lo = 1, hi = t + 1;
    while(lo < hi) {
        int mid = (lo + hi) >> 1;
        if(check(i, mid)) hi = mid;
        else lo = mid + 1;
    }
    return lo == t + 1 ? -1 : lo;
}

void solve() {
    for(int i = 1, j; i <= n; i = j) {
        j = i + 1;
        while(j <= n && nums[j] == nums[i]) j++;
        for(int k = i; k <= j - 1; k++)
            lb[k] = i, rb[k] = j - 1; // 记录nums[k]左边、右边最远和哪个元素相同
    }
    for(int i = 1; i <= n; i++)
        cout << cal(i) << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n;
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            sum[i] = sum[i - 1] + nums[i];
        }
        solve();
    };
};