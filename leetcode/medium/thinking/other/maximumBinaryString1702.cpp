/**
 * @Time : 2023/5/4-5:26 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * 贪心 从左往右 尽可能高位为1
     * 高位是1，则无需处理；高位是0则还需要看下一位的情况
     * 00 直接变 10
     * 01 通过举例观察发现，（利用10变01和00变10的规则）可以将下一个0变为1，从而实现将当前的01比昂为10
     *
     * 因此需要维护下一个0在哪里
     */
    string maximumBinaryString(string binary) {
        int n = binary.size();
        stack<int> zeros;
        for(int i = n - 1; i >= 0; i--)
            if(binary[i] == '0') zeros.push(i);
        for(int i = 0; i < n - 1; i++) {
            if(binary[i] == '1') continue;
            if(binary[i + 1] == '0') { // 00的情况
                binary[i] = '1';
                zeros.pop();
            }
            else if(zeros.size() > 1) { // 01的情况
                zeros.pop();
                binary[i] = binary[zeros.top()] = '1';
                zeros.pop();
                binary[i + 1] = '0';
                zeros.push(i + 1);
            }
        }
        return binary;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}