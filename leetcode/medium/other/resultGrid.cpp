/**
 * @Time : 2024/2/5-9:44 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛383 t3
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n, m, t, dx[4] = {0,0,1,-1}, dy[4] = {1,-1,0,0};
    vector<vector<int>> sum, cnt, image;
    vector<vector<int>> resultGrid(vector<vector<int>>& image, int threshold) {
        n = image.size(), m = image[0].size(), t = threshold;
        sum = vector(n, vector(m, 0)), cnt = vector(n, vector(m, 0));
        this->image = image;
        for(int i = 0; i <= n - 3; i++) {
            for(int j = 0; j <= m - 3; j++) {
                int temp = check(i, j);
                if(temp != -1) fill(i, j, temp);
            }
        }
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(cnt[i][j] == 0) sum[i][j] = image[i][j];
                else sum[i][j] /= cnt[i][j];
            }
        }
        return sum;
    }

    void fill(int x, int y, int val) {
        for(int i = 0; i <= 2; i++) {
            for (int j = 0; j <= 2; j++) {
                int cx = x + i, cy = y + j;
                cnt[cx][cy]++, sum[cx][cy] += val;
            }
        }
    }

    int check(int x, int y) {
        int xb = x + 2, yb = y + 2, sum = 0;
        for(int i = 0; i <= 2; i++) {
            for(int j = 0; j <= 2; j++) {
                int cx = x + i, cy = y + j;
                for(int k = 0; k < 4; k++) {
                    int nx = cx + dx[k], ny = cy + dy[k];
                    if(nx < x || ny < y || nx > xb || ny > yb) continue;
                    if(abs(image[nx][ny] - image[cx][cy]) > t) return -1;
                }
                sum += image[cx][cy];
            }
        }
        return sum / 9;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}