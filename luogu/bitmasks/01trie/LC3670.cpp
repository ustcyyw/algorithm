/**
 * @Time : 2025/10/22-17:07
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3670 2276 位运算 trie树 01-trie树 贪心
 */
 /*
  * 就类似于 求数对的最大异或值的思路
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, D = 20, N = 7e4 + 5;

struct Node {
    Node *next[2];
};

class Trie {
    Node *root = new Node();
    Node* insert(Node* x, int v, int i) {
        if(x == nullptr)
            x = new Node();
        if(i == -1) return x;
        int k = (1 << i) & v ? 1 : 0;
        x->next[k] = insert(x->next[k], v, i - 1);
        return x;
    }

    int search(Node* x, int v, int i) {
        if(i == -1) return 0;
        int k = (1 << i) & v ? 1 : 0;
        if(k == 1) {
            return search(x->next[0], v, i + 1);
        } else {
            int temp = search(x->next[1], v, i + 1);
            if(temp != -1) return (1 << i) + temp;
            return search(x->next[0], v, i + 1);
        }
    }

public:
    void insert(int v) {
        root = insert(root, v, D);
    }

    int search(int v) {
        return search(root, v, D);
    }
};

class Solution {
public:
    long long maxProduct(vector<int>& nums) {
        Trie trie;
        ll ans = 0;
        for(int num : nums) {
            ll temp = trie.search(num);
            ans = max(ans, temp * num);
            trie.insert(num);
        }
        return ans;
    }
};