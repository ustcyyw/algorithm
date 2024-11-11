/**
 * @Time : 2023/5/3-10:16 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> findThePrefixCommonArray(vector<int>& A, vector<int>& B) {
        int n = A.size();
        vector<int> res;
        vector<bool> marked(n + 1, false);
        for(int i = 0; i < n; i++) {
            marked[B[i]] = true;
            int cnt = 0;
            for(int j = 0; j <= i; j++)
                cnt += marked[A[j]];
            res.push_back(cnt);
        }
        return res;
    }

    /*
     * 因为A和B中 都是1～n的数字只出现一次
     * 所以在前缀i处，出现两次的数字才是公共的
     */
    vector<int> findThePrefixCommonArray2(vector<int>& A, vector<int>& B) {
        int n = A.size();
        vector<int> res, count(n + 1, 0);
        for(int i = 0, cnt = 0; i < n; i++) {
            if(++count[A[i]] == 2) cnt++;
            if(++count[B[i]] == 2) cnt++;
            res.push_back(cnt);
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}