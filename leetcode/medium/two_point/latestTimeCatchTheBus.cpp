/**
 * @Time : 2022/7/11-9:30 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个下标从 0 开始长度为 n 的整数数组 buses ，其中 buses[i] 表示第 i 辆公交车的出发时间。同时给你一个下标从 0 开始长度为 m 的整数数组 passengers ，其中 passengers[j] 表示第 j 位乘客的到达时间。所有公交车出发的时间互不相同，所有乘客到达的时间也互不相同。

给你一个整数 capacity ，表示每辆公交车 最多 能容纳的乘客数目。

每位乘客都会搭乘下一辆有座位的公交车。如果你在 y 时刻到达，公交在 x 时刻出发，满足 y <= x  且公交没有满，那么你可以搭乘这一辆公交。最早 到达的乘客优先上车。

返回你可以搭乘公交车的最晚到达公交站时间。你 不能 跟别的乘客同时刻到达。

注意：数组 buses 和 passengers 不一定是有序的。

 

示例 1：

输入：buses = [10,20], passengers = [2,17,18,19], capacity = 2
输出：16
解释：
第 1 辆公交车载着第 1 位乘客。
第 2 辆公交车载着你和第 2 位乘客。
注意你不能跟其他乘客同一时间到达，所以你必须在第二位乘客之前到达。
示例 2：

输入：buses = [20,30,10], passengers = [19,13,26,4,25,11,21], capacity = 2
输出：20
解释：
第 1 辆公交车载着第 4 位乘客。
第 2 辆公交车载着第 6 位和第 2 位乘客。
第 3 辆公交车载着第 1 位乘客和你。
 

提示：

n == buses.length
m == passengers.length
1 <= n, m, capacity <= 105
2 <= buses[i], passengers[i] <= 109
buses 中的元素 互不相同 。
passengers 中的元素 互不相同 。

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/the-latest-time-to-catch-a-bus
 */
class Solution {
public:
    int latestTimeCatchTheBus(vector<int>& buses, vector<int>& passengers, int capacity) {
        sort(buses.begin(), buses.end());
        sort(passengers.begin(), passengers.end());
        unordered_set<int> set;
        for(int num : passengers) set.insert(num);
        int i = 0, j = 0, n = buses.size(), m = passengers.size(), res = 0;
        // 在循环中有机会就更新最晚上车时间
        while (i < n && j < m){
            for(int c = capacity; c > 0; c--, j++){
                if(j == 0) res = passengers[0] - 1;
                else if(passengers[j] - 1 != passengers[j - 1])
                    res = passengers[j] - 1;
                if(j + 1 == m){ // 当前乘客是最后一个乘客 那如果最后一辆车还有空位，就让该人从最后一辆车的极限时间上车
                    // 还没使用最后一辆车(i != n-1)，或者最后一辆车在搭载当前乘客后，还剩至少一个位置(c > 1)
                    if(c > 1 || i != n - 1)
                        res = findValidMax(set, buses[n - 1]);
                    j++; // 最后一个乘客要上车，所以指针j右移
                    break;
                }
                if(buses[i] < passengers[j]){ // 当前乘客已经在当前车之后，那么该乘客由下一辆车来载
                    if(c > 0) // 当前车还有剩余的位置，该人可以从当前车的极限时间上车
                        res = findValidMax(set, buses[i]);
                    break;
                }
            }
            i++;
        }
        return res;
    }

    int findValidMax(unordered_set<int>& set, int hi){
        while (set.count(hi)) hi--;
        return hi;
    }
};

int main(){
    Solution s;
    vector<int> arr1 = {6,8,18,17}, arr2 = {6,8,17};
    s.latestTimeCatchTheBus(arr1, arr2, 1);
    cout << 0 << endl;
}