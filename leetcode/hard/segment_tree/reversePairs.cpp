/**
 * @Time : 2022/7/3-3:11 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>

using namespace std;
/**
 *给定一个数组 nums ，如果 i < j 且 nums[i] > 2*nums[j] 我们就将 (i, j) 称作一个重要翻转对。
你需要返回给定数组中的重要翻转对的数量。

示例 1:

输入: [1,3,2,3,1]
输出: 2
示例 2:

输入: [2,4,3,5,1]
输出: 3
注意:

给定数组的长度不会超过50000。
输入数组中的所有数字都在32位整数的表示范围内。

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/reverse-pairs
 */

class Solution {
public:
    /**
     * 本题中线段树中的信息是：落在区间上的元素有多少个
     */
    vector<int> info;
    int reversePairs(vector<int> &nums) {
        unordered_map<long, int> map = scatter(nums);
        int n = map.size(), res = 0;
        info.assign(4 * n, 0);
        for(int i = 0; i < nums.size(); i++){ // 枚举nums[j]
            long key = 2 * (long) nums[i]; // 要找其左边大于2 * nums[j]的元素有多少个
            int a = map[key], pos = map[(long)nums[i]];
            // query出来的是[1, a]上的，也就是小于等于nums[j] * 2的，再用总的减去这个数，就是大于nums[j] * 2的
            res += i - query(1, a, 1, n, 1);
            change(1, n, pos, 1);
        }
        return res;
    }
    void change(int l, int r, int pos, int x){
        if(l == r) {
            info[x]++; // 本题中每次改变就是指某个值对应的数量+1
            return;
        }
        int mid = (r + l) >> 1;
        if(pos <= mid) change(l, mid, pos,  2 * x);
        else change(mid + 1, r, pos,2 * x + 1);
        info[x] = info[2 * x] + info[2 * x + 1];
    }
    // 线段树的查询
    int query(int a, int b, int l, int r, int x) {
        // [l,r]是所查询的[a,b]的子区间，那么当前区间的所有信息都需要，直接返回info[x]
        if(a <= l && r <= b) return info[x];
        int mid = (l + r) >> 1, res = 0;
        if(a <= mid) res += query(a, b, l, mid, 2 * x);
        if(b > mid) res += query(a, b, mid + 1, r, 2 * x + 1);
        return res;
    }

    unordered_map<long, int> scatter(vector<int> &nums) {
        int n = nums.size() * 2;
        long aux[n];
        for (int i = 0, j = 0; i < nums.size(); i++, j += 2)
            aux[j] = nums[i], aux[j + 1] = (long) nums[i] * 2;
        sort(aux, aux + n);
        int count = unique(aux, aux + n) - aux;
        unordered_map<long, int> map;
        for (int num: nums) {
            long temp = (long) num;
            map[temp] = lower_bound(aux, aux + count, temp) - aux + 1;
            map[2 * temp] = lower_bound(aux, aux + count, 2 * temp) - aux + 1;
        }
        return map;
    }
};

int main() {
    Solution s;
    vector<int> arr = {1,3,2,3,1};
    s.reversePairs(arr);
    cout << 0 << endl;
}