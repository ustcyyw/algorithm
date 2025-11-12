/**
 * @Time : 2024/7/12-10:17 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1551D2 构造 数学
 */
/*
 * 先判定
* 1.奇数行 偶数列
* 至少要填满一行 剩下的牌 得成对出现 确保每一列最后都只剩偶数行要填充
* 2.偶数行
* 成对出现 一次占2*2的正方形 列数够放即可
 *
 * 确定可以安排的情况下
 * 奇数行的情况 先填满第一行 就和偶数行一致了
 * 先把横着的先排完 再安排竖着的
*/
#include<bits/stdc++.h>

using namespace std;
const int N = 3e5 + 10, mod = 1e9 + 7;
typedef long long ll;
int T, n, m, k;
vector<string> grid;

bool check(int n, int m, int k) {
    if(n % 2 == 1) {
        if(k * 2 < m) return false;
        k -= m / 2;
        return k % 2 == 0;
    } else {
        if(k % 2 != 0) return false;
        return k <= m / 2 * n;
    }
}
// 从左往右 从上到下安排 所以要考虑上边和左边的字母标识
// flag = true 说明要安排一个横的 要考虑的是grid[i - 1][j + 1]；反之 xxx
char pick(int i, int j, bool flag) {
    char c1 = '.', c2 = '.', c3 = '.';
    if(i > 0) c1 = grid[i - 1][j];
    if(j > 0) c2 = grid[i][j - 1];
    if(flag && i > 0) c3 = grid[i - 1][j + 1];
    if(!flag && j > 0) c3 = grid[i + 1][j - 1];
    for(char c = 'a'; c <= 'z'; c++) {
        if(c != c1 && c != c2 && c != c3) return c;
    }
    return '.';
}
// 从指定行开始 成对地安排上下两行
void pair_fill(int lo) {
    while(k > 0) {
        for(int i = lo; i < n && k; i += 2) {
            for(int j = 0; j + 1 < m && k; j += 2, k -= 2) {
                char c = pick(i, j, true);
                grid[i][j] = grid[i][j + 1] = c;
                c = pick(i + 1, j, true);
                grid[i + 1][j] = grid[i + 1][j + 1] = c;
            }
        }
    }
}

void solve() {
    if(n % 2 == 1) { // 奇数行 先填充第一行
        for(int i = 0; i < m; i += 2, k--) {
            char c = pick(0, i, true);
            grid[0][i] = grid[0][i + 1] = c;
        }
        pair_fill(1);
    } else pair_fill(0);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            if(grid[i][j] == '.') {
                char c = pick(i, j, false);
                grid[i][j] = grid[i + 1][j] = c;
            }
            cout << grid[i][j];
        }
        cout << "\n";
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> n >> m >> k;
        bool f = check(n, m, k);
        if(!f) cout << "NO\n";
        else {
            grid.assign(n, string(m, '.'));
            cout << "YES\n";
            solve();
        }
    }
};