/**
 * @Time : 2024/7/16-11:06 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1992D
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e4, mod = 1e9 + 7;
typedef long long ll;
int T, n, m, k;
string s;

bool solve() {
    int cnt = 0, i = 0;
    while (i <= n + 1) {
        int j = i + 1;
        while(j <= n + 1 && j - i <= m && s[j] != 'L') j++;
        if(j - i <= m) i = j;
        else {
            i = j - 1;
            while(i <= n + 1) {
                if(s[i] == 'C') return false;
                if(s[i] == 'W') cnt++, i++;
                if(s[i] == 'L') break;
            }
        }
    }
    return cnt <= k;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> m >> k >> s;
        s = 'L' + s + 'L';
        cout << (solve() ? "YES" : "NO") << "\n";
    }
};