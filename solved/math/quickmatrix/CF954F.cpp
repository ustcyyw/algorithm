/**
 * @Time : 2025/3/19-11:29 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF954F 2100 动态规划 矩阵快速幂 差分
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e4 + 15, mod = 1e9 + 7;
ll T, n, m, a[N], ls[N], rs[N], arr[3][3 * N], status[3 * N];
int base[3][3] = {{1, 1, 0}, {1, 1, 1}, {0, 1, 1}};
vector<ll> pos;
vector<vector<ll>> mp[8];

int find(ll val) {
    return lower_bound(pos.begin(), pos.end(), val) - pos.begin();
}

vector<vector<ll>> matrixMul(vector<vector<ll>>& A, vector<vector<ll>>& B){
    int N = A.size(), M = B[0].size(), K = A[0].size();
    vector<vector<ll>> ans(N, vector(M, 0ll));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            for(int k = 0; k < K; k++)
                ans[i][j] = (ans[i][j] + (A[i][k] * B[k][j]) % mod) % mod;
        }
    }
    return ans;
}
vector<vector<ll>> quickPower(vector<vector<ll>> a, ll b){
    int n = a.size(); // 能进行快速幂的矩阵 是一个方阵
    vector<vector<ll>> ans(n, vector(n, 0ll));
    for(int i = 0; i < n; i++)
        ans[i][i] = 1;
    while (b != 0){
        if((b & 1) == 1) ans = matrixMul(ans , a);
        a = matrixMul(a, a);
        b >>= 1ll;
    }
    return ans;
}

// s标识三行中哪一行有障碍物
void get_matrix(int s) {
    vector<vector<ll>> matrix(3, vector(3, 0ll));
    for(int i = 0; i < 3; i++) {
        if(s & (1 << i)) continue; // s中某一位为1 表示该行有障碍物 那么矩阵相应的列系数全为0
        for(int j = 0; j < 3; j++)
            matrix[j][i] = base[i][j];
    }
    mp[s] = matrix;
}

void solve() {
    vector<vector<ll>> ans = {{0, 1, 0}};
    for(int i = 1; i < pos.size(); i++) {
        ll lo = pos[i - 1], hi = pos[i], p = hi - lo;
        vector<vector<ll>> b = quickPower(mp[status[i]], p);
        ans = matrixMul(ans, b);
    }
    cout << ans[0][1];
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    pos.push_back(1), pos.push_back(m);
    for(int i = 1; i <= n; i++) {
        cin >> a[i] >> ls[i] >> rs[i];
        a[i]--;
        pos.push_back(ls[i] - 1), pos.push_back(rs[i]);
    }
    sort(pos.begin(), pos.end());
    pos.erase(unique(pos.begin(), pos.end()), pos.end());
    for(int i = 1; i <= n; i++) {
        int idx = a[i], l = find(ls[i]), r = find(rs[i]);
        arr[idx][l]++, arr[idx][r + 1]--;
    }
    for(int i = 1; i < pos.size(); i++) {
        int s = 0;
        for(int j = 0; j < 3; j++) {
            arr[j][i] += arr[j][i - 1];
            if(arr[j][i]) s |= 1 << j;
        }
        status[i] = s;
    }
    for(int i = 0; i < 8; i++)
        get_matrix(i);
    solve();
}