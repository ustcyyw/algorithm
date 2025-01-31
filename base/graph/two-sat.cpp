/**
 * @Time : 2025/1/30-2:58 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 2sat 强连通分量 scc 拓扑排序
 */
 /*
  * 处理的问题类型
  * 有一组变量 一共n个 这组变量只能取0/1两个逻辑值
  * 0/1两个逻辑值也可以认为是描述一种二元可能性，比如人的性别，石头落在边界的左边还是右边等
  * 然后有m个逻辑约束条件 比如 x1 | x2 = 1, x3 & x4 = 0 之类的
  * 给定这些约束条件 可以得出一些逻辑推理
  * x1 | x2 = 1， 我们可以得出 (x1 = 0 => x2 = 1) (x2 = 0 => x1 = 1)
  * x3 & x4 = 0， 我们可以得出 (x3 = 1 => x4 = 0) (x4 = 1 => x3 = 0)
  * 这些逻辑推理关系 是单向但 由左推出右 就像一个有向边
  * 由此我们可以进行建图 同一个变量因为有0/1两个值 就需要用两个结点去描述同一个变量
  * 为了方便 用结点i表示xi = 1，用结点i+n表示xi = 0
  * (特别注意这里的n是指变量的数目！)
  * 构建出有向图之后 因为逻辑推理是有方向性的 和拓扑排序一致
  * 但是有向图中可能有强连通分量 那么就需要先使用tarjan进行缩点
  * 在缩点后的新图中
  * 1. 如果i和i+n的颜色相同 在同一个强连通分量。意味着 xi = 0 => xi = 1 并且 xi = 1 => xi = 0
  * 出现了逻辑矛盾 就说明没法办法找到一组x的取值 满足m个条件
  * 2. i和i+n必须取拓扑排序靠后的结点。因为取拓扑序小的那个 就会出现
  * xi = 0 => xi = 1 或者 xi = 1 => xi = 0的情况 也出现了矛盾
  * 不过不需要再进行一次拓扑排序了。因为在tarjan算法的染色过程中 是先将dfs序靠后的进行上色
  * 也就是说 color[j] < color[i]，说明j的dfs序靠后 在拓扑序中j靠后
  * 那么如果 color[i] < color[i + n], i的拓扑序靠后 因此要取xi = 1
  * 反之 color[i + n] < color[i], i+1的拓扑序靠后 因此要取xi = 0
  *
  * 关于处理的问题的补充
  * 从逻辑推理的角度来说 并非是直接的逻辑表达式才能得出确定的推理
  * 只要是问变量的0/1取值 能根据题目条件得出确定的变量的逻辑推导关系
  * 一系列形式为 xi[0/1] => xj[0/1] （i != j） 的逻辑推导 就能建图
  * 例如 https://codeforces.com/contest/27/problem/D
  */

 /*
  * 模板题 https://www.luogu.com.cn/problem/P4782
  */
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5, M = 2 * N;
int n, dfn[M], low[M], color[M], onSta[M];
vector<int> graph[M];

void add(int x1, int v1, int x2, int v2) {
    if(v1 == 0 && v2 == 0) { // x1为假 或者 x2为假
        graph[x1].push_back(x2 + n);
        graph[x2].push_back(x1 + n);
    } else if(v1 == 1 && v2 == 1) { // x1为真 或者 x2为真
        graph[x1 + n].push_back(x2);
        graph[x2 + n].push_back(x1);
    } else if(v1 == 1 && v2 == 0) { // x1为真 或者 x2为假
        graph[x1 + n].push_back(x2 + n);
        graph[x2].push_back(x1);
    } else { // x1为假 或者 x2为真
        graph[x1].push_back(x2);
        graph[x2 + n].push_back(x1 + n);
    }
}

void scc() {
    int cc = 0, time = 1; // 分别表示颜色和时间戳
    stack<int> stack;
    function<void(int)> dfs = [&](int v) -> void {
        dfn[v] = low[v] = ++time;
        onSta[v] = 1, stack.push(v);
        for(int w : graph[v]) {
            if(dfn[w] == 0) {
                dfs(w);
                low[v] = min(low[v], low[w]);
            } else if(onSta[w])
                low[v] = min(low[v], dfn[w]);
        }
        if(dfn[v] == low[v]) {
            color[v] = ++cc;
            int temp = -1;
            while(temp != v) {
                temp = stack.top();
                color[temp] = cc; // 标记该结点的颜色
                onSta[temp] = 0, stack.pop();
            }
        }
    };
    for(int i = 0; i < n; i++)
        if(dfn[i] == 0) dfs(i);
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    cin >> n;
    for(int i = 1, x1, v1, x2, v2; i <= n; i++) {
        cin >> x1 >> v1 >> x2 >> v2;
        add(x1, v1, x2, v2);
    }
    scc();
    for(int i = 1; i <= n; i++) {
        if(color[i] == color[i + n]) {
            cout << "IMPOSSIBLE";
            return 0;
        }
    }
    cout << "POSSIBLE\n";
    for(int i = 1; i <= n; i++)
        cout << (color[i] < color[i + n]) << " ";
};