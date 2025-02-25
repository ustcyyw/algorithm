/**
 * @Time : 2025/2/24-12:58 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 动态开点线段树
 */
#include<bits/stdc++.h>
using namespace std;

struct Node {
    int val, tag;
    Node *left, *right;
    Node() : val(0), tag(0), left(nullptr), right(nullptr) {}

    Node(int val) {
        this->val = val;
        tag = 0;
        left = nullptr;
        right = nullptr;
    }
};

class SegmentTree {
    Node* root;
    int L, R;
    SegmentTree(int l, int r) {
        L = l, R = r;
    }

    Node* add(Node* x, int l, int r, int a, int b, int v) {
        if(x == nullptr) x = new Node();
        if(a <= l && r <= b) {
            x->val = v, x->tag = v;
            return x;
        }
        down(x);
        int mid = (l + r) >> 1;
        if(mid >= a) x->left = add(x->left, l, mid, a, b, v);
        if(mid < b) x->right = add(x->right, mid + 1, r, a, b, v);
        update(x, l, r);
        return x;
    }

    void update(Node* x, int l, int r) {
        if (x->left == nullptr)
            x->left = new Node();
        if (x->right == nullptr)
            x->right = new Node();
        x->val = min(x->left->val, x->right->val); // 需要计算最小值
    }

    int search(Node* x, int l, int r, int a, int b) {
        if(x == nullptr) x = new Node();
        if(a <= l && r <= b) return x->val;
        down(x);
        int mid = (l + r) >> 1, ans = INT_MAX;
        if(mid >= a) ans = search(x->left, l, mid, a, b);
        if(mid < b) ans = min(ans, search(x->right, mid + 1, r, a, b));
        return ans;
    }

    void add(int a, int b, int v) {
        root = add(root, L, R, a, b, v);
    }

    int search(int a, int b) {
        return search(root, L, R, a, b);
    }
    // 示例的down函数 是更新区间上的值
    void down(Node* x){
        if(x->tag == 0) return;
        if(x->left == nullptr) x->left = new Node();
        if(x->right == nullptr) x->right = new Node();
        x->left->tag = x->tag; x->right->tag = x->tag;
        x->left->val = x->tag; x->right->val = x->tag;
        x->tag = 0;
    }
};

int main(){
    cout << 0 << endl;
}