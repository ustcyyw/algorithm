/**
 * @Time : 2024/3/27-9:19 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 要尽可能地利用字母 那么每次排列出t 都应该尽可能地利用上一个t的子串
 * 所以应该找最长公共前后缀 z函数
 */
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int N = 1e6 + 5, mod = 1e9 + 7;
int one, zero;
string s, t;

int z_function(string& str){
    int n = str.size();
    vector<int> z(n, 0);
    z[0] = n;
    for(int i = 1, l = 0, r = 0; i < n; i++){
        if(i <= r) z[i] = min(z[i - l], r - i + 1);
        while (i + z[i] < n && str[i + z[i]] == str[z[i]]) z[i]++;
        if(i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
        if(z[i] == n - i) return z[i];
    }
    return 0;
}

string solve() {
    int n = s.size(), m = t.size();
    if(n < m) return s;
    one = 0, zero = 0;
    for(char c : s) {
        if(c == '0') zero++;
        else one++;
    }
    string ans;
    for(int i = 0, len = z_function(t); ;) {
        if(t[i] == '0' && zero) ans.push_back('0'), zero--;
        else if(t[i] == '1' && one) ans.push_back('1'), one--;
        else break;
        i = i + 1;
        if(i == m) i = len;
    }
    while(one-- > 0) ans.push_back('1');
    while(zero-- > 0) ans.push_back('0');
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> s >> t;
    cout << solve() << "\n";
};
