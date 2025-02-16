/**
 * @Time : 2025/2/16-12:26 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : F665E 2100 位运算 trie树
 */
/*
  * 假设k是 0010110 截止到当前位置的xor值为x 前置位置的xor值为y
  * 令v = x ^ y >= k, 那么v
  * 可能是1开头的任何一个数
  * 可能是01开头的任何一个数
  * 可能是0011开头的任何一个数
  * 可能是0010111开头的任何一个数
  * 还要加上k本身
  * 知道了v的选择 就可以通过y = x ^ v逆向知道y对应的情况
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 5, mod = 1e9 + 7, D = 31;
ll T, n, k, aux[32][2], ans = 0;

struct Node {
    Node *next[2];
    int cnt = 0;
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

    int search(Node* x, int v, int i, int j) {
        if(x == nullptr) return 0;
        if(i == j) return x->cnt;
        int k = (1 << i) & v ? 1 : 0;
        return search(x->next[k], v, i - 1, j);
    }

public:
    void insert(int v) {
        root = insert(root, v, D);
    }

    int search(int v, int j) {
        return search(root, v, D, j);
    }
};

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T--) {
        cin >> n >> k;
        int m = 0;
        aux[0][0] = k, aux[0][1] = -1; // 预处理所有
        for(int i = D - 1; i >= 0; i--) {
            int t = 1 << i;
            if((k & t) == 0) {
                m++;
                aux[m][0] = k | t, aux[m][1] = i - 1;
            }
        }
        Trie trie;
        trie.insert(0);
        for(int i = 1, x = 0, num; i <= n; i++) {
            cin >> num;
            x ^= num;
            for(int i = 0; i <= m; i++)
                ans += trie.search(aux[i][0] ^ x, aux[i][1]);
            trie.insert(x);
        }
        cout << ans << "\n";
    }
};