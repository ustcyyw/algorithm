/**
 * @Time : 2025/4/19-4:54 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 505, D = 30;
int T, n, m, have[N];
string a[N], b[N][N];

int find(string* temp) {
    int cnt = 0;
    for(int i = 1; i <= n; i++)
        cnt += temp[i] == a[i];
    return cnt;
}

int solve() {
    for(int i = 1; i <= n; i++)
        if(have[i] == 0) return -1;
    // 找公共元素最多的句子有多少个公共元素
    int cnt = 0;
    for(int i = 1; i <= m; i++)
        cnt = max(cnt, find(b[i]));
    return n + (n - cnt) * 2;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> T;
    while (T--) {
        cin >> n >> m;
        memset(have, 0, sizeof(have));
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        for(int i = 1; i <= m; i++) {
            for(int j = 1; j <= n; j++) {
                cin >> b[i][j];
                if(b[i][j] == a[j]) have[j] = 1;
            }
        }
        cout << solve() << "\n";
    }
    return 0;
}