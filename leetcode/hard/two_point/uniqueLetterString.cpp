/**
 * @Time : 2022/4/24-7:30 PM
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
     * 执行用时：68 ms, 在所有 C++ 提交中击败了26.70%的用户
     * 内存消耗：256.4 MB, 在所有 C++ 提交中击败了5.11%的用户
     */
    int n, mod = 1000000007;
    int uniqueLetterString(string s) {
        n = s.size();
        vector<vector<int>> pre = getPreIndex(s), after = getAfterIndex(s);
        long res = 0;
        for(int i = 0; i < n; i++){
            int cur = s[i] - 'A';
            res = (res + (i - pre[cur][i]) * (after[cur][i] - i)) % mod;
        }
        return (int)res;
    }

    vector<vector<int>> getPreIndex(string s){
        vector<int> map = vector(26, -1);
        vector<vector<int>> indexs = vector(26, vector(n, 0));
        for(int i = 0; i < n; i++){
            int cur = s[i] - 'A';
            indexs[cur][i] = map[cur];
            map[cur] = i;
        }
        return indexs;
    }
    vector<vector<int>> getAfterIndex(string s){
        vector<int> map = vector(26, n);
        vector<vector<int>> indexs = vector(26, vector(n, 0));
        for(int i = n - 1; i >= 0; i--){
            int cur = s[i] - 'A';
            indexs[cur][i] = map[cur];
            map[cur] = i;
        }
        return indexs;
    }
};

int main(){

}