/**
 * @Time : 2024/2/4-9:48 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 双周赛123 t4 离散化+前缀和
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<vector<int>> sum;
    int get_sum(int x1, int y1, int x2, int y2) {
        return sum[x2][y2] + sum[x1 - 1][y1 - 1] - sum[x2][y1 - 1] - sum[x1 - 1][y2];
    }

    void preSum(int m1, int m2) {
        for(int i = 1; i <= m1; i++) {
            for(int j = 1; j <= m2; j++)
                sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
        }
    }

    unordered_map<int, int> scatter(set<int>& set) {
        unordered_map<int, int> map;
        map[INT_MIN] = 1;
        int k = 2;
        for(int num : set) {
            map[num] = k++;
        }
        return map;
    }

    int numberOfPairs(vector<vector<int>>& points) {
        int n = points.size(), cnt = 0;
        set<int> set_x, set_y;
        for(auto& point : points) {
            int x1 = point[0], y1 = point[1];
            set_x.insert(x1), set_y.insert(y1);
        }
        unordered_map<int, int> mx = scatter(set_x), my = scatter(set_y);
        int m1 = mx.size(), m2 = my.size();
        sum = vector(m1 + 1, vector(m2 + 1, 0));
        for(auto& point : points) {
            int x = point[0], y = point[1];
            sum[mx[x]][my[y]] = 1;
        }
        preSum(m1, m2);
        for(int i = 0; i < n; i++) {
            int x1 = mx[points[i][0]], y1 = my[points[i][1]];
            for(int j = 0; j < n; j++) {
                if(i == j) continue;
                int x2 = mx[points[j][0]], y2 = my[points[j][1]];
                if(x2 >= x1 && y1 >= y2 && get_sum(x1, y2, x2, y1) == 2)
                    cnt++;
            }
        }
        return cnt;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}