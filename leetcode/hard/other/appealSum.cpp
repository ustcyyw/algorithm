/**
 * @Time : 2022/7/30-1:52 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * 执行用时：16 ms, 在所有 C++ 提交中击败了92,28%的用户
     * 内存消耗：10.3 MB, 在所有 C++ 提交中击败了67.47%的用户
     *
     * 考虑每一个字母能贡献的答案，为了避免重复，其影响范围划定为[i + 1, n - 1]
     * 其中i为上一个相同字母所在的索引
     * 然后数其影响范围内，包含它的子数组有多少
     */
    long long appealSum(string s) {
        int n = s.size();
        vector<int> pres = vector(26, -1);
        long long res = 0;
        for(int i = 0; i < n; i++){
            int index = s[i] - 'a';
            res += (long long)(i - pres[index]) * (n - i);
            pres[index] = i;
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}