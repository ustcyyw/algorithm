/**
 * @Time : 2024/3/28-9:58 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
int n, nums[N], valid[N];

bool check(int k) {
    memset(valid, 0, sizeof(valid));
    multiset<int> set;
    for(int i = 1; i <= n - k + 1; i++) {
        set.insert(nums[i] - i);
        if(i - k >= 1) set.erase(set.find(nums[i - k] - (i - k)));
        if(i - k >= 0 && *set.begin() >= k - i) valid[i] = 1;
    }
    set.clear();
    for(int i = n; i >= k; i--) {
        set.insert(nums[i] + i);
        if(i + k <= n) set.erase(set.find(nums[i + k] + (i + k)));
        if(i + k <= n + 1 && valid[i] && *set.begin() >= k + i)
            return true;
    }
    return false;
}

void solve() {
    int lo = 1, hi = (n + 1) / 2;
    while(lo < hi) {
        int mid = (lo + hi + 1) >> 1;
        if(check(mid)) lo = mid;
        else hi = mid - 1;
    }
    cout << lo << "\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> nums[i];
    solve();
};