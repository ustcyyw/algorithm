#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, N = 5e4 + 5, MIN_VAL = -2e9;

// 预处理 [1-N]范围内所有数的因子
vector<int> divisors[N];
int init = []() {
    for (int i = 1; i < N; ++i)
        for (int j = i; j < N; j += i)
            divisors[j].push_back(i);
    return 0;
}();

class Solution {
public:
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        map<int, ll> map;
        for(int num : nums) {
            for(int d : divisors[num])
                map[d]++;
        }
        for(auto& p : map)
            p.second = p.second * (p.second - 1) / 2;
        vector<vector<ll>> aux, infos;
        for(auto it = map.rbegin(); it != map.rend(); it++) {
            ll num = it->first, cnt = it->second;
            aux.push_back({num, cnt});
            for(int d : divisors[num])
                map[d] -= cnt;
        }
        reverse(aux.begin(), aux.end());
        int n = aux.size(), m = queries.size();
        for(int i = 0; i < m; i++)
            infos.push_back({queries[i], i});
        sort(infos.begin(), infos.end());
        ll sum = 0;
        vector<int> ans(m, 0);
        for(int i = 0, j = 0; i < m; i++) {
            ll pos = infos[i][0], idx = infos[i][1];
            while(j < n && sum <= pos)
                sum += aux[j++][1];
            ans[idx] = aux[j - 1][0];
        }
        return ans;
    }
};

int main() {
    vector<int> arr1 = {4,4,2,1};
    vector<ll> arr2 = {5,3,1,0};
    vector<int> arr3 = {1, 2, 3};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr5 = {"cd", "bcd", "xyz"};
    vector<vector<int>> arr4 = {{8, 7, 6},
                                {8, 3, 2}};
    Solution s;
    s.gcdValues(arr1, arr2);
}
