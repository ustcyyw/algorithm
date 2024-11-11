/**
 * @Time : 2022/8/17-8:02 PM
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
     * 执行用时：16 ms, 在所有 C++ 提交中击败了40.35%的用
     * 户内存消耗：9.3 MB, 在所有 C++ 提交中击败了17.10%的用户
     */
    int mod = 1e9 + 7;
    int dx[3] = {0,-1,-1}, dy[3] = {-1,-1,0};
    vector<int> pathsWithMaxScore(vector<string>& board) {
        int n = board.size(), m = board[0].size();
        vector<vector<int>> sum = vector(n, vector(m, 0));
        vector<vector<long>> ways = vector(n, vector(m, 0l));
        ways[0][0] = 1;
        for(int i = 1; i < n && board[i][0] != 'X'; i++)
            ways[i][0] = 1, sum[i][0] = sum[i - 1][0] + board[i][0] - '0';
        for(int j = 1; j < m && board[0][j] != 'X'; j++)
            ways[0][j] = 1, sum[0][j] = sum[0][j - 1] + board[0][j] - '0';
        for(int i = 1; i < n; i++){
            for(int j = 1; j < m; j++){
                if(board[i][j] == 'X') continue;
                for(int k = 0; k < 3; k++){
                    int px = i + dx[k], py = j + dy[k];
                    if(board[px][py] == 'X') continue;
                    if(sum[i][j] == sum[px][py])
                        ways[i][j] = (ways[i][j] + ways[px][py]) % mod;
                    else if(sum[i][j] < sum[px][py]){
                        sum[i][j] = sum[px][py];
                        ways[i][j] = ways[px][py];
                    }
                }
                if(sum[i][j] != 0 && (i != n - 1 || j != m - 1))
                    sum[i][j] += board[i][j] - '0';
            }
        }
        return {sum[n - 1][m - 1], (int)ways[n - 1][m - 1]};
    }
};

int main(){
    Solution s;
    vector<string> b = {"E23","2X2","12S"};
    s.pathsWithMaxScore(b);
    cout << 0 << endl;
}