/**
 * @Time : 2025/11/7-11:16
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3645 2018 思维 贪心 排序
 */
 /*
  * l = 1的 拿1个最大的
  * l = 2  如果有超过2个 那就直接拿2个最大的完事
  * l = 3  如果l=2的有剩余 再拿1个l=3的，让那个l=2的失活，接下来就可以继续挑l=3的了
  *
  * 所以数量不足limit[i]的组 直接全部拿
  * 然后在下一组的时候 一个一个拿 让前面不到limit限制的先达到 然后失活 就能腾出数量限制了
  * 超过limit[i]的组 那就只能拿最大的limit[i]个，然后这一组的就都失活
  */
#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 1e5 + 5;

class Solution {
public:
    long long maxTotal(vector<int>& value, vector<int>& limit) {
        int n = value.size();
        map<int, vector<int>> map;
        for(int i = 0; i < n; i++)
            map[limit[i]].push_back(value[i]);
        ll ans = 0;
        for(auto& p : map) {
            int cnt = p.first;
            sort(p.second.begin(), p.second.end());
            for(int i = p.second.size() - 1; i >= 0 && cnt > 0; i--, cnt--)
                ans += p.second[i];
        }
        return ans;
    }
};