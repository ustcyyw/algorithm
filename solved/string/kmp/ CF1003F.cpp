/**
 * @Time : 2024/4/17-10:56 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 305, M = 1e5 + 5;
int n, nums[N], lens[N] = {0}, base;

// nums[lo, hi]代表模式串
int kmp(int lo, int hi) {
    int m = hi - lo + 1, ans = 0;
    vector<int> pi(m);
    for (int i = 1, c = 0; i < m; i++) {
        int v = nums[lo + i];
        while (c && nums[lo + c] != v)
            c = pi[c - 1];
        if (nums[lo + c] == v) c++;
        pi[i] = c;
    }
    for (int i = 1, c = 0, pre = -1000; i <= n; i++) { // 用pre表示上一次匹配的子串开始索引
        int v = nums[i];
        while (c && nums[lo + c] != v)
            c = pi[c - 1];
        if (nums[lo + c] == v) c++;
        if (c == m) {
            if(i - m + 1 - pre >= m) ans++, pre = i - m + 1;
            c = pi[c - 1];
        }
    }
    return ans;
}

void solve() {
    int res = 0; // 计算能缩短的长度
    for(int i = 1; i <= n; i++) {
        for(int j = i; j <= n; j++) {
            int cnt = kmp(i, j);
            if(cnt >= 2) {
                int temp = (lens[j] - lens[i - 1] - (j - i + 1) + (j - i)) * cnt;
                res = max(res, temp);
            }
        }
    }
    cout << (base - res);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    base = n - 1;
    unordered_map<string, int> map;
    string t;
    for(int i = 1; i <= n; i++) {
        cin >> t;
        base += t.size();
        lens[i] = lens[i - 1] + t.size();
        if(!map.count(t)) map[t] = map.size();
        nums[i] = map[t];
    }
    solve();
};