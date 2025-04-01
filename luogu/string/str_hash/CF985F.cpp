/**
 * @Time : 2025/3/31-10:20 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF985F 2300 字符串hash
 */
 /*
  * 以一一映射意义下 同构的两个字符串
  * 以t为模版字符串，s来映射
  * s[i] != t[i]时
  * 映射表中没有s[i]时，添加映射 s[i] -> t[i]
  * 否则映射表中 s[i] != t[i], 则返回不同构成
  * 也就是说 s中相同的字母的位置集合，这个集合对应的t中的字母必须是相同的字母（不必与s中相同）
  * 将字符串中 相同字母的位置集合 叫 pos[i]
  * 比如s = "abcaa", pos[a] = {1,4,5}, pos[b] = {2}
  * 于是同构的意义就是 s中pos[i]的集合 与t中pos[i]的集合 一致
  * 如果pos换一种表示方式，用字符串来表示
  * pos[i][j] = '1'表示对于字母i，在s[j] = i
  * pos[i][j] = '0'表示对于字母i，在s[j] != i
  * pos[a] = "10010", pos[b] = "01000", pos[c] = "00100"
  * 于是同构的意义就是 pos的字符串集合一致
  * 要校验字符串集合一致 显然可以使用字符串hash来优化
  * 对于26个字母的二进制字符串 找到对应子串的hash值 将这26个hash值进行比较看是否一致即可
  *
  * 校验一致时 用map会超时，用vector排序可以ac
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 2e5 + 15, M = 30;
const ull B1 = 131, P1 = 1e9 + 7;      // 第一个哈希参数
const ull B2 = 29, P2 = 998244353;  // 第二个哈希参数
ll n, m;
vector<pair<ull, ull> > vl,vr;
string s;

ull H1s[26][N], H2s[26][N];  // 哈希值
ull P1_pow[N], P2_pow[N];  // 幂次表

int init = []() -> int {
    P1_pow[0] = P2_pow[0] = 1;
    for (int i = 1; i < N; i++) {
        P1_pow[i] = P1_pow[i - 1] * B1 % P1;
        P2_pow[i] = P2_pow[i - 1] * B2 % P2;
    }
    return 0;
}();

void init_hash(char c, ull *H1, ull *H2) {
    for (int i = 1; i <= n; i++) {
        char cc = s[i - 1] == c ? '1' : '0';
        H1[i] = (H1[i - 1] * B1 + cc) % P1;
        H2[i] = (H2[i - 1] * B2 + cc) % P2;
    }
}

// 获取子串 [l, r] 的哈希值
pair<ull, ull> get_hash(const ull *H1, const ull *H2, int l, int r) {
    ull hash1 = (H1[r] - H1[l - 1] * P1_pow[r - l + 1] % P1 + P1) % P1;
    ull hash2 = (H2[r] - H2[l - 1] * P2_pow[r - l + 1] % P2 + P2) % P2;
    return {hash1, hash2};
}

bool check(int k1, int k2, int len) {
    vl.clear(), vr.clear();
    for(int i = 0, r1 = k1 + len - 1, r2 = k2 + len - 1; i < 26; i++) {
        vl.push_back(get_hash(H1s[i], H2s[i], k1, r1));
        vr.push_back(get_hash(H1s[i], H2s[i], k2, r2));
    }
    sort(vl.begin(), vl.end()), sort(vr.begin(), vr.end());
    return vl == vr;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m >> s;
    for(int i = 0; i < 26; i++) {
        init_hash((char)(i + 'a'), H1s[i], H2s[i]);
    }
    for(int i = 1, k1, k2, len; i <= m; i++) {
        cin >> k1 >> k2 >> len;
        cout << (check(k1, k2, len) ? "YES" : "NO") << "\n";
    }
}