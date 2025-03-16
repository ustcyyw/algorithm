/**
 * @Time : 2025/3/15-11:49 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF557D 2000 dfs trick 分类讨论
 */
/*
  * trick : 用黑白染色法确定无向图中是否有奇数环 偶数环
  * 在dfs的时候 给结点按dfs的访问顺序重新编号
  * 当遇到已访问的结点时 当前结点和那个已访问的结点如果编号奇偶相同 则这是一个奇数个结点的环
  * 否则 是一个偶数个结点的环
  *
  * 可以简化地这样理解：
  * 现在讨论的两个结点 有一个共同的祖先，该祖先的编号无论奇偶
  * 如果两个结点编号奇偶性相同 这两个结点到该祖先的距离奇偶性也相同
  * 那么这两个路径之和为偶数 再加上这两个结点的当前边 环的长度就是奇数了（环的长度=环中结点个数）
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e5 + 5, mod = 1e9 + 7;
int T, n, m, flag = 0, cnt = 0, ids[N];
vector<int> graph[N];

void dfs(int v, int id, int& c1, int& c2) {
    if(id % 2 == 1) c1++;
    else c2++;
    ids[v] = id;
    for(int w : graph[v]) {
        if(ids[w]) {
            if(id % 2 == ids[w] % 2) flag = 1;
        } else dfs(w, id + 1, c1, c2);
    }
}

void solve() {
    vector<int> arr1, arr2;
    for(int i = 1; i <= n; i++) {
        if(ids[i] == 0) {
            int c1 = 0, c2 = 0;
            dfs(i, 1, c1, c2);
            cnt = max(c1 + c2, cnt);
            arr1.push_back(c1), arr2.push_back(c2);
        }
    }
    ll a1 = -1, a2 = 0;
    // 已经有奇数环的情况 那么就不用添加任何边了
    if(flag == 1) {
        a1 = 0, a2 = 1;
    } else if(cnt == 2) { // 只有孤立的一条边的情况 也就是分量最多2个结点 需要再任选一个结点 连两条边
        a1 = 2;
        for(int i = 0; i < arr1.size(); i++) {
            if(arr1[i] == 1 && arr2[i] == 1)
                a2 += n - 2;
        }
    } else { // 一个分量中有 >= 3 个结点，与trick同理 将同奇数、偶数编号的两点连起来 就能得到一个奇数长度的环
        a1 = 1;
        for(int i = 0; i < arr1.size(); i++) {
            ll c1 = arr1[i], c2 = arr2[i];
            if(c1 > 1) a2 += c1 * (c1 - 1) / 2;
            if(c2 > 1) a2 += c2 * (c2 - 1) / 2;
        }
    }
    cout << a1 << " " << a2;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T-- > 0) {
        cin >> n >> m;
        if(m == 0) { // 没有任何边 那就需要任选三个点 用三条边连起来
            cout << 3 << " " << (ll)n * (n - 1) * (n - 2) / 6;
            return 0;
        }
        for(int i = 1, v, w; i <= m; i++) {
            cin >> v >> w;
            graph[v].push_back(w), graph[w].push_back(v);
        }
        solve();
    }
}