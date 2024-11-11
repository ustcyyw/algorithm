/**
 * @Time : 2024/3/24-1:12 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛390 t2
 */
 /*
  * 如果要使用+1操作 一定是在一开始全部加到第一个数上
  * 然后再使用复制操作 这样能让和最大
  * 因此枚举num，表示+1操作将第一个数变化为多少
  */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minOperations(int k) {
        int ans = INT_MAX;
        for(int num = 1; num <= k; num++) {
            int temp = k - num;
            temp = temp % num == 0 ? temp / num : temp / num + 1;
            ans = min(ans, temp + num - 1);
        }
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}