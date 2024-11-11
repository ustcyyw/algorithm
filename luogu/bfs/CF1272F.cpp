/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
/*
 * 公共超序列问题 首先要计算两个字符串的最长公共子序列
 * 本题中还需要进行括号匹配，假设是从左到右构建匹配点括号 那么会出现左括号暂时出现多余
 * 共需要3个维度描述状态
 * 定义dp[i][j][k]: 匹配至s[i], t[j]，多余的左括号有k个的最短序列长度
 * 因为要构造出最短序列 还需要记录转移过程 {i,j,k} 转移到 {ni, nj, nk}
 * 就记录{ni, nj, nk}的前置状态是 {i,j,k} （逆向记录 因为最终状态是{n, m, 0}是确定的）
 *
 * dp[i][j][k]的转移过程中 从一个状态到下一个状态 序列长度都是+1
 * 因此将这些状态视为三维空间的点，点与点之间如果相连 边权是1
 * 最短序列长度的问题 从动态规划化简为最短路径问题 又因为边权都是1 等价于一个bfs
 * 因为不关注序列长度 dp数组可以直接不维护
 *
 * 于是剩下的问题就是确定哪些点是相连的 以及确定状态的边界（点的边界）
 * {i,j,k}
 * 1.添加右括号，要求k > 0，nk = k - 1
 *  1a. 如果s[i+1] == ')'，s[i+1]被匹配 i += 1
 *  1b. 如果t[j+1] == ')'，t[j+1]被匹配 j += 1
 *  1c. s[i+1]和t[j+1]都被匹配
 *  但凡字符相等 就应当进行匹配 因为匹配之后仍可以自由添加括号 先进行匹配不会使结果变差
 * 2.添加左括号，要求k < m + n, nk = k + 1
 * 要求k < m + n的原因 两字符串即使全是左括号，构造出来的最终答案里 最多也就只有m + n个左括号
 * 同理
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 205;
string s, t;
int n, m;
struct node {
    int i, j, k;
};
node f[N][N][2 * N];
queue<node> q;

void add(node pn, int i, int j, int k) {
    if(f[i][j][k].i != -1) return; // 对应node中i被赋值 说明已经在bfs中访问过了
    q.push((node){i, j, k}), f[i][j][k] = pn;
}

void solve() {
    memset(f, -1, sizeof(f));
    q.push((node){0, 0, 0});
    while(!q.empty()) {
        node x = q.front();
        int i = x.i, j = x.j, k = x.k;
        if(k > 0) { // 添加右括号
            int ni = i + (i + 1 < n && s[i + 1] == ')');
            int nj = j + (j + 1 < m && t[j + 1] == ')');
            add(x, ni, nj, k - 1);
            if(ni == n - 1 && nj == m - 1 && k - 1 == 0) break;
        }
        if(k < m + n) { // 添加左括号
            int ni = i + (i + 1 < n && s[i + 1] == '(');
            int nj = j + (j + 1 < m && t[j + 1] == '(');
            add(x, ni, nj, k + 1);
            if(ni == n - 1 && nj == m - 1 && k + 1 == 0) break;
        }
        q.pop();
    }
    // 从最终状态倒推出构造结果
    string res;
    node x = (node){n - 1, m - 1, 0}; // 末状态
    while(x.i || x.j || x.k) { // 初始状态 i j k 都为0
        node p = f[x.i][x.j][x.k];
        if(x.k == p.k + 1) res = '(' + res; // 当前状态的左括号比前置状态多1 所以放置的是左括号
        else res = ')' + res;
        x = p;
    }
    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> s >> t;
    s = '.' + s, t = '.' + t;
    n = s.size(), m = t.size();
    q = {};
    solve();
};