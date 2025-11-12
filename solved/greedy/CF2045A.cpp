/**
 * @Time : 2025/1/10-11:27 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2045A 1700 贪心 分类讨论
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e5 + 5, mod = 998244353;
int T, n, cnt[26], cnt1, cntP, cnt2, cntY;
string s;

void init() {
    for(char c : s)
        cnt[c - 'A']++;
    cntY = cnt['Y' - 'A'];
    cntP = min(cnt['N' - 'A'], cnt['G' - 'A']);
    cnt1 = cnt['A' - 'A'] + cnt['E' - 'A'] + cnt['I' - 'A'] + cnt['O' - 'A'] + cnt['U' - 'A'];
    cnt2 = s.size() - cntY - cnt1 - 2 * cntP;
}

int cal(int c1, int c2, int cp) {
    if(c1 * 2 <= cp) return c1 * 5;
    if(c1 * 2 >= c2 + cp) { // 匹配的辅音不够多 辅音全会用完 但是元音只能有 (c2 + cp) / 2个
        int t = (c2 + cp) / 2;
        if((c2 + cp) % 2 == 0) return t + c2 + 2 * cp; // 刚好成对
        return t + c2 - 1 + 2 * cp; // 有一个辅音被剩下 让单个的剩下
    } else { // 辅音够多 所以元音c1个都能用完 优先让ng的组合匹配
        int need = c1 * 2 - cp; // 在双字母辅音用完的请下 需要的单字母辅音
        return c1 + 2 * cp + need;
    }
}

void solve() {
    init();
    int ans = 0;
    for(int i = 0; i <= cntY; i++) {
        for(int j = 0; j <= cntP; j++) {
            ans = max(ans, cal(cnt1 + i, cnt2 + cntY - i + 2 * j, cntP - j));
        }
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> s;
        solve();
    }
};