/**
 * @Time : 2022/8/19-10:38 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个区间列表，请你删除列表中被其他区间所覆盖的区间。

只有当 c <= a 且 b <= d 时，我们才认为区间 [a,b) 被区间 [c,d) 覆盖。

在完成所有删除操作后，请你返回列表中剩余区间的数目。

 

示例：

输入：intervals = [[1,4],[3,6],[2,8]]
输出：2
解释：区间 [3,6] 被区间 [2,8] 覆盖，所以它被删除了。
 

提示：​​​​​​

1 <= intervals.length <= 1000
0 <= intervals[i][0] < intervals[i][1] <= 10^5
对于所有的 i != j：intervals[i] != intervals[j]

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/remove-covered-intervals
 */
class Solution {
public:
    /**
     * 执行用时：20 ms, 在所有 C++ 提交中击败了76.48%的用户
     * 内存消耗：11.1 MB, 在所有 C++ 提交中击败了32.42%的用户
     */
    int removeCoveredIntervals(vector<vector<int>>& intervals) {
        int res = intervals.size(), right = 0;
        sort(intervals.begin(), intervals.end(), [](auto& a, auto& b) -> bool {
            return a[0] != b[0] ? a[0] < b[0] : a[1] > b[1];
        });
        for(vector<int>& interval : intervals){
            if(right >= interval[1]) res--;
            else right = interval[1];
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}