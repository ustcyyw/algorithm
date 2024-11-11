/**
 * @Time : 2022/11/17-10:45 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

/*
 * 有序集合递推，集合中元素为[运算值,值的属性(本题中为对应的最小子数组的右端点)]。
 * 实现：递推 + 维护有序集合
 *
 * 维护有序集合（类似单调队列/单调栈）：
 * 随着元素变多，以位或为例
 * 1.按位或结果要么不变
 * （若不变会连续不变，因此对于连续相同的值可以去重、保留一个最小右端点、减小集合长度、优化复杂度）、
 * 2.要么变大（最先放入集合中的元素其按位或结果越大，即维护了集合的单调性）。
 *
 * 递推：
 * 由于是求子数组（不是子序列）
 * 前一个元素的满足的子数组的右端点，也是当前元素的满足的子数组的右端点。
 *
 * 用途
 * 适用：
 * 1.运算具有单调性（如按位或/乘法/lcm/按位与/gcd...，后两者单调递减）
 * 2.且值域较小（在内层循环遍历所有集合值不会超时）；
 * 3.求的子数组，相邻子数组的结果可以被复用。
 *
 * 可以得到所有的值 /值属性（计数/子数组长度/…）。
 */

class Solution {
public:
    /*
     * 2411题：按位或最大的子数组，长度最小
     * 子数组元素增加，位或的结果不变或者增大，具有单调性
     * 在固定左端点i的情况下，右端点j右移动，这个过程中位或的结果可能不变，记为t
     * 那么达到t的最小的j，就确定了以i开头的，位或值为t的最小子数组
     *
     * 从后往左遍历
     * 有序集合arr维护：<位或值，该值对应的最小右端点>
     * 序列是单调递减，也就是arr[k].first > arr[k + 1].first
     * 这也保证了 arr[k].second > arr[k + 1].second
     * 因为arr[k]和arr[k + 1]在遍历过程中左端点都是同一个
     * arr[k]的位或值大，那么一定是右端点更靠右，这个子数组中有更多的元素
     *
     * 当遍历到一个新的元素nums[i]时
     * arr中的所有位或值都要更新
     * arr[k].first |= nums[i]
     * 更新后，可能会有 arr[k].first = arr[k + 1].first = arr[k + 2].first = ... = arr[j - 1].first
     * 但 arr[k].first != arr[j].first
     * 注意arr[k].second是最小的右端点，因此这个更新过程中arr[k].first会被不断赋值(等价于arr[k]被赋值)
     * 直到arr[k].first != arr[j].first
     *
     * arr[j].first就是一个未重复出现的值，要存储下来 arr[++k] = arr[j]
     * 最终arr[0, k]就是更新之后保留的值
     *
     * 注意在更新之前，arr末尾添加<0,i>，这样位或更新后
     * 这个元素依然在arr最后一个位置，变为<nums[i], i>
     */
    vector<int> smallestSubarrays(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n);
        vector<pair<int, int>> arr; // 维护位或值及其对应的最小右端点
        for(int i = n - 1; i >= 0; i--){
            int num = nums[i], k = 0;
            arr.push_back({num, i});
            arr[0].first |= num;
            for(int j = 1; j < arr.size(); j++){ // arr中的所有位或值都要更新
                arr[j].first |= num;
                if(arr[k].first == arr[j].first) arr[k] = arr[j];
                else arr[++k] = arr[j]; // arr[j].first就是一个未重复出现的值，要存储下来
            }
            arr.resize(k + 1); // 剔除无用的值
            res[i] = arr[0].second - i + 1; // arr[0]中的异或值最大
        }
        return res;
    }

    /**
     * 2470:最小公倍数lcm为target的子数组的数目
     * 子数组元素增加，lcm不变或者增大，具有单调性
     * lcm增大的时候，最小也是*2，因此lcm的值域比较小，且题目限定了target <= 1000，大于这个值的lcm直接不必考虑
     *
     * 从后往左遍历
     * 有序集合arr维护：<最小公倍数lcm，该值对应的子数组数量>
     * 序列是单调递减，但公倍数不断变大，可能会导致头元素已经超过了target，就可以直接舍弃
     *
     * 当遍历到一个新的元素nums[i]时
     * arr中有效元素的lcm都要更新，如果有相同的lcm，就通过累加进行去重
     */
    int subarrayLCM(vector<int>& nums, int target){
        int n = nums.size(), res = 0;
        vector<pair<int, int>> arr;
        for(int i = n - 1; i >= 0; i--){
            int j = 1, k = 0, num = nums[i];
            arr.push_back({1, 1});
            while (j < arr.size() && arr[0].first > target) // 头元素已经超过了target，就可以直接舍弃
                arr[0] = arr[j++];
            arr[0].first = lcm(arr[0].first, num);
            for(; j < arr.size(); j++){
                arr[j].first = lcm(arr[j].first, num);
                // 注意这里是求数组的数量，所以去重的时候不是替换，而是累加
                if(arr[j].first == arr[k].first) arr[k].second += arr[j].second;
                else arr[++k] = arr[j];
            }
            arr.resize(k + 1);
            for(auto& p : arr)
                if(p.first == target) res += p.second;
        }
        return res;
    }

    /**
     * 2447：最小公约数gcd等于target的子数组的数目
     * 数组元素增加，gcd不变或者减小，具有单调性
     * gcd减小的时候，最少也是除以2，因此gcd的值域比较小
     *
     * 从后往左遍历
     * 有序集合arr维护：<最大公约数gcd，该值对应的子数组数量>
     * 集合是单调增的，头元素可能会小于target，那么不管增添什么新的元素，其gcd都不可能为target，舍弃
     */
    int subarrayGCD(vector<int>& nums, int target) {
        int n = nums.size(), res = 0;
        vector<pair<int, int>> arr;
        for(int i = n - 1; i >= 0; i--){
            int j = 1, k = 0, num = nums[i];
            arr.push_back({num,  1});
            while (j < arr.size() && arr[0].first < target)
                arr[0] = arr[j++];
            arr[0].first = gcd(arr[0].first, num);
            for(; j < arr.size(); j++){
                arr[j].first = gcd(arr[j].first, num);
                if(arr[j].first == arr[k].first) arr[k].second += arr[j].second;
                else arr[++k] = arr[j];
            }
            arr.resize(k + 1);
            for(auto& p : arr)
                if(p.first == target) res += p.second;
        }
        return res;
    }

    /**
     * 898题 合并方式与2411一致，甚至不需要维护索引的相关信息
     */
    int subarrayBitwiseORs(vector<int>& nums) {
        int n = nums.size();
        unordered_set<int> set;
        vector<int> arr; // 本题只求有多少位或值，因此不需要额外记录信息
        for(int i = n - 1; i >= 0; i--){
            int k = 0, num = nums[i];
            arr.push_back(0);
            arr[0] |= num;
            for(int j = 1; j < arr.size(); j++){
                arr[j] |= num;
                if(arr[k] != arr[j])
                    arr[++k] = arr[j];
            }
            arr.resize(k + 1);
            for(int t : arr)
                set.insert(t);
        }
        return set.size();
    }

    /*
     * https://leetcode.cn/problems/minimum-number-of-operations-to-make-all-array-elements-equal-to-1
     * 周赛342场 t4
     * 本题要通过相邻元素a,b之间求gcd(a,b)，选其中一个变为gcd(a,b)
     * 最终使数组中所有元素变为1
     *
     * 加入数组中已经有1，最好的办法就是用1和周围的数求gcd，将周围的数不断变为1
     * 如果数组中初始已经有cnt个1，那么答案就是n - cnt
     *
     * 如果数组中没有1，找到一个最短的子数组，通过相邻元素gcd得到1，用这个1去执行上述操作
     * 就能到达最小操作数
     */
    int minOperations(vector<int>& nums) {
        int cnt = 0, n = nums.size();
        for(int num : nums)
            if(num == 1) cnt++;
        if(cnt > 0) return n - cnt;
        int len = minLen(nums);
        return len == INT_MAX ? -1 : (len - 1) + n - 1;
    }
    /*
     * 求gcd = 1的最小子数组的长度
     * 1.gcd的操作具有单调性，在不断进行gcd的过程中，结果是越来越小的 且最终会等于1
     * 2.本题中nums[i] < 1e6 并且gcd减小，每次不变或者至少变为原来的1/2 因此值域的大小有限
     * 3.求子数组的长度
     * 因此可以维护有序集合，进行递推，集合元素维护 <gcd的值，该值对应数组右端点的最小值>
     * gcd的值单调递增，右端点的最小值 单调递减
     */
    int minLen(vector<int>& nums){
        int res = INT_MAX, n = nums.size();
        vector<pair<int, int>> arr;
        for(int i = n - 1; i >= 0; i--){
            int k = 0, num = nums[i];
            arr.push_back({num, i});
            arr[0].first = gcd(arr[0].first, num);
            for(int j = 1; j < arr.size(); j++) {
                arr[j].first = gcd(arr[j].first, num);
                if(arr[j].first == arr[k].first) arr[k].second = arr[j].second;
                else arr[++k] = arr[j];
            }
            if(arr[0].first == 1)
                res = min(res, arr[0].second - i + 1);
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}