/**
 * @Time : 2024/1/3-12:45 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 每个#都等概率被修改为. 因此求数学期望时分母都是一样的 等于#的数量cnt
 * 那么只需要将 每一个#替换为.后连通分量数之和求出来，除以cnt就是答案
 * 涉及到连通性 并且是去掉一个点 容易想到和tarjan算法的割点相关
 *
 * 如果不改变任何字符，通过dfs找到所有连通分量，记原本的连通分量数目为id
 * 对于每一个# 看将其替换为.后 连通分量数目的变化
 * 那么最终连通分量数之和 = id * cnt + (sum of change)
 *
 * 1.#是一个孤立的点 去掉他 会让连通分量数目-1
 * 2.#不是割点 那么去掉他 对连通分量数目没有影响
 * 3.#是割点，去掉他 会使连通分量数目增加，但是增加多少呢
 *      得从tarjan的本质 dfs搜索树入手。回想两类割点
 *      root：有两个及以上的子结点，那么该根结点是割点，有cc个子结点 去掉它就会新增cc-1个连通分量
 *      非root：有儿子结点 并且存在low[son] >= dfn[x]就是割点
 *      存在多少个子结点满足low[son] >= dfn[x]，去掉它就会新增多少个连通分量
 *      因为dfs搜索树中的不同子结点本身不连通，他们又没法回溯到x的祖先 去掉x后就独立成别的分量了
 */
#include<bits/stdc++.h>
using namespace std;

const int N = 1e3 + 5, mod = 998244353, dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};
int n, m, id, cnt, grid[N][N]; // nodes[i]表示去掉结点i 会新增的连通分量数
long long total;
unordered_map<int, vector<int>> graph;

void tarjan() {
    vector<int> dfn((n + 1) * m + 1, -1), low((n + 1) * m + 1, INT_MAX);
    int time = 1;
    function<void(int, int)> dfs = [&](int v, int f) -> void {
        dfn[v] = low[v] = time++;
        int cc = 0;
        for (int w: graph[v]) {
            if (dfn[w] == -1) {
                cc++, dfs(w, v);
                low[v] = min(low[v], low[w]);
                if(f != -1 && low[w] >= dfn[v]) total++;
            } else if (w != f)
                low[v] = min(low[v], dfn[w]);
        }
        if (f == -1 && cc > 1) total += cc - 1;
    };
    for (int i = 1; i <= n; i++) {
        for(int j = 1; j <= m; j++) {
            if(grid[i][j] && dfn[i * m + j] == -1)
                dfs(i * m + j, -1);
        }
    }
}
//找到原本的图有多少个连通分量，并且在这个过程中判断是否有孤立的点 去掉他 会让连通分量数目-1
void group() {
    vector<vector<bool>> marked(n + 2, vector(m + 2, false));
    function<int(int, int)> dfs = [&](int i, int j) -> int {
        marked[i][j] = true;
        int ans = 1;
        for (int k = 0; k < 4; k++) {
            int x = i + dx[k], y = j + dy[k];
            if (!grid[x][y] || marked[x][y]) continue;
            ans += dfs(x, y);
        }
        return ans;
    };
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if(!marked[i][j] && grid[i][j]) {
                id++;
                if(dfs(i, j) == 1) total -= 1;
            }
        }
    }
}

long long q_pow(int a, int b){
    long long res = 1, temp = a;
    while (b != 0){
        if((b & 1) == 1) res = res * temp % mod;
        temp = temp * temp % mod;
        b >>= 1;
    }
    return res;
}

void solve() {
    total += (long long)cnt * id;
    long long inv = q_pow(cnt, mod - 2);
    cout << total % mod * inv % mod << endl;
}

int main() {
    cin >> n >> m;
    for (int i = 0; i < N; i++)
        memset(grid[i], 0, sizeof(grid[i]));
    graph = {}, cnt = 0, id = 0, total = 0;
    string line;
    for (int i = 1; i <= n; i++) {
        cin >> line;
        for (int j = 0; j < m; j++)
            grid[i][j + 1] = line[j] == '#';
    }
    group();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (!grid[i][j]) continue;
            cnt++;
            int v = i * m + j;
            if (!graph.count(v)) graph[v] = {};
            for (int k = 0; k < 4; k++) {
                int x = i + dx[k], y = j + dy[k];
                if (grid[x][y]) graph[v].push_back(x * m + y);
            }
        }
    }
    tarjan();
    solve();
}