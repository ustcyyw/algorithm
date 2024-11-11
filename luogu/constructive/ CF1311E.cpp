/**
 * @Time : 2024/6/24-11:41 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1311E 构造 + 递归
 */
 /*
  * 总距离最短的构造方法是平衡二叉树 距离最长的是退化为单链
  * 可以分别计算出最短距离和最长距离
  * 只要所给的d介于二者之间 总是能通过调整结点位置构造出指定总距离的
  * 定义dfs(f, n, d)表示构造一个n个结点并且总距离为d的二叉树 并且根结点编号为f
  * 记左子树的数目为lc，右子树数目为rc 那么 lc + rc + 1 = n
  * 记左子树中结点到其子树根的总距离为ld，右子树中结点到其子树根的总距离为rd
  * 那么 ld + rd + (n - 1) = d
  * 加上(n - 1)就是指所有子结点到f的距离都要经过左子树的根 or 右子树的根 再走1的距离到根结点
  * 枚举lc 根据 lc, rc = n - lc - 1 计算出两个子树的中距离和的限制
  * ld1 <= ld <= ld2, rd1 <= rd  <= rd2
  * 再根据 ld + rd + (n - 1) = d，可知 rd = d - ld - (n - 1)
  * 于是 rt1 = d - rd2 - (n - 1) <= rd <= rt2 = d - rd1 - (n - 1)
  * 因此 rd >= max(rd1, rt1), rd <= min(rd2, rt2)
  * 如果这个不等式有解就说明可以让右子树有rc = n - lc - 1个结点，并且取其中一个解 rd = max(rd1, rt1)
  * 那么左子树有lc个结点，ld = d - (n - 1) - rd
  * 继续递归即可
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 1e6 + 5;
typedef long long ll;
int T, M, D, ans[5005];

int min_dis(int m) {
    int sum = 0;
    for(int t = 0, cnt = 1; m > 0; t++, cnt *= 2) {
        sum += t * min(cnt, m);
        m -= min(cnt, m);
    }
    return sum;
}

int max_dis(int m) {
    return m * (m - 1) / 2;
}

void dfs(int f, int n, int d) {
    for(int lc = 1; lc < n; lc++) {
        int ld1 = min_dis(lc), ld2 = max_dis(lc);
        int rd1 = min_dis(n - lc - 1), rd2 = max_dis(n - lc - 1);
        int rt1 = d - (n - 1) - ld2, rt2 = d - (n - 1) - ld1;
        int lo = max(rd1, rt1), hi = min(rd2, rt2);
        if(lo <= hi) {
            int rd = lo, ld = d - (n - 1) - rd;
            ans[f + 1] = f;
            dfs(f + 1, lc, ld);
            if(lc != n) {
                ans[f + lc + 1] = f;
                dfs(f + lc + 1, n - lc - 1, rd);
            }
            break;
        }
    }
}

void solve() {
    dfs(1, M, D);
    cout << "YES\n";
    for(int i = 2; i <= M; i++)
        cout << ans[i] << " ";
    cout << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while (T-- > 0) {
        cin >> M >> D;
        int lo = min_dis(M), hi = max_dis(M);
        if(D < lo || D > hi) {
            cout << "NO\n";
            continue;
        }
        solve();
    }
};