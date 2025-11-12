/**
 * @Time : 2024/5/11-4:26 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1157G
 */
/*
* 枚举分界点（i, j） 在那之前都是0 在那及之后都是1
*
* [1,i-1]行 全都是0 是否能满足 能满足的情况下 列应该如何调整 相应的行应该如何调整
* 第1行有翻转 或者不翻转的情况 以不翻转为例
* 第1行是1的列 都记该列需要翻转 是0的列都记该行不翻转
* 然后检查第2行 对列的要求是否一致, 第3行...
*
* [i+1,n]行 全都是1 是否能满足
*
* 可以进行前后缀分解 然后单独check第i行。
* 但是前缀有2组 后缀有2组 共4种搭配情况 需要都枚举
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 205;
int n, m, grid[N][N], same_flag[4] = {0};
vector<int> pre1, up1, pre2, up2, suf1, down1, suf2, down2;
vector<pair<vector<int>, vector<int>>> ps, ud;

bool check_same(vector<int>& a, vector<int>& b) {
    for(int i = 0; i < m; i++)
        if(a[i] != b[i]) return false;
    return true;
}

// 指定相应行进行改变 不等于val就要在对应列进行翻转
void general_line(vector<int>& base, int i, int val) {
    for(int j = 0; j < m; j++) {
        if(grid[i][j] != val)
            base[j] = 1;
    }
}

void init_pre(vector<int>& pre, vector<int>& up) {
    for(int i = 1; i < n; i++) { // 逐行检查 按第一行的翻转情况 是否可以将[0,i]行全部变为0
        vector<int> temp1(m, 0), temp2(m, 0);
        general_line(temp1, i, 0); // 第i行不翻转的情况
        if(check_same(temp1, up)) {
            pre[i] = 0;
            continue;
        }
        general_line(temp2, i, 1); // 第i行翻转的情况
        if(check_same(temp2, up)) {
            pre[i] = 1;
        } else break; // 第i行无论是否翻转 都无法根据第一行的情况变为全为0
    }
}

void init_suf(vector<int>& suf, vector<int>& down) {
    for(int i = n - 2; i >= 0; i--) { // 逐行检查 按第最后一行的翻转情况 是否可以将[i, n - 1]行全部变为1
        vector<int> temp1(m, 0), temp2(m, 0);
        general_line(temp1, i, 1); // 第i行不翻转的情况 对于后缀来说 不为1的列要变化
        if(check_same(temp1, down)) {
            suf[i] = 0;
            continue;
        }
        general_line(temp2, i, 0); // 第i行翻转的情况
        if(check_same(temp2, down)) {
            suf[i] = 1;
        } else break; // 第i行无论是否翻转 都无法根据第一行的情况变为全为1
    }
}
// add = 0, 表示第i行没有翻转； add = 1表示第i行翻转了
bool check_line(vector<int>& base, int i, int j, int add) {
    for(int k = 0; k < m; k++) {
        int val = (grid[i][k] + base[k] + add) % 2;
        if(k < j && val == 1) return false;
        if(k >= j && val == 0) return false;
    }
    return true;
}

int check_split(vector<int>& pre, vector<int>& suf, vector<int>& up, vector<int>& down,
                int k, int i, int j) {
    if(i > 0 && pre[i - 1] == -1) return -1;
    if(i < n - 1 && suf[i + 1] == -1) return -1;
    // 第i行不是第一行或者最后一行，那么就要求前缀和后缀对列的翻转情况一致
    if(i != 0 && i != n - 1 && !same_flag[k]) return -1;
    vector<int>& base = i == 0 ? down : up;
    // 第j行不翻转的情况
    if(check_line(base, i, j, 0)) return 0;
    // 第j行翻转的情况
    if(check_line(base, i, j, 1)) return 1;
    return -1;
}

void comb(vector<int>& pre, vector<int>& suf, vector<int>& up, vector<int>& down, int i) {
    if(check_same(up, down)) same_flag[i] = 1;
    ps.emplace_back(pre, suf);
    ud.emplace_back(up, down);
}

void std_out(vector<int>& pre, vector<int>& suf, int i, int flag) {
    for(int k = 0; k < i; k++)
        cout << pre[k];
    cout << flag;
    for(int k = i + 1; k < n; k++)
        cout << suf[k];
    cout << "\n";
}

void solve() {
    // 第一行不翻转的情况
    general_line(up1, 0, 0);
    pre1[0] = 0, init_pre(pre1, up1);
    // 第一行翻转的情况 那么1会变为0 0变为1，所以原本不等1的列要翻转
    general_line(up2, 0, 1);
    pre2[0] = 1, init_pre(pre2, up2);
    // 最后一行不翻转的情况 不是1的要变为1
    general_line(down1, n - 1, 1);
    suf1[n - 1] = 0, init_suf(suf1, down1);
    // 最后一行翻转的情况
    general_line(down2, n - 1, 0);
    suf2[n - 1] = 1, init_suf(suf2, down2);
    comb(pre1, suf1, up1, down1, 0), comb(pre1, suf2, up1, down2, 1);
    comb(pre2, suf1, up2, down1, 2), comb(pre2, suf2, up2, down2, 3);
    for(int k = 0; k < 4; k++) {
        vector<int> &pre = ps[k].first, &suf = ps[k].second;
        vector<int> &up = ud[k].first, &down = ud[k].second;
        // 枚举分割点 分割点以前都是0 分割点及其以后都是1
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                int temp = check_split(pre, suf, up, down, k, i, j);
                if(temp == -1) continue;
                cout << "YES\n";
                std_out(pre, suf, i, temp);
                vector<int>& base = i == 0 ? down : up;
                for(int l = 0; l < m; l++)
                    cout << base[l];
                return;
            }
        }
    }
    cout << "NO";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++)
            cin >> grid[i][j];
    }
    pre1.assign(n, -1), pre2.assign(n, -1);
    suf1.assign(n, -1), suf2.assign(n, -1);
    up1.assign(m, 0), up2.assign(m, 0);
    down1.assign(m, 0), down2.assign(m, 0);
    solve();
};