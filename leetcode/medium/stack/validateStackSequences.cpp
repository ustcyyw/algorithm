/**
 * @Time : 2022/5/9-4:25 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

/**
 * 直接用栈模拟
 */
class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int> stack;
        int n = pushed.size();
        for(int i = 0, j = 0; j < n; ){
            while (i < n && pushed[i] != popped[j])
                stack.push(pushed[i++]);
            if(i < n) stack.push(pushed[i++]);
            while (!stack.empty() && stack.top() == popped[j]){
                stack.pop();
                j++;
            }
            if(i == n && !stack.empty()) return false;
        }
        return true;
    }
};

int main(){

}