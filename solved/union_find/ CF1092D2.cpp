/**
 * @Time : 2024/4/25-8:28 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 只能相邻且相等的两个数进行+1操作 至少要把所有数变成一开始的最大值
 * 那么先从最小的数开始考虑
 * 考虑连续一片最小的数 如果是奇数个 那么不管怎么操作 都有一个数剩下 无法增大 那答案就是no
 * 将这一片连续的数增大到min(leftNum, rightNum),与左边或者右边连成一片
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int n, m, id[N], l[N], r[N], sz[N];
vector<int> nums, pos;
vector<int> aux[N];

void scatter() {
    pos = nums;
    sort(pos.begin(), pos.end());
    pos.erase(unique(pos.begin(), pos.end()), pos.end());
    m = (int)pos.size();
}

int rk(int val) {
    return lower_bound(pos.begin(), pos.end(), val) - pos.begin();
}

int find(int p) {
    return id[p] == p ? p : id[p] = find(id[p]);
}
// 返回两个分量合并后 新分量的id
void connect(int p, int q) {
    p = find(p), q = find(q);
    if(p == q) return ;
    id[p] = q, sz[q] += sz[p]; // p合并到q 所以要维护q分量的信息
    l[q] = min(l[q], l[p]), r[q] = max(r[q], r[p]);
}

bool merge(vector<int>& arr) {
    for(int i = 0, k = arr.size(); i < k; ) {
        int j = i + 1;
        while(j < k) { // 先将位置相邻且大小一样的分量进行合并
            int p = find(arr[j - 1]), q = find(arr[j]);
            if(r[p] + 1 == l[q]) connect(p, q);
            else break;
            j++;
        }
        int p = find(arr[i]); // 查看当前分量（可能是已经合并过的了）
        if(sz[p] % 2 == 1 && sz[p] != n) return false; // 连通块大小为奇数 那么总会有一个数没法改变
        int lo = l[p], hi = r[p];
        if(lo == 0 && hi == n - 1) break; // 说明已经只剩一个连通块了
        int num1 = lo - 1 >= 0 ? nums[lo - 1] : INT_MAX;
        int num2 = hi + 1 < n ? nums[hi + 1] : INT_MAX;
        if(num1 < num2) connect(p, lo - 1); // 左边的数较小 要先通过+1操作与左边相等 并且变为同一个连通块
        else connect(p, hi + 1);
        i = j;
    }
    return true;
}

bool solve() {
    for(int i = 0; i < n; i++) { // 按数的大小分组 并且每一组都是从左到右
        int rank = rk(nums[i]);
        aux[rank].push_back(i);
    }
    for(int i = 0; i < m; i++) { // 先从最小的数开始考虑
        if(aux[i].empty()) continue;
        bool flag = merge(aux[i]);
        if(!flag) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 0; i < n; i++)
        id[i] = l[i] = r[i] = i;
    fill(sz, sz + n, 1);
    nums.assign(n, 0);
    for(int i = 0; i < n; i++)
        cin >> nums[i];
    scatter();
    cout << (solve() ? "YES" : "NO");
};