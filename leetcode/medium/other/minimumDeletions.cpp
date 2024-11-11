/**
 * @Time : 2024/3/17-3:33 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛389 t3
 */
 /*
  * 枚举最小频率的字母 比它小的都删掉 比它了超过k的 就删除部分直到只超过k
  */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumDeletions(string word, int k) {
        vector<int> cnt(26, 0), arr;
        for(char c : word)
            cnt[c - 'a']++;
        for(int num : cnt)
            if(num) arr.push_back(num);
        sort(arr.begin(), arr.end());
        int ans = INT_MAX, n = arr.size();
        for(int i = 0, left = 0; i < n; i++) {
            int sum = 0;
            for(int j = i + 1; j < n; j++)
                if(arr[j] - arr[i] > k) sum += arr[j] - arr[i] - k;
            ans = min(ans, left + sum);
            left += arr[i];
        }
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}