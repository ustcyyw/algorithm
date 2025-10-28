#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 1e5 + 5;

ll qPow(ll x, ll y) {
    ll ans = 1;
    while (y) {
        if (y & 1) ans = ans * x % mod;
        y >>= 1;
        x = x * x % mod;
    }
    return ans;
}
// 预处理逆元
ll invF[N];
int init = []() -> int {
    for (int i = 1; i < N; i++)
        invF[i] = qPow(i, mod - 2);
    return 0;
}();

class Solution {
public:
    vector<vector<ll>> arr;
    int xorAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size(), m = sqrt(n);
        arr.assign(m, {});
        vector<ll> base(n, 1ll);
        for(auto& query : queries) {
            int l = query[0], r = query[1], k = query[2], v = query[3];
            if(k >= m) {
                for(int i = l; i <= r; i += k)
                    base[i] = base[i] * v % mod;
            } else mul(l, r, k, v);
        }
        ll ans = 0;

        return ans;
    }

    void mul(int l, int r, int k, int v) {

    }
};

int main() {
    vector<int> arr1 = {1,2};
    vector<int> arr2 = {2};
    vector<int> arr3 = {17};
    vector<string> arr5 = {"aa", "ac"};
    vector<vector<int>> arr4 = {{0,1},{2,0},{1,2}};
    Solution s;
}
