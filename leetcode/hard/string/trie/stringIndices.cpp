/**
 * @Time : 2024/3/24-3:30 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛390 t4 字典树
 */
#include<bits/stdc++.h>
using namespace std;
/*
 * 假设两个字符串s和t的最长公共后缀长度是l
 * s[i, n-1] = t[j, m-1]，n - i = l，m - j = l
 * 但是s[i-1,n-1] != t[j-1,m-1]
 * 那么将两个字符串同时翻转 s[0, l - 1] = t[0, l - 1]，但是s[0,l] != t[0,l]....
 * 也就是说最长公共后缀就是将两个字符串翻转后的最长公共前缀 可以使用trie树
 */
struct Node {
    int len, idx;
    Node *next[26];
    Node() {
        memset(next, NULL, sizeof(next));
        len = INT_MAX;
    }
};

Node* insert(Node* x, string& s, int i, int idx) {
    if(x == nullptr) x = new Node();
    if(s.size() < x->len) {
        x->len = s.size();
        x->idx = idx;
    }
    if(i == s.size()) return x;
    x->next[s[i] - 'a'] = insert(x->next[s[i] - 'a'], s, i + 1, idx);
    return x;
}

int search(Node* x, string& s, int i) {
    if(i == s.size()) return x->idx;
    if(x->next[s[i] - 'a'] == nullptr) return x->idx;
    return search(x->next[s[i] - 'a'], s, i + 1);
}

class Solution {
public:
    vector<int> stringIndices(vector<string>& container, vector<string>& query) {
        Node* root = new Node();
        for(int i = 0; i < container.size(); i++) {
            string& word = container[i];
            reverse(word.begin(), word.end());
            root = insert(root, word, 0, i);
        }
        vector<int> res;
        for(string& word : query) {
            reverse(word.begin(), word.end());
            res.push_back(search(root, word, 0));
        }
        return res;
    }
};