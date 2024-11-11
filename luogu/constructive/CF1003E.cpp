/**
 * @Time : 2024/4/16-2:28 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 既然是一棵树 比如要选一个根结点 默认就选1
 * 有半径的要求 可以先将确定半径的分枝构成出来
 * 也就是将深度最深len1 和 次深len2 的两条路径构建出来
 * 构造时使用id标识现在已构造的最后一个结点编号 添加一个新的结点首先要++id
 * 那么深度最深的那条路径的 除了根结点1 第一个结点就是编号为2的
 * 因为星型结构是直径最小的 剩下就需要在已有的结点上尽量填满（使结点度数尽量为k）
 * 填充结点时要保证深度和度数不超过相应的要求
 * 具体而言就是
 * 1.先将根结点的儿子结点都构造上 因为根结点是特殊的没有入度的 它的出度比其它所有结点至少多1
 * 2.结点2的子结点深度最深为len1 - 1
 * 3.除2以外的1的子结点的子结点 深度最深为len2 - 1
 *
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 4e5 + 5, M = 1e5 + 5;
int n, k, d, id;
vector<int> graph[N];

void dfs(int v, int degree, int len) {
    if(len == 0 || id > n) return;
    int sz = degree - graph[v].size(); // 计算填满指定出度degree还需要添加多少子结点
    for(int i = 0; i < sz && id <= n; i++) {
        graph[v].push_back(++id);
    }
    for(int w : graph[v]) {
        dfs(w, degree, len - 1);
    }
}

bool solve() {
    if(d >= n) return false;
    if(k == 1) { // 度数为1 只允许两个点之间一条边 因此只要多余2个结点 就没法构建
        if(n > 2) return false;
        graph[1].push_back(2);
        return true;
    }
    id = 1; // 标识现在已构造的最后一个结点编号
    int half = d / 2, mod = d % 2, len1 = half + mod, len2 = half;
    // 构建半径的一边 这一边除了根结点1之外 第一个结点是2
    dfs(1, 1, len1);
    // 构建半径的另一边
    if(len2 > 0) {
        graph[1].push_back(++id);
        dfs(id, 1, len2 - 1);
    }
    // 构建完半径就已经使结点数超过n
    if(id > n) return false;
    // 将根结点填满k个子结点
    while(len2 > 0 && graph[1].size() < k)
        graph[1].push_back(++id);
    // 遍历根结点的子结点 填满其它子结点
    for(int v : graph[1]) {
        if(len2 == 0 || id > n) break;
        int l = v == 2 ? len1 - 1 : len2 - 1; // 结点2这一分支允许深度是len1，也就是从结点2算起深度为len1 - 1
        dfs(v, k - 1, l);
    }
    // 填满的情况下 仍然有结点没有构建到树中
    if(id < n) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> d >> k;
    bool ans = solve();
    if(!ans) cout << "NO";
    else {
        cout << "YES" << "\n";
        for(int v = 1; v <= n; v++) {
            for(int w : graph[v]) {
                if(w > n) continue;
                cout << v << " " << w << "\n";
            }
        }
    }
};