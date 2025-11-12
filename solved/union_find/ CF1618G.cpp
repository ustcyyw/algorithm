/**
 * @Time : 2024/7/22-7:36 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1618G 并查集套路 离线查询
 */
 /*
  * 每个查询互相独立 并且k和置换关系有单调性 k越大 置换的可能越大 离线查询
  * 能置换的元素构成一个连通分量 想到了使用并查集
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, m, Q, id[2 * N], sz[2 * N];
ll base = 0ll, ans[N], sum[2 * N];
vector<vector<int>> queries, nums, diff;

void init() {
    nums.push_back({0, 0});
    sort(nums.begin(), nums.end());
    sort(queries.begin(), queries.end());
    for(int i = 1; i <= n + m; i++) {
        id[i] = i;
        int num = nums[i][0], flag = nums[i][1];
        if(flag == 1) sz[i] = 1, base += num;
        sum[i] = sum[i - 1] + num;
        if(i > 1) diff.push_back({num - nums[i - 1][0], i});
    }
    sort(diff.begin(), diff.end());
}

int find(int p) {
    return id[p] == p ? p : id[p] = find(id[p]);
}

// 将q分量合并到p分量中
void merge(int q, int p) {
    base -= sum[p] - sum[p - sz[p]];
    base -= sum[q] - sum[q - sz[q]];
    id[q] = p, sz[p] += sz[q];
    base += sum[p] - sum[p - sz[p]];
}

void connect(int p, int q) {
    p = find(p), q = find(q);
    if(p == q) return;
    if(p > q) merge(q, p);
    else merge(p, q);
}

void solve() {
    int j = 0;
    for(auto& query : queries) {
        int k = query[0], i = query[1];
        while(j < diff.size() && diff[j][0] <= k) {
            int p = diff[j][1], q = p - 1;
            connect(p, q);
            j++;
        }
        ans[i] = base;
    }
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m >> Q;
    for(int i = 1, num; i <= n; i++) {
        cin >> num;
        nums.push_back({num, 1});
    }
    for(int i = 1, num; i <= m; i++) {
        cin >> num;
        nums.push_back({num, 2});
    }
    for(int i = 1, k; i <= Q; i++) {
        cin >> k;
        queries.push_back({k, i});
    }
    init();
    solve();
    for(int i = 1; i <= Q; i++)
        cout << ans[i] << "\n";
};