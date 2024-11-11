/**
 * @Time : 2023/2/19-4:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/**
 * 给你两个下标从 0 开始的数组 nums1 和 nums2 ，和一个二维数组 queries 表示一些操作。总共有 3 种类型的操作：

操作类型 1 为 queries[i] = [1, l, r] 。你需要将 nums1 从下标 l 到下标 r 的所有 0 反转成 1 或将 1 反转成 0 。l 和 r 下标都从 0 开始。
操作类型 2 为 queries[i] = [2, p, 0] 。对于 0 <= i < n 中的所有下标，令 nums2[i] = nums2[i] + nums1[i] * p 。
操作类型 3 为 queries[i] = [3, 0, 0] 。求 nums2 中所有元素的和。
请你返回一个数组，包含所有第三种操作类型的答案。

 

示例 1：

输入：nums1 = [1,0,1], nums2 = [0,0,0], queries = [[1,1,1],[2,1,0],[3,0,0]]
输出：[3]
解释：第一个操作后 nums1 变为 [1,1,1] 。第二个操作后，nums2 变成 [1,1,1] ，所以第三个操作的答案为 3 。所以返回 [3] 。
示例 2：

输入：nums1 = [1], nums2 = [5], queries = [[2,0,0],[3,0,0]]
输出：[5]
解释：第一个操作后，nums2 保持不变为 [5] ，所以第二个操作的答案是 5 。所以返回 [5] 。
 

提示：

1 <= nums1.length,nums2.length <= 105
nums1.length = nums2.length
1 <= queries.length <= 105
queries[i].length = 3
0 <= l <= r <= nums1.length - 1
0 <= p <= 106
0 <= nums1[i] <= 1
0 <= nums2[i] <= 109

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/handling-sum-queries-after-update
 */
#include<bits/stdc++.h>
using namespace std;
#define ls (2 * x)
#define rs (2 * x + 1)
const int N = 1e5 + 5;
class Solution {
public:
    /*
     * 题目中的query类型用type表示
     * type = 3是一个对于nums2的求和操作
     * type = 2表面上是修改操作，但是修改后记录答案时是求和，因此不需要关注nums2中的各个元素是多少
     * 只需要关注和的变化，每一个nums1中为1的地方，都增加了p，因此只要知道nums1中一共有多少个1即可
     * type = 1对某个区间上的0和1进行翻转，就是改变了该区间中1的个数，改变了该区间的和
     *
     * 区间修改，区间查询 线段树
     * tag[x] = 1表示对应的区间中0和1要翻转
     * 并且如果某个区间的tag[x] = 1，然后再进行一次翻转，等于这个区间没有翻转
     * 因而在更新tag时，很简单有 tag = (tag + 1) % 2
     */
    int sum[4 * N], tag[4 * N];
    long long total = 0ll;
    vector<long long> handleQuery(vector<int>& nums1, vector<int>& nums2, vector<vector<int>>& queries) {
        int n = nums1.size();
        for(int num : nums2)
            total += num;
        build(nums1, 1, 0, n - 1);
        vector<long long> res;
        for(auto& query : queries){
            int type = query[0];
            if(type == 3) res.push_back(total);
            if(type == 2) total += (long long)query[1] * sum[1];
            if(type == 1) change(query[1], query[2], 1, 0, n - 1);
        }
        return res;
    }

    void change(int a, int b, int x, int l, int r){
        if(a <= l && r <= b){
            tag[x] = (tag[x] + 1) % 2;
            sum[x] = (r - l + 1 - sum[x]);
            return;
        }
        down(x, l, r);
        int mid = (r + l) >> 1;
        if(a <= mid) change(a, b, ls, l, mid);
        if(b > mid) change(a, b, rs, mid + 1, r);
        update(x);
    }

    void build(vector<int>& nums, int x, int l, int r){
        if(l == r) {
            sum[x] = nums[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(nums, ls, l, mid);
        build(nums, rs, mid + 1, r);
        update(x);
    }

    void update(int x){
        sum[x] = sum[ls] + sum[rs];
    }

    void down(int x, int l, int r){
        if(tag[x] == 0) return;
        int mid = (l + r) >> 1;
        sum[ls] = (mid - l + 1 - sum[ls]);
        sum[rs] = (r - mid - sum[rs]);
        tag[ls] = (tag[ls] + 1) % 2;
        tag[rs] = (tag[rs] + 1) % 2;
        tag[x] = 0;
    }
};

int main(){
    Solution s;
    vector<int> arr1 = {1,0,1}, arr2 = {0,0,0};
    vector<vector<int>> query = {{1,1,1}};
    s.handleQuery(arr1, arr2, query);
    cout << 0 << endl;
}