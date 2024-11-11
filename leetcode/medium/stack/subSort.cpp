/**
 * @Time : 2022/6/21-2:46 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> subSort(vector<int>& array) {
        vector<int> range1 = next_less_or_equal(array), range2 = pre_large(array);
        if(range1[0] == -1) return range2;
        if(range2[0] == -1) return range1;
        return {min(range1[0], range2[0]), max(range1[1], range2[1])};
    }

    // 找下一个小于等于的元素
    vector<int> next_less_or_equal(vector<int>& arr){
        stack<int> stack; // 单调增的栈（可以相等）
        int lo = -1, hi = -1;
        for(int i = arr.size() - 1; i >= 0; i--){
            while (!stack.empty() && arr[i] < arr[stack.top()]) stack.pop();
            if(!stack.empty() && i + 1 != stack.top()){
                if(hi == -1) hi = stack.top();
                lo = arr[stack.top()] == arr[i] ? i + 1 : i;
            }
            stack.push(i);
        }
        return {lo, hi};
    }

    // 找到前一个更大的元素，相等的元素已经在next_less_or_equal中考虑了
    vector<int> pre_large(vector<int>& arr){
        stack<int> stack; // 单调减的栈
        int lo = -1, hi = -1;
        for(int i = 0; i < arr.size(); i++){
            while (!stack.empty() && arr[i] >= arr[stack.top()]) stack.pop();
            if(!stack.empty()){
                if(lo == -1) lo = stack.top();
                hi = i;
            }
            stack.push(i);
        }
        return {lo, hi};
    }
};

int main(){
    Solution s;
    vector<int> arr = {1,3,9,7,5};
    s.subSort(arr);
    cout << arr[493] << "," << arr[494] << endl;
}