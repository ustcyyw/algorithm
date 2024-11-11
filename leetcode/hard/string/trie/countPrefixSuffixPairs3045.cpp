/**
 * @Time : 2024/2/28-9:35 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 使用z函数来找相同的前缀、后缀
 * 使用trie树来查找和插入
 * 关键在于 在插入过程中通过z函数判断 前缀和后缀是否相同 如果相同将这个前缀进行计数
 * 在找(i,j)对时，对words[i]进行查找 看它对应的前缀计数是多少
 */
#include<bits/stdc++.h>
using namespace std;
const int R = 26;
struct Node {
    int cnt;
    Node *next[R];
    Node() {
        memset(next, NULL, sizeof(next));
        cnt = 0;
    }
};

class Trie {
    Node *root = new Node();
    Node* insert(Node* x, string& s, vector<int>& z,int i) {
        if(x == nullptr)
            x = new Node();
        if(i == s.size()) return x;
        x->next[s[i] - 'a'] = insert(x->next[s[i] - 'a'], s, z, i + 1);
        // 重点 前缀和后缀相同 将这个前缀进行计数
        if(z[s.size() - i - 1] == i + 1) x->next[s[i] - 'a']->cnt++;
        return x;
    }

    int search(Node* x, string& s, int i) {
        if(x == nullptr) return 0;
        if(i == s.size()) return x->cnt;
        return search(x->next[s[i] - 'a'], s, i + 1);
    }
public:
    void insert(string& s, vector<int>& z) {
        root = insert(root, s, z, 0);
    }

    int search(string& s) {
        return search(root, s, 0);
    }
};

class Solution {
public:
    long long countPrefixSuffixPairs(vector<string>& words) {
        long long res = 0;
        Trie trie;
        for(int i = words.size() - 1; i >= 0; i--) {
            string& s = words[i];
            res += trie.search(s);
            vector<int> z = z_function(s);
            trie.insert(s, z);
        }
        return res;
    }

    vector<int> z_function(string& s){
        int n = s.size();
        vector<int> z(n, 0);
        z[0] = n;
        for(int i = 1, l = 0, r = 0; i < n; i++){
            if(i <= r) z[i] = min(z[i - l], r - i + 1);
            while (i + z[i] < n && s[i + z[i]] == s[z[i]]) z[i]++;
            if(i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
        }
        return z;
    }
};