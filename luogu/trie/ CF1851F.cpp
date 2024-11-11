/**
 * @Time : 2024/6/29-1:48 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 分别异或 然后求与运算最大值
 * 最高位 想办法弄出1
 * x的最高位是0，要求ai和aj的最高位是1
 * x的最高位是1，要求ai和aj的最高位是0
 * 所以要找到2个数最长公共前缀 让高位尽可能是都是1
 * 剩下的低位就看两个数这一位如果相同 就让x取相反，否则x随意
 * 可以用trie树找最长公共前缀。
 *
 * 但更好的解决办法是 根据二进制的性质，从小到大排序后相邻的两个数一定拥有最长的公共前缀
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
typedef long long ll;
int T, n, k, nums[N], len, a, b, c, ans;

struct Node {
    int cnt;
    Node *next[2];
    vector<int> idx;
    Node(){
        memset(next, NULL, sizeof(next));
        cnt = 0;
    }
};
vector<Node*> nodes; // 记录最长前缀所在的结点

class Trie {
    Node *root = new Node();
    Node* insert(Node* x, int& num, int i, int id) {
        if(x == nullptr)
            x = new Node();
        x->cnt++;
        if(i == -1) {
            x->idx.push_back(id);
            return x;
        }
        int mask = (num >> i) & 1;
        x->next[mask] = insert(x->next[mask], num, i - 1, id);
        return x;
    }

    void maxPre(Node* x, int pre, int i) {
        if(k - i >= len) {
            if(len < k - i) nodes = {};
            len = k - i, nodes.push_back(x);
        }
        if(x == nullptr || i == -1) return;
        if(x->next[0] != nullptr && x->next[0]->cnt >= 2)
            maxPre(x->next[0], pre, i - 1);
        if(x->next[1] != nullptr && x->next[1]->cnt >= 2)
            maxPre(x->next[1], pre + (1 << i), i - 1);
    }

public:
    void insert(int num, int i, int id) {
        root = insert(root, num, i, id);
    }

    void maxPre(int num, int i) {
        maxPre(root, num, i);
    }

    int search(Node* x) {
        if(x->next[0] == nullptr && x->next[1] == nullptr) return x->idx[0];
        if(x->next[0] != nullptr) return search(x->next[0]);
        else return search(x->next[1]);
    }
};

int get_x(int num1, int num2) {
    int x = 0;
    for(int i = 0; i < k; i++) {
        int t = (1 << i), t1 = num1 & t, t2 = num2 & t;
        if(t1 == 0 && t2 == 0) x |= t;
    }
    return x;
}

void solve() {
    Trie trie;
    for(int i = 1; i <= n; i++)
        trie.insert(nums[i], k - 1, i);
    trie.maxPre(0, k);
    for(auto & node : nodes) {
        int i, j;
        if(node->next[0] == nullptr)
            i = node->idx[0], j = node->idx[1];
        else i = trie.search(node->next[0]), j = trie.search(node->next[1]);
        int num1 = nums[i], num2 = nums[j], x = get_x(num1, num2);
        int temp = (num1 ^ x) & (num2 ^ x);
        if(temp > ans) {
            ans = temp;
            a = i, b = j, c = x;
        }
    }
    cout << a << " " << b << " " << c << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> k;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        nodes = {}, len = -1, ans = -1;
        solve();
    }
};