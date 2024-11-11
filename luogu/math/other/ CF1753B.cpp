/**
 * @Time : 2024/3/13-9:42 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 *
 */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int MOD = 1e9 + 7, N = 5e5 + 5;
int T, n, x, cnt[N];

string solve() {
    for(int i = 0, y; i < n; i++) {
        cin >> y;
        cnt[y]++;
    }
    for(int i = 1; i < x; i++) {
        if(cnt[i] % (i + 1) != 0) return "No";
        cnt[i + 1] += cnt[i] / (i + 1);
    }
    return "Yes";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> x;
    memset(cnt, 0, sizeof(cnt));
    cout << solve() << "\n";
};