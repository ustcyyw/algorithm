/**
 * @Time : 2022/4/25-12:11 AM
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
     * 执行用时：0 ms, 在所有 C++ 提交中击败了100.00%的用户
     * 内存消耗：5.7 MB, 在所有 C++ 提交中击败了96.69%的用户
     */
    int binaryGap(int n) {
        int res = 0;
        bitset<32> bits = n;
        for(int i = 0, pre = -1; i < bits.size(); i++){
            if(bits[i] == 1){
                if(pre != -1) res = max(res, i - pre);
                pre = i;
            }
        }
        return res;
    }
};

int main(){

}