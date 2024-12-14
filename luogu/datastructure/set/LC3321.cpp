/**
 * @Time : 2024/12/13-9:52 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3321 数据结构 对顶有序集合 类似于对顶堆的思路
 */
 /*
  * 键有两个部分构成 num和num出现的次数cnt 将cnt作为主要键就可以满足题目要求的顺序
  * 用两个有序集合就可以维护排名前x的元素了 然后动态维护sum即可
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N = 1e10;

class Solution {
public:
    int x;
    set<ll> left, right; // left中存排名靠后的元素 right中存排名靠前的元素
    unordered_map<int, int> map;
    vector<long long> findXSum(vector<int>& nums, int k, int x) {
        this->x = x;
        vector<ll> ans;
        ll sum = 0;
        for(int lo = 0, hi = 0; hi < nums.size(); hi++) {
            add(sum, nums[hi]);
            if(hi - lo + 1 > k) remove(sum, nums[lo++]);
            if(hi - lo + 1 == k) ans.push_back(sum);
        }
        return ans;
    }

    void remove(ll& sum, int num) {
        ll curK = map[num] * N + num, nextK = (map[num] - 1) * N + num;
        map[num]--;
        if(left.count(curK)) {
            left.erase(curK), left.insert(nextK);
        } else {
            right.erase(curK), left.insert(nextK);
            ll maxK = *left.rbegin();
            left.erase(maxK), right.insert(maxK);
            sum = sum - cal(curK) + cal(maxK);
        }
    }

    void add(ll& sum, int num) {
        ll curK = map[num] * N + num, nextK = (map[num] + 1) * N + num;
        map[num]++;
        if(left.count(curK)) left.erase(curK);
        else if(right.count(curK))
            right.erase(curK), sum -= cal(curK);
        right.insert(nextK), sum += cal(nextK);
        if(right.size() > x) {
            ll minK = *right.begin();
            right.erase(minK);
            sum -= cal(minK), left.insert(minK);
        }
    }

    ll cal(ll kk) {
        return kk / N * (kk % N);
    }
};
