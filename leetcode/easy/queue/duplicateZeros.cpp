/**
 * @Time : 2022/6/17-2:05 AM
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
     * 执行用时：8 ms, 在所有 C++ 提交中击败了51.92%的用户
     * 内存消耗：9.6 MB, 在所有 C++ 提交中击败了15.15%的用户
     */
    void duplicateZeros(vector<int>& arr) {
        deque<int> queue;
        for(int i = 0; i < arr.size(); i++){
            int num = arr[i];
            if(!queue.empty()) {
                arr[i] = queue.front();
                queue.pop_front();
                if(num == 0)
                    queue.push_back(0), queue.push_back(0);
            } else if(num == 0)
                queue.push_back(0);
        }
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}