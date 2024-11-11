/**
 * @Time : 2022/9/30-2:45 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int getXORSum(vector<int>& arr1, vector<int>& arr2) {
        vector<int> cnt1 = countBit(arr1), cnt2 = countBit(arr2);
        int res = 0;
        for(int i = 0; i < 32; i++){
            if((long)cnt1[i] * cnt2[i] % 2 == 1)
                res |= 1 << i;
        }
        return res;
    }

    vector<int> countBit(vector<int>& arr){
        vector<int> cnt(32, 0);
        for(int num : arr){
            for(int i = 0; i < 32; i++)
                if((1 << i) & num)
                    cnt[i]++;
        }
        return cnt;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}