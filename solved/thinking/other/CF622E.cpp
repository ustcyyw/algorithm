/**
 * @Time : 2024/4/8-9:45 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 结点1允许同时存在多个蚂蚁 那么对于1的所有儿子结点son[i]
 * 如果知道son[i]中最后一只蚂蚁到达的时间ti，取这些时间的最大值再+1就是答案
 *
 * 对于某一个1的儿子结点son，求最后一只蚂蚁到达的时间
 * 如果所有叶子结点深度不一样 蚂蚁们都可以按先来后到的顺序通过son
 * 但是如果存在深度一样的叶子结点 那么他们在到son的途中可能会在某个公共结点相遇
 * 比如有v和w两蚂蚁同时到达结点node1，v先走一步 那么w到达node1及其所有祖先结点的时间就会滞后1秒
 * 在此基础之上 如果w行走途中和x又在另外一个结点node2相遇了，这次x先走
 * w到达node2及其所有祖先结点的时间就会再滞后1秒
 * 到达时间是关键 但凡遇到相同到达时间 就要让其中一只蚂蚁滞后1秒
 * 滞后过的蚂蚁还可能与别的蚂蚁同时到达某个结点
 *
 * 因此我们要对叶子结点深度进行排序 这是原始的蚂蚁行走时间
 * 一旦有相同的时间 必然会有相遇的情况 让其中一只先走 其它依次排队滞后
 * 假设当前蚂蚁x滞后处理后的时间是t，另外一只蚂蚁y的原始行走时间 <= t
 * 就说明y和x都是同时排队的，就再对y进行滞后处理 t++
 */
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N = 1e6 + 5;
int n;
vector<int> graph[N];

void dfs(vector<int>& ot, int v, int f, int depth) {
    if(graph[v].size() == 1) ot.push_back(depth);
    for(int w : graph[v]) {
        if(w != f)
            dfs(ot, w, v, depth + 1);
    }
}

void solve() {
    int ans = 0;
    for(int w : graph[1]) {
        vector<int> originT; // 原始到达时间
        dfs(originT, w, 1, 0);
        sort(originT.begin(), originT.end());
        int t = -1;
        for(int ot : originT) {
            if(t < ot) t = ot; // 此时当前蚂蚁不需要滞后 直接走。蚂蚁的行走时间将由ot及之后的蚂蚁确定
            else t++; // t >= ot的情况 蚂蚁的滞后时间+1
        }
        ans = max(t, ans);
    }
    cout << (ans + 1);
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 0, v, w; i < n - 1; i++) {
        cin >> v >> w;
        graph[v].push_back(w), graph[w].push_back(v);
    }
    solve();
};