/**
 * @Time : 2022/6/27-2:37 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int m, n, k;
    int kthSmallest(vector<vector<int>>& mat, int k) {
        n = mat.size(), m = mat[0].size();
        this->k = k;
        long max = 0, min = 0;
        for(vector<int>& row : mat)
            max += row[m - 1], min += row[0];
        int lo = min, hi = max;
        while (lo < hi){
            int mid = (lo + hi) >> 1;
            if(dfs(mat, min, 0, mid) < k) lo = mid + 1;
            else hi = mid;
        }
        return lo;
    }

    // 和小于等于key的组合数量
    int dfs(vector<vector<int>>& mat, int sum, int row, int key){
        int count = 0;
        if(row == n - 1){
            for(int i = 0; i < m; i++){
                if(sum - mat[row][0] + mat[row][i] <= key) count++;
                else break;
            }
            return count;
        }
        // 给定一个初始和是每个数组的第一列之和，其它数组和，在对行枚举的时候将第一个元素与所枚举的元素交换就可以求出新的和
        for(int i = 0; i < m; i++){
            int newSum = sum - mat[row][0] + mat[row][i];
            if(newSum <= key)
                count += dfs(mat, newSum, row + 1, key);
            else break;
            if(count > k) return count; // 很关键的剪枝
        }
        return count;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}