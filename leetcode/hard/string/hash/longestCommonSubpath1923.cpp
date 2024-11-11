/**
 * @Time : 2023/11/18-5:04 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 字符串双hash
 */
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 5;
int p[2] = {29, 31};
int mod[2] = {int(1e9 + 9), 998244353};
int x[2][N];
int init = []() -> int {
    x[0][0] = x[1][0] = 1;
    for(int k = 0; k < 2; k++) {
        for (int i = 1; i < N; i++) {
            x[k][i] = 1ll * x[k][i - 1] * p[k] % mod[k];
        }
    }
    return 0;
}();

class Solution {
public:
    vector<vector<vector<int>>> hs;

    int longestCommonSubpath(int n, vector<vector<int>> &paths) {
        for (auto &path: paths)
            hs.push_back(get_hash(path));
        int lo = 0, hi = INT_MAX;
        for (auto &path: paths)
            hi = min(hi, (int) path.size());
        while (lo < hi) {
            int mid = (lo + hi + 1) >> 1;
            if (check(mid)) lo = mid;
            else hi = mid - 1;
        }
        return lo;
    }

    bool check(int len) {
        unordered_set<ll> all, cur;
        for (int k = 0; k < hs.size(); k++) {
            auto& h = hs[k];
            cur.clear();
            for (int i = 0; i + len - 1 < h[0].size() - 1; i++) {
                ll t = hash(h, i, i + len - 1);
                // 当前是第一轮条路径，或者只有先前存在的子路径 现在才有必要放进去
                if(k == 0 || all.count(t))
                    cur.insert(t);
            }
            if(cur.empty()) return false; // 已经找不到公共的子路径了
            swap(cur, all);
        }
        return true;
    }

    static ll hash(vector<vector<int>> &h, int l, int r) {
        vector<ll> res(2, 0);
        for (int k = 0; k < 2; k++) {
            ll t = (h[k][r + 1] - 1ll * h[k][l] * x[k][r - l + 1]) % mod[k];
            res[k] = (t + mod[k]) % mod[k];
        }
        return res[0] * (ll)1e6 + res[1];
    }

    static vector<vector<int>> get_hash(vector<int>& path) {
        int n = path.size();
        vector<vector<int>> h(2, vector(n + 1, 0));
        x[0][0] = x[1][0] = 1;
        for(int k = 0; k < 2; k++) {
            for (int i = 1; i <= n; i++) {
                h[k][i] = (1ll * h[k][i - 1] * p[k] + path[i - 1]) % mod[k];
            }
        }
        return h;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}