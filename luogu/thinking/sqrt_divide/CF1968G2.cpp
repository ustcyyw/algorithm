/**
 * @Time : 2024/12/9-8:51 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
  * 当分组数较大时 前缀长度小
  *
  * k的取值范围在[n / M, n]上有很多次查询，但是对应的前缀长度 <= M
  * (分组数为n / M, 每组都相同都极限情况，前缀长度也只有n / (n / M) = M)
  * 这些前缀个数很少 因此可以考虑预处理所有长度 <= M 的前缀
  * 对于确定长度len的前缀，单次处理使用kmp算法得到其可以分为cnt个部分
  * 然后记录mp[cnt] = max(mp[cnt], len), 分为cnt个部分时 前缀最长能为多少
  * 时间复杂度 sqrt(n) * n
  * 对于给定的部分数k 找到大于等于k的最小键cnt
  * 长度为len的前缀 分为cnt个部分都可以 那么分为k个部分必然也可以
  * 但是比k小的键 就说明以那个前缀去拆分s 无法得到k这么多个部分
  * 因此答案就是 大于等于k的最小键
  * 预处理的时间复杂度 M * n. 单次查询的时间复杂度log(M)
  *
  * 而k取值范围在[1, n / M)上，查询次数不多 可以采用easy版本的做法
  * 对每个k都二分+kmp处理，整体的时间复杂度时n * n / M * log(n)
  *
  * 结合n = 2e5来看 取M = 2e3
  * 预处理时间复杂度是4e8
  * 二分计算的整体复杂度是 2e5 * 1e2 * 18 = 3.6e8
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, M = 2000;
int T, n, l, r, pi[N];
map<int, int> mp;
string s;
// 查看最多有多少个不交叠的pattern子串
int kmp(string &text, string pattern) {
    int m = pattern.length();
    for (int i = 1, c = 0; i < m; i++) {
        char v = pattern[i];
        while (c && pattern[c] != v)
            c = pi[c - 1];
        if (pattern[c] == v) c++;
        pi[i] = c;
    }
    int res = 0, pre = -1;
    for (int i = 0, c = 0; i < text.length(); i++) {
        char v = text[i];
        while (c && pattern[c] != v)
            c = pi[c - 1];
        if (pattern[c] == v) c++;
        if (c == m) { // 找到一个匹配的子串
            int t = i - m + 1;
            if(t >= pre) res++, pre = t + m;
            c = pi[c - 1];
        }
    }
    return res;
}

void init() {
    mp = {};
    for(int i = 1; i <= min(M, n); i++) {
        int cnt = kmp(s, s.substr(0, i));
        mp[cnt] = max(mp[cnt], i);
    }
}

// 当分组数较小时 前缀的长度比较大 用二分答案的方式求解
// 对二分的上界做优化 因为随着分组数k增大 前缀长度单调不增 因此每次二分的上界从为上一次的结果
void solve1(int k, int& phi) {
    int lo = 0, hi = min(phi, n / k);
    while(lo < hi) {
        int mid = (lo + hi + 1) >> 1;
        int cnt = kmp(s, s.substr(0, mid));
        if(cnt >= k) lo = mid;
        else hi = mid - 1;
    }
    phi = lo;
    cout << lo << " ";
}

// 分组数较大时 前缀大长度较小 从预处理的结果中找答案
void solve2(int k) {
    auto it = mp.lower_bound(k);
    if(it == mp.end()) cout << 0 << " ";
    else cout << it->second << " ";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> l >> r;
        cin >> s;
        init();
        for(int k = l, pre = n; k <= r; k++) {
            if(k >= n / M) solve2(k);
            else solve1(k, pre);
        }
        cout << "\n";
    }
};