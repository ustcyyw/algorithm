/**
 * @Time : 2023/5/7-11:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/*
 * 给你一个下标从 0 开始、长度为 n 的数组 nums 。一开始，所有元素都是 未染色 （值为 0 ）的。

给你一个二维整数数组 queries ，其中 queries[i] = [indexi, colori] 。

对于每个操作，你需要将数组 nums 中下标为 indexi 的格子染色为 colori 。

请你返回一个长度与 queries 相等的数组 answer ，其中 answer[i]是前 i 个操作 之后 ，相邻元素颜色相同的数目。

更正式的，answer[i] 是执行完前 i 个操作后，0 <= j < n - 1 的下标 j 中，满足 nums[j] == nums[j + 1] 且 nums[j] != 0 的数目。

 

示例 1：

输入：n = 4, queries = [[0,2],[1,2],[3,1],[1,1],[2,1]]
输出：[0,1,1,0,2]
解释：一开始数组 nums = [0,0,0,0] ，0 表示数组中还没染色的元素。
- 第 1 个操作后，nums = [2,0,0,0] 。相邻元素颜色相同的数目为 0 。
- 第 2 个操作后，nums = [2,2,0,0] 。相邻元素颜色相同的数目为 1 。
- 第 3 个操作后，nums = [2,2,0,1] 。相邻元素颜色相同的数目为 1 。
- 第 4 个操作后，nums = [2,1,0,1] 。相邻元素颜色相同的数目为 0 。
- 第 5 个操作后，nums = [2,1,1,1] 。相邻元素颜色相同的数目为 2 。
示例 2：

输入：n = 1, queries = [[0,100000]]
输出：[0]
解释：一开始数组 nums = [0] ，0 表示数组中还没染色的元素。
- 第 1 个操作后，nums = [100000] 。相邻元素颜色相同的数目为 0 。
 

提示：

1 <= n <= 105
1 <= queries.length <= 105
queries[i].length == 2
0 <= indexi <= n - 1
1 <=  colori <= 105


来源：力扣（LeetCode）
链接：https://leetcode.cn/problems/number-of-adjacent-elements-with-the-same-color
 */
class Solution {
public:
    vector<int> colorTheArray(int n, vector<vector<int>>& queries) {
        int cnt = 0;
        vector<int> res, arr(n, 0);
        for(auto& query : queries) {
            int i = query[0], c = query[1];
            if(i - 1 >= 0 && arr[i - 1] != 0) {
                if(arr[i] == arr[i - 1]) cnt--;
                if(arr[i - 1] == c) cnt++;
            }
            if(i + 1 < n && arr[i + 1] != 0) {
                if(arr[i] == arr[i + 1]) cnt--;
                if(arr[i + 1] == c) cnt++;
            }
            arr[i] = c;
            res.push_back(cnt);
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}