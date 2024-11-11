/**
 * @Time : 2024/11/5-11:06 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1914G1 思维
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e3 + 5, mod = 998244353;
int T, n, nums[N], nxt[N], pre[N];

void init() {
    map<int, int> map;
    for(int i = 2 * n; i >= 1; i--) {
        int num = nums[i];
        if(map.count(num)) nxt[i] = map[num];
        else map[num] = i, nxt[i] = -1;
    }
    map.clear();
    for(int i = 1; i <= 2 * n; i++) {
        int num = nums[i];
        if(map.count(num)) pre[i] = map[num];
        else map[num] = i, pre[i] = 2 * n + 1;
    }
}

int group(int lo) {
    int i = lo, j = nxt[i];
    for(; i <= 2 * n && i <= j; ) {
        j = max(j, nxt[i]);
        i++;
    }
    return i - 1;
}

bool check(int lo, int hi, int idx) {
    int i = nxt[idx], j = idx, l = idx, r = nxt[idx];
    while(i >= l || j <= r) {
        if(l == lo || r == hi) return true;
        if(i >= l) {
            l = min(pre[i], l), r = max(nxt[i], r);
            i--;
        }
        if(j <= r) {
            l = min(pre[j], l), r = max(nxt[j], r);
            j++;
        }
    }
    return false;
}

int cal(int lo, int hi) {
    int cnt = 0;
    for(int i = lo; i <= hi; i++) {
        if(nxt[i] == -1) continue;
        cnt += check(lo, hi, i);
    }
    return cnt * 2;
}

void solve() {
    ll cnt = 0, ans = 1;
    for(int i = 1, j; i <= 2 * n; ) {
        j = group(i);
        cnt++, ans = ans * cal(i, j) % mod;
        i = j + 1;
    }
    cout << cnt << " " << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n;
        for(int i = 1; i <= 2 * n; i++)
            cin >> nums[i];
        init();
        solve();
    }
};