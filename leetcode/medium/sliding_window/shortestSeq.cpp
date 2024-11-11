/**
 * @Time : 2022/7/4-11:09 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 假设你有两个数组，一个长一个短，短的元素均不相同。找到长数组中包含短数组所有的元素的最短子数组，其出现顺序无关紧要。

返回最短子数组的左端点和右端点，如有多个满足条件的子数组，返回左端点最小的一个。若不存在，返回空数组。

示例 1:

输入:
big = [7,5,9,0,2,1,3,5,7,9,1,1,5,8,8,9,7]
small = [1,5,9]
输出: [7,10]
示例 2:

输入:
big = [1,2,3]
small = [4]
输出: []
提示：

big.length <= 100000
1 <= small.length <= 100000

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/shortest-supersequence-lcci
 */
class Solution {
public:
    vector<int> shortestSeq(vector<int>& big, vector<int>& small) {
        int nb = big.size(), bs = small.size();
        if(bs > nb) return {};
        unordered_set<int> set;
        unordered_map<int, int> map;
        for(int num : small)
            set.insert(num);
        int left = 0, right = 0, len = nb + 1, lo = -1, hi = -1;
        while (right < nb){
            int num = big[right];
            if(set.count(num))
                map[num] = map.find(num) == map.end() ? 1 : map[num] + 1;
            while (map.size() == bs){
                if(len > right - left + 1){
                    len = right - left + 1;
                    lo = left, hi = right;
                }
                int temp = big[left++];
                if(set.count(temp) && --map[temp] == 0) map.erase(temp);
            }
            right++;
        }
        if(lo == -1) return {};
        return {lo, hi};
    }
};

int main(){
    Solution s;
    vector<int> big = {7, 5, 9, 0, 2, 1, 3, 5, 7, 9, 1, 1, 5, 8, 8, 9, 7}, small = {1,5,7,9};
    s.shortestSeq(big, small);
    cout << 0 << endl;
}