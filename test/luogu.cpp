/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e5 + 5, mod = 998244353;
int T, aux[6][3] = {{0,1,2}, {0,2,1}, {1,0,2}, {1,2,0}, {2,0,1}, {2,1,0}};
string str[3];

// s1的后缀、s2的前缀 最长公共部分的长度
int common(string& s1, string& s2) {
    string s = s2 + s1;
    int n1 = s1.size(), n2 = s2.size(), n = n1 + n2;
    vector<int> z(n, 0);
    z[0] = n;
    for(int i = 1, l = 0, r = 0; i < n; i++){
        if(i <= r) z[i] = min(z[i - l], r - i + 1);
        while (i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;
        if(i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
    }
    for(int i = max(n1, n2); i < n; i++) {
        if(z[i] == n - i) return n - i;
    }
    return 0;
}

int cal(string& s1, string& s2, string& s3) {
    int c1 = common(s1, s2);
    string temp = s1 + s2.substr(c1);
    int c2 = common(temp, s3);
    return temp.size() + s3.size() - c2;
}

int allContains(string& s1, string& s2, string& s3) {
    if(s1.find(s2) != string::npos && s1.find(s3) != string::npos)
        return s1.size();
    return INT_MAX;
}
// 第一个字符串包含第二个字符串的情况
int firstContainsTwo(string& s1, string& s2, string& s3) {
    if(s1.find(s2) == string::npos) return INT_MAX;
    int c1 = common(s1, s3), c2 = common(s3, s1);
    return s1.size() + s3.size() - max(c1, c2);
}

int solve() {
    int ans = INT_MAX;
    for(auto& p : aux) {
        int i = p[0], j = p[1], k = p[2];
        ans = min(ans, allContains(str[i], str[j], str[k]));
        ans = min(ans, firstContainsTwo(str[i], str[j], str[k]));
        ans = min(ans, cal(str[i], str[j], str[k]));
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while (T-- > 0) {
        cin >> str[0] >> str[1] >> str[2];
        cout << solve();
    }
};