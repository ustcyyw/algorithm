/**
 * @Time : 2023/4/23-8:54 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int fieldOfGreatestBlessing(vector<vector<int>>& forceField) {
        vector<vector<double>> ranges;
        unordered_set<double> posX, posY;
        for(auto& info : forceField) {
            int x = info[0], y = info[1];
            double half = info[2] * 1.0 / 2;
            double x1 = x - half, y1 = y - half, x2 = x + half, y2 = y + half;
            ranges.push_back({x1, y1, x2, y2});
            posX.insert(x1), posX.insert(x2);
            posY.insert(y1), posY.insert(y2);
        }
        unordered_map<double, int> mapX = scatter(posX), mapY = scatter(posY);
        int n = mapX.size(), m = mapY.size();
        vector<vector<int>> diff(n + 1, vector(m + 1, 0));
        for(vector<double> info : ranges) {
            int x1 = mapX[info[0]], y1 = mapY[info[1]];
            int x2 = mapX[info[2]], y2 = mapY[info[3]];
            diff[x1][y1] += 1;
            diff[x2 + 1][y1] -= 1;
            diff[x1][y2 + 1] -= 1;
            diff[x2 + 1][y2 + 1] += 1;
        }
        vector<vector<int>> arr = diffToArray(diff);
        int res = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++)
                res = max(res, arr[i][j]);
        }
        return res;
    }

    vector<vector<int>> diffToArray(vector<vector<int>>& diff){
        int n = diff.size() - 1, m = diff[0].size() - 1;
        vector<vector<int>> arr(n, vector(m, 0));
        for(int i = 0; i < n; i++){
            for(int j = 0, lineSum = 0; j < m; j++){
                lineSum += diff[i][j];
                arr[i][j] = (i == 0 ? 0 : arr[i - 1][j]) + lineSum;
            }
        }
        return arr;
    }

    unordered_map<double, int> scatter(unordered_set<double>& pos){
        vector<double> list;
        for(double num : pos)
            list.push_back(num);
        sort(list.begin(), list.end());
        unordered_map<double, int> map;
        for(int i = 0; i < list.size(); i++)
            map[list[i]] = i;
        return map;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}