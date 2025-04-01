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