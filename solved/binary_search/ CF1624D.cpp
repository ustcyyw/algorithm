/**
 * @Time : 2024/7/25-11:19 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1624D 二分答案 贪心
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, k, one, two, cnt[26];
string s;

bool check(int len) {
    int need1 = (len % 2) * k, need2 = (len / 2) * k;
    if(need2 > two) return false;
    return need1 <= one + (two - need2) * 2;
}

void solve() {
    for(int num : cnt) {
        one += num % 2;
        two += num / 2;
    }
    int lo = 0, hi = s.size() / k;
    while(lo < hi) {
        int mid = (lo + hi + 1) >> 1;
        if(check(mid)) lo = mid;
        else hi = mid - 1;
    }
    cout << lo << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> k >> s;
        one = two = 0;
        memset(cnt, 0, sizeof(cnt));
        for(char c : s)
            cnt[c - 'a']++;
        solve();
    }
};