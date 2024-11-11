/**
 * @Time : 2022/8/16-12:33 PM
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
     * 内存消耗：5.7 MB, 在所有 C++ 提交中击败了97.85%的用户
     */
    int maxDiff(int num) {
        string min_val = to_string(num), max_val = to_string(num);
        int i = 0, j = 0, n = min_val.length();
        //i如果移动，说明开头第一位是1，那么后续遇到1都是不能更改的，遇到0也没法改小，要一直找到非1非0的数
        while (i < n && (min_val[i] == '1' || min_val[i] == '0')) i++;
        char c = i == 0 ? '1' : '0', temp = min_val[i];
        for(int k = 0; k < n; k++){
            if(min_val[k] == temp)
                min_val[k] = c;
        }
        while (j < n && max_val[i] == '9') j++;
        c = '9', temp = max_val[j];
        for(int k = 0; k < n; k++)
            if(max_val[k] == temp)
                max_val[k] = c;
        return stoi(max_val) - stoi(min_val);
    }
};

int main(){
    Solution s;
    cout << 0 << endl;
}