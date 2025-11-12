/**
 * @Time : 2023/12/15-9:55 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 第一个字母选择a 后续还剩下 c(n - 1, ca - 1) 种字符 这是最小的 t = c(n - 1, ca - 1) 个字符
 * 如果 t < k, 说明第一个字符应该排 b, 并且接下来应该找 k - t小的序列 （固定前缀下的第k - t小的序列）
 * 如果 t >= k 说明第一个字符应该排 a, 那么继续找第k小的序列
 */

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int N = 62;
ull comb[N][N];
int init = []() -> int {
    for (int i = 0; i < N; i++) {
        comb[i][0] = 1;
        for (int j = 1; j <= i; j++)
            comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]);
    }
    return 0;
}();

void dfs(string& s, int i, int a, int b, ull k) {
    if(i == s.size()) return;
    if(a == 0 || b == 0) {
        s[i] = a == 0 ? 'b' : 'a';
        if(a == 0) b--;
        else a--;
        dfs(s, i + 1, a, b, k);
    } else {
        ull t = comb[a + b - 1][a - 1]; // 尝试当前位置放a
        if(t >= k) s[i] = 'a', dfs(s, i + 1, a - 1, b, k);
        else s[i] = 'b', dfs(s, i + 1, a, b - 1, k - t); // 当前位置放a太小了，应该放b
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    int a, b;
    cin >> a >> b;
    ull k;
    cin >> k;
    string s(a + b, 'a');
    dfs(s, 0, a, b, k);
    cout << s << endl;
}