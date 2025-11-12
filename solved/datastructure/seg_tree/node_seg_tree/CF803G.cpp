/**
 * @Time : 2025/2/24-9:38 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF803G 2300 数据结构 动态开点线段树 st表
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e5 + 5, M = 400;
int n, k, q;

class STable {
public:
    int n, m;
    vector<vector<int>> dp;

    int f(int num1, int num2) {
        return min(num1, num2);
    }

    void init(vector<int>& nums) {
        n = nums.size(), m = log2(n);  // 计算 log2(n)
        dp.assign(n, vector<int>(m + 1, 0));
        for (int i = 0; i < n; i++) {
            dp[i][0] = nums[i];
        }
        for (int j = 1; j <= m; j++) {
            int pj = 1 << (j - 1);
            for (int i = 0; i + pj < n; i++) {
                dp[i][j] = f(dp[i][j - 1], dp[i + pj][j - 1]);
            }
        }
    }

    int search(int l, int r) {
        int len = r - l + 1, j = log2(len);
        return f(dp[l][j], dp[r - (1 << j) + 1][j]);
    }

    int get_min(int l, int r) {
        if (l > r) return INT_MAX;
        if (r - l + 1 >= n) return search(0, n - 1);
        int lo = l % n, hi = r % n;
        if (hi >= lo) return search(lo, hi);
        return min(search(lo, n - 1), search(0, hi));
    }
};

STable st;

class Node {
public:
    int val, tag;
    Node* left;
    Node* right;

    Node() : val(0), tag(0), left(nullptr), right(nullptr) {}

    Node(int l, int r) {
        val = st.get_min(l, r);
        tag = 0;
        left = nullptr;
        right = nullptr;
    }
};

class SegmentTree {
public:
    Node* root;
    int L, R;

    SegmentTree(int l, int r) : L(l), R(r) {
        root = new Node(l, r);
    }

    void add(int a, int b, int v) {
        root = add(root, L, R, a, b, v);
    }

    int search(int a, int b) {
        return search(root, L, R, a, b);
    }

private:
    Node* add(Node* x, int l, int r, int a, int b, int v) {
        if (x == nullptr) x = new Node(l, r);
        if (a <= l && r <= b) {
            x->val = v;
            x->tag = v;
            return x;
        }
        down(x);
        int mid = (l + r) >> 1;
        if (mid >= a) x->left = add(x->left, l, mid, a, b, v);
        if (mid < b) x->right = add(x->right, mid + 1, r, a, b, v);
        update(x, l, r);
        return x;
    }

    int search(Node* x, int l, int r, int a, int b) {
        if (x == nullptr) x = new Node(l, r);
        if (a <= l && r <= b) return x->val;
        down(x);
        int mid = (l + r) >> 1;
        int ans = INT_MAX;
        if (mid >= a) ans = search(x->left, l, mid, a, b);
        if (mid < b) ans = min(ans, search(x->right, mid + 1, r, a, b));
        return ans;
    }

    void update(Node* x, int l, int r) {
        int mid = (l + r) >> 1;
        if (x->left == nullptr)
            x->left = new Node(l, mid);
        if (x->right == nullptr)
            x->right = new Node(mid + 1, r);
        x->val = min(x->left->val, x->right->val); // 需要计算最小值
    }

    void down(Node* x) {
        if (x->tag == 0) return;
        if (x->left == nullptr) x->left = new Node();
        if (x->right == nullptr) x->right = new Node();
        x->left->tag = x->tag, x->right->tag = x->tag;
        x->left->val = x->tag, x->right->val = x->tag;
        x->tag = 0;
    }
};

int main() {
    cin >> n >> k;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) {
        cin >> nums[i];
    }
    st.init(nums);
    SegmentTree tree(0, n * k - 1);
    cin >> q;
    for (int i = 0, t, l, r, x; i < q; i++) {
        cin >> t >> l >> r;
        l--, r--;
        if (t == 1) {
            cin >> x;
            tree.add(l, r, x);
        } else cout << tree.search(l, r) << endl;
    }
    return 0;
}