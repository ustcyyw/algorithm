/**
 * @Time : 2024/4/8-11:06 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 差分 离散化
 */
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N = 1e6 + 5;
int n, k, m, arr[N][2];
vector<int> pos;

int find(int val) {
    return lower_bound(pos.begin(), pos.end(), val) - pos.begin();
}

void solve() {
    m = pos.size();
    vector<int> aux(m + 1, 0);
    for(int i = 0; i < n; i++) {
        int lo = find(arr[i][0]), hi = find(arr[i][1]);
        aux[lo]++, aux[hi + 1]--;
    }
    vector<vector<int>> ans;
    for(int i = 0, lo = INT_MIN, sum = 0; i < m; i++) {
        sum += aux[i];
        if(sum >= k) {
            if(lo == INT_MIN) lo = pos[i];
        } else if(lo != INT_MIN){
            ans.push_back({lo / 2, pos[i - 1] / 2});
            lo = INT_MIN;
        }
    }
    cout << ans.size() << "\n";
    for(auto& p : ans)
        cout << p[0] << " " << p[1] << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k;
    for(int i = 0, l, r; i < n; i++) {
        cin >> l >> r;
        arr[i][0] = 2 * l, arr[i][1] = 2 * r;
        pos.push_back(2 * l), pos.push_back(2 * r), pos.push_back(2 * r + 1);
    }
    sort(pos.begin(), pos.end());
    pos.erase(unique(pos.begin(), pos.end()), pos.end());
    solve();
};