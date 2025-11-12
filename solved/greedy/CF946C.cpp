/**
 * @Time : 2025/3/21-11:31 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF946C 1300 贪心
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 3e5 + 15, mod = 1e9 + 7;
int T, n;
string s;

bool check() {
    for(int i = 0, cur = 0; i < s.size(); i++) {
        int c = s[i] - 'a';
        if(c <= cur) {
            s[i] = (char)(cur + 'a');
            cur++;
        }
        if(cur == 26) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> s;
        cout << (check() ? s : "-1") << "\n";
    }
}