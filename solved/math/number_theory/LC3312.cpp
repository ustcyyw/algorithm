/**
 * @Time : 2025/1/15-9:11 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3312 数学 容斥原理
 */
 /*
  * 数的取值范围比较小 单个数的因子个数有限（在此数据范围内最多有72个因子）
  * 如果两个数有多个公共因子，取最大那个就是gcd
  * 统计每个因子，有多少个数含有这个因子
  * 找gcd，所以先从最大因子num开始思考 假设这个含有这个因子的数有c1个
  * 那么一共有 c1 * (c1 - 1) / 2 个数对的gcd为num
  * 但这些数对，还会有更小的公共因子divisors[num]，要将这些更小的公共因子减去num的影响
  */
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