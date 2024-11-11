/**
 * @Time : 2022/6/4-2:00 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

/**
 * 执行用时：12 ms, 在所有 C++ 提交中击败了89.91%的用户
 * 内存消耗：9.7 MB, 在所有 C++ 提交中击败了35.10%的用户
 */

class Solution {
public:
    int n, len;
    bool makesquare(vector<int>& matchsticks) {
        n = matchsticks.size();
        int sum = 0;
        for(int& length : matchsticks)
            sum += length;
        if(sum % 4 != 0) return false;
        // 先从大的开始选，这样可以先用尽可能少的火柴凑出单条边，或者凑不出来的时候提早结束
        sort(matchsticks.begin(), matchsticks.end());
        len = sum / 4;
        return backTrack(matchsticks, 0, len);
    }

    bool backTrack(vector<int>& arr, int cur, int left){
        if(cur == n) return left == 0;
        if(left == 0) left = len; // 说明上一边已经凑齐，要去凑下一条边了。
        for(int i = arr.size() - 1, pre = -1; i >= 0; i--){
            int temp = arr[i];
            if(temp == -1 || temp == pre) continue; // 当前元素已使用；或者当前元素和上一个元素相同，就不必尝试了
            if(left - temp < 0) break;
            pre = temp;
            arr[i] = -1;
            if(backTrack(arr, cur + 1, left - temp)) return true;
            arr[i] = temp;
        }
        return false;
    }
};

int main(){
    Solution s;
    vector<int> arr = {10,6,5,5,5,3,3,3,2,2,2,2};
    s.makesquare(arr);
}