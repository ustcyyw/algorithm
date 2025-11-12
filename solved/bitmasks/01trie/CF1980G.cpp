/**
 * @Time : 2024/12/4-2:39 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1980G 2300 位运算 01trie树
 */
/*
  * v和u之间连一条边，f是其lca
val[v] ^ val[f] ^ (val[w] ^ val[f])
= val[v] ^ val[w]
这是原本的异或值
还要加上累计的y操作，如果边数量为偶数 无影响，否则得再算上一个y

val[v] ^ val[w] ^ x ^ (y:0)
要找最大值 x ^ val[v]确定。 val[w] ^ (y:0) 不确定

depth[v] - depth[f] + depth[w] - depth[f] = depth[v] + depth[w] - 2depth[f]
2 * depth[f] 一定是偶数，
1. depth[v]和depth[w]奇偶性不同，depth[v] + depth[w]是奇数 整体答案是奇数
    此时v到w的路径上有奇数条路径 答案是 （x ^ val[v] ^ y) ^ val[w]
2. depth[v]和depth[w]奇偶性相同 整体答案是偶数
    此时v到w的路径上有偶数条路径 答案是 (x ^ val[v]) ^ val[w]
因此 如果depth[v]是偶数
    要去depth[w]为偶数的集合中 去查看x ^ val[v]和谁匹配能得出最大值
    要去depth[w]为奇数的集合中 去查看x ^ val[v] ^ y和谁匹配
    如果depth[v]是奇数 则反之
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5, mod = 1e9 + 7;
int T, n, q, depth[N], val[N], y;
vector<vector<vector<int>>> graph;

const int D = 30;
struct Node {
    Node *next[2];
    int cnt = 0;
    Node() {
        memset(next, NULL, sizeof(next));
    }
};

class Trie {
    Node *root = new Node();
    Node* insert(Node* x, int v, int i) {
        if(x == nullptr)
            x = new Node();
        x->cnt++;
        if(i == -1) return x;
        int k = (1 << i) & v ? 1 : 0;
        x->next[k] = insert(x->next[k], v, i - 1);
        return x;
    }

    int search(Node* x, int v, int i) {
        if(i == -1) return 0;
        int k = (1 << i) & v ? 1 : 0, other = (k + 1) % 2;
        if(x->next[other] != nullptr && x->next[other]->cnt > 0)
            return (1 << i) + search(x->next[other], v, i - 1);
        else if(x->next[k] != nullptr && x->next[k]->cnt > 0)
            return + search(x->next[k], v, i - 1);
        return 0;
    }

    Node* remove(Node* x, int v, int i) {
        if(x == nullptr) return nullptr;
        x->cnt--;
        int k = (1 << i) & v ? 1 : 0;
        x->next[k] = remove(x->next[k], v, i - 1);
        return x;
    }

public:
    void insert(int v) {
        root = insert(root, v, D);
    }

    int search(int v) {
        return search(root, v, D);
    }

    void remove(int v) {
        root = remove(root, v, D);
    }
};

void dfs(int v, int f, int xorv) {
    depth[v] = f == -1 ? 0 : depth[f] + 1;
    val[v] = xorv;
    for(auto& edge : graph[v]) {
        int w = edge[0], t = edge[1];
        if(w == f) continue;
        dfs(w, v, xorv ^ t);
    }
}

void solve(Trie& tree1, Trie& tree2, int v, int x) {
    int v1 = x ^ val[v], v2 = x ^ val[v] ^ y;
    if(depth[v] % 2 == 0) {
        tree2.remove(val[v]);
        cout << max(tree2.search(v1), tree1.search(v2)) << " ";
        tree2.insert(val[v]);
    } else {
        tree1.remove(val[v]);
        cout << max(tree1.search(v1), tree2.search(v2)) << " ";
        tree1.insert(val[v]);
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n >> q;
        graph.assign(n + 1, {}), y = 0;
        for(int i = 1, a, b, w; i < n; i++) {
            cin >> a >> b >> w;
            graph[a].push_back({b, w}), graph[b].push_back({a, w});
        }
        dfs(1, -1, 0);
        Trie tree1, tree2;
        for(int i = 1; i <= n; i++) {
            if(depth[i] % 2 == 0) tree2.insert(val[i]);
            else tree1.insert(val[i]);
        }
        char ope;
        for(int i = 1, v1, v2; i <= q; i++) {
            cin >> ope >> v1;
            if(ope == '^') y ^= v1;
            else {
                cin >> v2;
                solve(tree1, tree2, v1, v2);
            }
        }
        cout << "\n";
    };
};