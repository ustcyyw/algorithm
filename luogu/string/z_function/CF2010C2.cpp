/**
 * @Time : 2025/1/6-11:07 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2010C2 1700 字符串 z函数
 */
#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
const int N = 2e5 + 5, mod = 998244353;
int T;
string s;

vector<int> z_function(string& s){
    int n = s.size();
    vector<int> z(n, 0);
    z[0] = n;
    for(int i = 1, l = 0, r = 0; i < n; i++){
        if(i <= r) z[i] = min(z[i - l], r - i + 1);
        while (i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;
        if(i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    return z;
}

string solve() {
    vector<int> z = z_function(s);
    for(int i = 1, n = s.size(); i < n; i++) {
        int len = n - i;
        if(z[i] == len && len - 1 >= i)
            return s.substr(0, len);
    }
    return "";
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> s;
        string ans = solve();
        if(!ans.empty()) cout << "YES\n" << ans;
        else cout << "NO";
    }
};