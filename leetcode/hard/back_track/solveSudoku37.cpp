/**
 * @Time : 2023/3/22-9:11 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<vector<bool>> row, col, box;
    void solveSudoku(vector<vector<char>>& board) {
        row = vector(9, vector(10, false));
        col = vector(9, vector(10, false));
        box = vector(9, vector(10, false));
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                if(board[i][j] == '.') continue;
                int num = board[i][j] - '0', box_id = i / 3 * 3 + j / 3;
                row[i][num] = col[j][num] = box[box_id][num] = true;
            }
        }
        backTrack(board, 0, 0);
    }

    bool backTrack(vector<vector<char>>& board, int i, int j){
        if(i == 9) return true;
        int ni = i + (j + 1) / 9, nj = (j + 1) % 9;
        if(board[i][j] != '.')
            return backTrack(board, ni, nj);
        for(int num = 1; num <= 9; num++){
            int box_id = i / 3 * 3 + j / 3;
            if(row[i][num] || col[j][num] || box[box_id][num]) continue;
            board[i][j] = (char)(num + '0');
            row[i][num] = col[j][num] = box[box_id][num] = true;
            if(backTrack(board, i + (j + 1) / 9, (j + 1) % 9))
                return true;
            row[i][num] = col[j][num] = box[box_id][num] = false;
            board[i][j] = '.';
        }
        return false;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}