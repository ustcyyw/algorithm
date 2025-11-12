/**
 * @Time : 2024/6/18-12:19 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1283F 贪心 拓扑排序
 */
/*
  * 2,4,8,16,32,64...   贡献值为2^i的灯泡 比它编号小的所有灯泡的贡献值之和都大
  * 也就是说一条路径的贡献值的相对大小 只取决于这条路径对应的子树中 结点的最大编号
  *
  * ai是按边重要性排序后 通电一端的灯泡
  * 没有出现在ai中的点的编号 一定是叶子结点 并且a[n - 1]是最小编号的结点的父亲
  * 更一般地 倒着遍历ai 便利一个结点 将其计数-1，计数为0 说明它成为了新的等价叶子结点
  * （这个过程就像拓扑排序）
  * 并且每次要将等价编号最小的结点弹出与当前的遍历到的结点连成一条边
  * 更新最大结点编号 以便用于下一轮找到编号最小的结点
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 998244353;
typedef long long ll;
int T, n, arr[N], cnt[N];
vector<vector<int>> edges;

struct cmp{
    bool operator()(pair<int, int>& a, pair<int, int>& b){
        return a.second > b.second;
    }
};
priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;

void solve() {
    for(int i = 1; i <= n; i++)
        if(cnt[i] == 0) pq.push({i, i});
    for(int i = n - 1; i >= 1; i--) {
        int v = arr[i];
        cnt[v]--;
        pair<int, int> p = pq.top();
        pq.pop();
        int w = p.first, m_node = p.second;
        edges.push_back({v, w});
        if(cnt[v] == 0) pq.push({v, max(v, m_node)});
    }
    cout << arr[1] << "\n";
    for(vector<int>& edge : edges)
        cout << edge[0] << " " << edge[1] << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1; i < n; i++){
        cin >> arr[i];
        cnt[arr[i]]++;
    }
    solve();
};