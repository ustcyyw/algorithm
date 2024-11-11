/**
 * @Time : 2024/3/6-4:58 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * ls, rs分别表示某个结点的左子结点和右子结点
 * cnt[i]: i子树中结点个数
 * 在v已经感染的情况下，要切掉一个结点阻止感染 要么切左边 要么切右边
 * 切左边 那么能拯救的结点：
 * 1. 左子树中除ls[v]以外的结点cnt[ls[v]] - 1
 * 2. 右子树中rs[v]被感染 继续后续的拯救
 * 切右边 类似地
 * 两种方案取最大
 * 就是二叉树上的递归取最大值
 */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int N = 3e5 + 5;
int n, T, ls[N], rs[N], cnt[N];
vector<vector<int>> graph;

void dfs1(int v, int f) {
    for(int w : graph[v]) {
        if(w == f) continue;
        if(ls[v] == -1) ls[v] = w;
        else rs[v] = w;
        dfs1(w, v), cnt[v] += cnt[w];
    }
}

int dfs2(int v) {
    if(ls[v] == -1) return 0;
    if(rs[v] == -1) return cnt[ls[v]] - 1;
    return max(cnt[ls[v]] - 1 + dfs2(rs[v]), cnt[rs[v]] - 1 + dfs2(ls[v]));
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        graph.assign(n + 1, {});
        fill(ls, ls + n + 1, -1), fill(rs, rs + n + 1, -1);
        fill(cnt, cnt + n + 1, 1);
        for(int i = 0, v, w; i < n - 1; i++) {
            cin >> v >> w;
            graph[v].push_back(w), graph[w].push_back(v);
        }
        dfs1(1, -1);
        cout << dfs2(1) << "\n";
    }
};