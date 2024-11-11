/**
 * @Time : 2023/9/4-8:48 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 3e5 + 5;
long n, m, k, sum[N];
string s;

long solve() {
    long total = sum[n];
    if(total * m <= k) return (long)n * m; // 能将所有x进行替换的情况
    long t = k / total, mod = k % total, res = 0;
    // 选取的串中间有完整t个子串，前面和后面两个子串分别取靠近中间的部分
    if(t + 2 <= m) {
        int l = 0, r = 0;
        while (r < n && sum[r] <= mod) {
            while (l < n && sum[r] + sum[n] - sum[l] > mod) l++;
            if(sum[r] <= mod)
                res = max(res, n - l + r);
            r++;
        }
    }
    // 选取的串有t个周期，但开头位置不是子串开头，后面再跟着一段额外部分
    if(t + 1 <= m) {
        int l = 0, r = 0;
        while (r < n) {
            while (l < n && sum[r + 1] - sum[l] > mod) l++;
            res = max(res, (long)r - l + 1);
            r++;
        }
    }
    return t * n + res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m >> k >> s;
    for(int i = 1; i <= n; i++)
        sum[i] = sum[i - 1] + (s[i - 1] == 'x');
    cout << solve() << endl;
}