/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
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