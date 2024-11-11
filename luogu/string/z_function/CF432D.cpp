/**
 * @Time : 2024/3/6-10:02 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * z函数 z[i]:s[i,n-1]与s的最长公共前缀长度
 * s[i, n-1]长度为n-i, 如果有z[i] == n - i, 说明 s[i,n-1] = s[0, n-i-1]
 * 这是一个答案字符 要计算其出现了多少次
 * 已知 s[i,n-1] = s[0, n-i-1]
 * 如果存在 z[j] = l >= n-i, s[j, l+j-1] = s[0, l-1]
 * l-1 >= n-i-1, 所以s[0, n-i-1]是s[0, l-1]的前缀，所以s[i,n-1]是s[j, l+j-1]的前缀
 * 因此以j为开始下标 s[i,n-1] 出现了一次。
 * 要计算s[i,n-1]出现了几次 就只需要找到有多少个z[j] >= n - i即可
 */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int N = 1e5 + 5;
int n, m, cnt[N];
string s;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    memset(cnt, 0, sizeof(cnt));
    cin >> s;
    n = s.size();
    vector<int> z(n, 0), lens;
    z[0] = n, lens.push_back(n);
    for(int i = 1, l = 0, r = 0; i < n; i++){
        if(i <= r) z[i] = min(z[i - l], r - i + 1);
        while (i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;
        if(i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
        lens.push_back(z[i]);
    }
    sort(lens.begin(), lens.end());
    int ans = 0;
    for(int i = n - 1, j = 0; i >= 0; i--) {
        if(z[i] != n - i) continue;
        ans++;
        while(j < n && lens[j] < n - i) j++;
        cnt[n - i] = n - j;
    }
    cout << ans << "\n";
    for(int i = 1; i <= n; i++) {
        if(cnt[i]) cout << i << " " << cnt[i] << "\n";
    }
};