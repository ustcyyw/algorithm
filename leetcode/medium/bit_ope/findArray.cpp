/**
 * @Time : 2022/10/9-1:06 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 * 给你一个长度为 n 的 整数 数组 pref 。找出并返回满足下述条件且长度为 n 的数组 arr ：

pref[i] = arr[0] ^ arr[1] ^ ... ^ arr[i].
注意 ^ 表示 按位异或（bitwise-xor）运算。

可以证明答案是 唯一 的。

 

示例 1：

输入：pref = [5,2,0,3,1]
输出：[5,7,2,3,2]
解释：从数组 [5,7,2,3,2] 可以得到如下结果：
- pref[0] = 5
- pref[1] = 5 ^ 7 = 2
- pref[2] = 5 ^ 7 ^ 2 = 0
- pref[3] = 5 ^ 7 ^ 2 ^ 3 = 3
- pref[4] = 5 ^ 7 ^ 2 ^ 3 ^ 2 = 1
示例 2：

输入：pref = [13]
输出：[13]
解释：pref[0] = arr[0] = 13
 

提示：

1 <= pref.length <= 105
0 <= pref[i] <= 106

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/find-the-original-array-of-prefix-xor
 */
class Solution {
public:
    vector<int> findArray(vector<int>& pref) {
        int n = pref.size();
        vector<int> res;
        res.push_back(pref[0]);
        for(int i = 1; i < n; i++)
            res.push_back(pref[i] ^ pref[i - 1]);
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}