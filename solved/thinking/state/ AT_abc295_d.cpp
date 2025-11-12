/**
 * @Time : 2023/8/30-5:20 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int M = (2 << 10);
int cnt[M];
string s;

long solve() {
    long res = 0;
    cnt[0] = 1;
    for(int i = 0, u = 0; i < s.size(); i++) {
        u ^= 1 << (s[i] - '0');
        res += cnt[u];
        cnt[u]++;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> s;
    memset(cnt, 0, sizeof(cnt));
    cout << solve() << endl;
}
