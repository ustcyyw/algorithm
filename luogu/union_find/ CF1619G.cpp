/**
 * @Time : 2024/7/24-10:08 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1619G 并查集 + 二分答案
 */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 1e9 + 7;
typedef long long ll;
int T, n, k, id[N], minTime[N], marked[N];
map<int, vector<vector<int>>> row, col;

int find(int p) {
    return id[p] == p ? p : id[p] = find(id[p]);
}

void connect(int p, int q) {
    p = find(p), q = find(q);
    if(p == q) return ;
    id[p] = q;
    minTime[q] = min(minTime[q], minTime[p]);
}

void merge(vector<vector<int>>& arr) {
    sort(arr.begin(), arr.end());
    for(int i = 0, m = arr.size(), j; i < m; ) {
        j = i + 1;
        while(j < m && arr[j][0] - arr[j - 1][0] <= k) {
            connect(arr[j][1], arr[i][1]);
            j++;
        }
        i = j;
    }
}

bool check(vector<int>& times, int time) {
    int i = (--upper_bound(times.begin(), times.end(), time)) - times.begin();
    return time + 1 + i + 1 >= times.size();
}

int solve() {
    for(auto& p : row)
        merge(p.second);
    for(auto& p : col)
        merge(p.second);
    vector<int> times;
    for(int i = 1; i <= n; i++) {
        int p = find(i);
        if(!marked[p])
            marked[p] = 1, times.push_back(minTime[p]);
    }
    sort(times.begin(), times.end());
    if(times.back() == 0 || times.size() == 1) return 0;
    int lo = 0, hi = times.back();
    while(lo < hi) {
        int mid = (lo + hi) >> 1;
        if(check(times, mid)) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> k;
        row = {}, col = {};
        fill(marked, marked + n + 1, 0);
        for(int i = 1, x, y, time; i <= n; i++) {
            cin >> x >> y >> time;
            row[x].push_back({y, i}), col[y].push_back({x, i});
            id[i] = i, minTime[i] = time;
        }
        cout << solve() << "\n";
    }
};