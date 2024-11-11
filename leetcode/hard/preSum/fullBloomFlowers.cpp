/**
 * @Time : 2022/8/1-9:57 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个下标从 0 开始的二维整数数组 flowers ，其中 flowers[i] = [starti, endi] 表示第 i 朵花的 花期 从 starti 到 endi （都 包含）。同时给你一个下标从 0 开始大小为 n 的整数数组 persons ，persons[i] 是第 i 个人来看花的时间。

请你返回一个大小为 n 的整数数组 answer ，其中 answer[i]是第 i 个人到达时在花期内花的 数目 。

 

示例 1：



输入：flowers = [[1,6],[3,7],[9,12],[4,13]], persons = [2,3,7,11]
输出：[1,2,2,2]
解释：上图展示了每朵花的花期时间，和每个人的到达时间。
对每个人，我们返回他们到达时在花期内花的数目。
示例 2：



输入：flowers = [[1,10],[3,3]], persons = [3,3,2]
输出：[2,2,1]
解释：上图展示了每朵花的花期时间，和每个人的到达时间。
对每个人，我们返回他们到达时在花期内花的数目。
 

提示：

1 <= flowers.length <= 5 * 104
flowers[i].length == 2
1 <= starti <= endi <= 109
1 <= persons.length <= 5 * 104
1 <= persons[i] <= 109

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/number-of-flowers-in-full-bloom
 */
class Solution {
public:
    /**
     * 离散化的差分
     */
    vector<int> fullBloomFlowers(vector<vector<int>>& flowers, vector<int>& persons) {
        unordered_set<int> set;
        for(vector<int>& flower : flowers){
            set.insert(flower[0]); set.insert(flower[1]);
        }
        for(int person : persons)
            set.insert(person);
        vector<int> times;
        for(int num : set)
            times.push_back(num);
        unordered_map<int, int> map = scatter(times);
        vector<int> aux = vector(times.size() + 1, 0), sum = vector(times.size() + 1, 0);
        for(vector<int>& flower : flowers){
            int start = map[flower[0]], end = map[flower[1]];
            aux[start]++, aux[end + 1]--;
        }
        for(int i = 1; i < sum.size(); i++)
            sum[i] = sum[i - 1] + aux[i];

        vector<int> res;
        for(int person : persons)
            res.push_back(sum[map[person]]);
        return res;
    }

    unordered_map<int, int> scatter(vector<int>& nums){
        sort(nums.begin(), nums.end());
        unordered_map<int, int> map;
        for(int i = 0; i < nums.size(); i++)
            map[nums[i]] = i;
        return map;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}