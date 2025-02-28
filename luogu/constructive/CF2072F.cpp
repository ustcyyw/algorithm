/**
 * @Time : 2025/2/27-9:03 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2072F 1687 构造 找规律
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 505, mod = 1e9 + 7;
ll T, n, k, p[N];

int init = []() -> int {
    p[0] = 1;
    for(int i = 1; i < 32; i++)
        p[i] = p[i - 1] * 2;
    return 0;
}();

string dfs(int m) {
    int idx = upper_bound(p, p + 32, m) - p - 1;
    string ans;
    if(m == p[idx]) ans.assign(m, '*');
    else {
        string temp = dfs(m - p[idx]);
        ans = temp;
        while(ans.size() + temp.size() < m)
            ans.push_back('.');
        ans += temp;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> k;
        string ans = dfs(n);
        for(char c : ans)
            cout << (c == '*' ? k : 0) << " ";
        cout << "\n";
    }
}