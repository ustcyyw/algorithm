/**
 * @Time : 2022/6/24-1:33 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给定一个放有字母和数字的数组，找到最长的子数组，且包含的字母和数字的个数相同。

返回该子数组，若存在多个最长子数组，返回左端点下标值最小的子数组。若不存在这样的数组，返回一个空数组。

示例 1:

输入: ["A","1","B","C","D","2","3","4","E","5","F","G","6","7","H","I","J","K","L","M"]

输出: ["A","1","B","C","D","2","3","4","E","5","F","G","6","7"]
示例 2:

输入: ["A","A"]

输出: []
提示：

array.length <= 100000

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/find-longest-subarray-lcci
 */
class Solution {
public:
    /**
     * 区间上的数字，字母和统计，首先想到前缀和
     * 假设在某个索引hi处的前缀和 数字和字母分别为 a1, b1
     * 前面某个索引lo处的前缀和为a2, b2，要在[lo - 1, hi]上的数字和字母数量一致
     * 就需要 a1 - a2 = b1 - b2 -->  a1 - b1 = a2 - b2 所以要求差值相同
     * 要求最长，那就记录某个差值出现的第一个位置即可
     *
     * 执行用时：112 ms, 在所有 C++ 提交中击败了83.56%的用户
     * 内存消耗：92 MB, 在所有 C++ 提交中击败了28.42%的用户
     */
    vector<string> findLongestSubarray(vector<string>& array) {
        unordered_map<int, int> map; // diff -> index
        map[0] = 0; // 初始时，0个字母0个数字，差值为0，对应的下标为1
        int char_count = 0, num_count = 0, lo = -1, hi = -1, len = 0;
        for(int i = 0; i < array.size(); i++){
            if(isdigit(array[i][0])) num_count++;
            else char_count++;
            int diff = num_count - char_count;
            if(map.find(diff) == map.end()) map[diff] = i + 1; // 前缀和与索引要相差1
            else if(len < i - map[diff]){
                len = i - map[diff];
                lo = map[diff], hi = i; // map[diff]对应的是前缀和索引，本来要-1才是原本的索引，但是区间是该位置的右一位，所以还要+1
            }
        }
        vector<string> res;
        if(lo == -1) return res;
        for(int i = lo; i <= hi; i++)
            res.push_back(array[i]);
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}