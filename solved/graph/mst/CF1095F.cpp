/**
 * @Time : 2024/4/24-12:41 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 最小生成树
  * 用prim算法 选择横切边 在树中的结点 与树外结点的最小边
  * 要么是特殊边 要么是树中结点最小值和树外结点最小值 二选一
  * 树中结点与树外结点：树中的那个一定是值最小的结点，树外则选择还未被选择的点中最小的
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int n, m, start = -1, marked[N];
ll nums[N];
vector<vector<ll>> edges[N];

struct cmp1 {
    bool operator()(int &i, int &j) {
        return nums[i] - nums[j] >= 0; // cpp 中优先队列是大顶堆 要得到小顶堆 不等号方向要反着
    }
};

priority_queue<int, vector<int>, cmp1> nodes; // 记录不在树中的结点的最小值

struct cmp2 {
    bool operator()(vector<ll> &a, vector<ll> &b) {
        return a[1] - b[1] >= 0; // cpp 中优先队列是大顶堆 要得到小顶堆 不等号方向要反着
    }
};

priority_queue<vector<ll>, vector<vector<ll>>, cmp2> spe; // 树中结点的特殊边

void relax(int v) {
    marked[v] = 1;
    for(auto& edge : edges[v]) {
        int w = edge[0];
        if(!marked[w]) spe.push(edge);
    }
}

pair<ll, ll> pick() {
    while(!nodes.empty() && marked[nodes.top()])
        nodes.pop();
    while(!spe.empty() && marked[spe.top()[0]])
        spe.pop();
    ll w1 = nodes.top(), len1 = nums[start] + nums[nodes.top()];
    if(spe.empty()) return make_pair(w1, len1);
    ll w2 = spe.top()[0], len2 = spe.top()[1];
    return len1 <= len2 ? make_pair(w1, len1) : make_pair(w2, len2);
}

void solve() {
    ll cnt = 1, ans = 0;
    relax(start);
    while(cnt < n) {
        pair<int, ll> p = pick();
        relax(p.first), ans += p.second;
        cnt++;
    }
    cout << ans;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        cin >> nums[i];
        if(start == -1 || nums[start] > nums[i])
            start = i;
    }
    for(int i = 1; i <= n; i++)
        nodes.push(i);
    for(ll i = 1, a, b, w; i <= m; i++) {
        cin >> a >> b >> w;
        edges[a].push_back({b, w}), edges[b].push_back({a, w});
    }
    solve();
};