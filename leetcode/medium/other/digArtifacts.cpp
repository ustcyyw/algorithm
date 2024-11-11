/**
 * @Time : 2022/8/11-1:04 PM
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
     * 执行用时：408 ms, 在所有 C++ 提交中击败了90.57%的用户
     * 内存消耗：142.6 MB, 在所有 C++ 提交中击败了94.34%的用户
     */
    int digArtifacts(int n, vector<vector<int>>& artifacts, vector<vector<int>>& dig) {
        vector<vector<bool>> grid = vector(n, vector(n ,false));
        for(auto& d : dig)
            grid[d[0]][d[1]] = true;
        int res = 0;
        for(auto& artifact : artifacts)
            if(check(grid, artifact)) res++;
        return res;
    }

    bool check(vector<vector<bool>>& grid, vector<int>& a){
        for(int i = a[0]; i <= a[2]; i++)
            for(int j = a[1]; j <= a[3]; j++)
                if(!grid[i][j]) return false;
        return true;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}