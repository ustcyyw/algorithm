/**
 * @Time : 2024/7/6-11:47 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1454F 双指针 线段树
 */
 /*
  * 中间的一段是取min min值等于max的值 max的值也是单调的
  * 有单调性 如果区间越大 min值越小
  * 双指针？
  * i增大 左区间范围小了 min的值增大 如果这个值大于max值 就得右移动j值 直到min(i,j-1) <= max
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, nums[N], x, y, z;
map<int, vector<int>> pre, suf;

#define ls x << 1
#define rs (x << 1) | 1
const int MIN_VAL = -2e9, MAX_VAL = 2e9;

class SegmentTree {
private:
    int n;
    vector<int> val;
    // 单点修改
    void add(int x, int l, int r, int pos, int v) {
        if(l == r) {
            val[x] = v;
            return ;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) add(ls, l, mid, pos, v);
        else add(rs, mid + 1, r, pos, v);
        val[x] = min(val[ls], val[rs]);
    }

    int search(int x, int l, int r, int a, int b) {
        if(a <= l && r <= b) return val[x];
        int mid = (l + r) >> 1, res = MAX_VAL;
        if(a <= mid) res = search(ls, l, mid, a, b);
        if(b > mid) res = min(res, search(rs, mid + 1, r, a, b));
        return res;
    }

public:
    SegmentTree(int n) {
        this-> n = n;
        val = vector(4 * (n + 1), MIN_VAL);
    }

    void add(int pos, int v) {
        add(1, 0, n, pos, v);
    }

    int search(int a, int b) {
        return search(1, 0, n, a, b);
    }
};

bool solve() {
    SegmentTree tree(n);
    for(int i = 1, val = nums[1]; i <= n; i++) {
        tree.add(i, nums[i]);
        val = max(val, nums[i]);
        pre[val].push_back(i);
    }
    for(int i = n, val = nums[n]; i >= 1; i--) {
        val = max(val, nums[i]);
        suf[val].push_back(i);
    }
    for(auto& p : pre) {
        int val = p.first;
        if(!suf.count(val)) continue;
        vector<int> &arr1 = p.second, &arr2 = suf[val];
        reverse(arr2.begin(), arr2.end());
        for(int i = 0, j = 0, n1 = arr1.size(), n2 = arr2.size(); i < n1; i++) {
            int lo = arr1[i] + 1;
            while(j < n2 && (lo > arr2[j] - 1 || tree.search(lo, arr2[j] - 1) > val))
                j++;
            if(j != n2 && lo <= arr2[j] - 1 && tree.search(lo, arr2[j] - 1) == val) {
                x = arr1[i], y = arr2[j] - 1 - x, z = n - x - y;
                return true;
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        pre = {}, suf = {};
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        if(solve()) cout << "YES\n" << x << " " << y << " " << z << "\n";
        else cout << "NO\n";
    }
};