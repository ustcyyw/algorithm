/**
 * @Time : 2025/1/2-4:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF954I 2200 状态压缩 暴力枚举 kmp
 */
 /*
  * 只有6个字符 最多5次操作
  * b > a, c > a, d > a, e > a, f > a
  * 那么所有字符都会变成a, 两个字符串必然相等
  *
  * 所以只需要考虑
  * 1次操作：将1个字符变为另外5个字符中的一个
  * ...
  * 4次操作：选择4个字母 变成另外的2个字母
  *
  * 需要分析一下为什么选择了一些要变化的字母 规定他们只能变成另外一些字母是正确的
  * 比如选择了a b两个字母
  * 1. 先a -> b, 然后 b -> c 最终结果是a和b都变成了c
  * 其效果和 a -> c, b -> c是一致的
  * 2. 先b -> c, 然后 a -> b。最终s和t中原本是a和b的字符 变成了c和b
  * 而a -> c, b -> c 最终s和t中原本是a和b的字符都变成了c
  * 显然第二种变换方式更容易使得s的子串和t相等
  * 因此将选择变化的字母 变化成没有选的字母 至少是不坏的
  *
  * 在这个基础上分析暴力枚举的最坏情况
  * 操作3次 也就是选择3个字母进行变换，枚举他们可以变换成的字母 得到变换方案
  * 最多有 C(6,3) * 3 ^ 3 = 540 种
  * 将操作1次 2次 3次 4次的所有变换方案加起来 大约1e3中
  * 对于每种变换方案 将原字符串修改后使用kmp进行匹配 找到匹配的子串 时间复杂度是o(n)
  * 考虑到n <= 1.25 e5 整体的时间复杂度在1e8量级
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 125000 + 5, mod = 998244353;
int T, n, ans[N], full = (1 << 6) - 1;
string s, t, chars = "abcdef";

string change_str(string& str, vector<int>& aux) {
    string cc = str;
    for(int i = 0; i < cc.size(); i++) {
        int idx = str[i] - 'a';
        if(aux[idx] != -1)
            cc[i] = chars[aux[idx]];
    }
    return cc;
}
// 通过回溯的方式得到选择字母情况为status的情况下的所有变换方案
void dfs(int status, int i, vector<vector<int>>& arr, vector<int>& change) {
    if(i == 6) {
        vector<int> temp = change;
        arr.push_back(temp);
        return;
    }
    int f = (1 << i) & status;
    if(f == 0) dfs(status, i + 1, arr, change);
    else {
        for(int j = 0; j < 6; j++) {
            if(((1 << j) & status) == 0) {
                change[i] = j;
                dfs(status, i + 1, arr, change);
            }
        }
    }
}

void kmp(string& text, string& pattern, int cnt) {
    int m = pattern.length();
    vector<int> pi(m);
    for (int i = 1, c = 0; i < m; i++) {
        char v = pattern[i];
        while (c && pattern[c] != v)
            c = pi[c - 1];
        if (pattern[c] == v) c++;
        pi[i] = c;
    }
    for (int i = 0, c = 0; i < text.length(); i++) {
        char v = text[i];
        while (c && pattern[c] != v)
            c = pi[c - 1];
        if (pattern[c] == v) c++;
        if (c == m) {
            ans[i - m + 1] = min(ans[i - m + 1], cnt);
            c = pi[c - 1];
        }
    }
}

void change(int status, int cnt) {
    vector<vector<int>> arr;
    vector<int> temp(6, -1);
    dfs(status, 0, arr, temp);
    for(auto& aux : arr) {
        string sc = change_str(s, aux), tc = change_str(t, aux);
        kmp(sc, tc, cnt);
    }
}

void solve() {
    memset(ans, 6, sizeof(ans));
    for(int u = 1; u <= full; u++) { // 枚举选择的字母
        change(u, __builtin_popcount(u));
    }
    kmp(s, t, 0);
    for(int i = 0; i < s.size() - t.length() + 1; i++)
        cout << ans[i] << " ";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> s >> t;
        solve();
    }
};