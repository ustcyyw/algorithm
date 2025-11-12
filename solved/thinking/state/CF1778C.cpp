/**
 * @Time : 2024/3/11-8:13 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * a中最多出现10种字母 使用一个二进制位表示相应的字母是否要被替换
  * 并且使用一个int类型变量表示字母是否被替换的情况 肯定是要用满k种字母
  * 能被替换的字母 就替换为和b相等的字母即可
  * 最后 使用双指针来确定连续相等的子串（长度），计算这个字串能贡献多少答案
  */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int MOD = 1e9 + 7, N = 2e5 + 5;
int T, n, k, cnt[30];
string a, b;

void map_character() {
    int count = 0;
    fill(cnt, cnt + 27, -1);
    for(char c : a)
        if(cnt[c - 'a'] == -1) cnt[c - 'a'] = count++;
}

bool equal(int s, int i) {
    return a[i] == b[i] || (1 << cnt[a[i] - 'a'] & s);
}

ll cal(int s) {
    ll sum = 0;
    for(int i = 0, j = 0; i < n; ) {
        while(i < n && !equal(s, i)) i++;
        j = i;
        while(j < n && equal(s, j)) j++;
        ll len = j - i;
        sum += len * (len + 1) / 2; // 该子串贡献的答案
        i = j;
    }
    return sum;
}

ll solve() {
    if(k == 10) return (ll)n * (n + 1) / 2;
    map_character();
    ll res = 0;
    for(int s = 0; s <= (1 << 10) - 1; s++) {
        if(__builtin_popcount(s) != k) continue;
        res = max(res, cal(s));
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> k;
        cin >> a >> b;
        cout << solve() << "\n";
    }
};