/**
 * @Time : 2024/4/11-10:29 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N = 5005;
int T, n, diff[N];
string s;

bool check(int len) {
    memset(diff, 0, sizeof(diff));
    for(int i = 0, sum = 0; i < n; i++) {
        sum += diff[i];
        if((s[i] - '0' + sum) % 2 == 0) { // 考虑翻转和原本字母的情况
            if(i + len > n) return false;
            sum++, diff[i + len]--;
        }
    }
    return true;
}

int solve() {
    for(int len = n; len > 1; len--) {
        if(check(len)) return len;
    }
    return 1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        cin >> s;
        cout << solve() << "\n";
    }
};