/**
 * @Time : 2023/12/26-11:39 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛377 t3 floyd最短路
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long minimumCost(string source, string target, vector<char>& original,
                          vector<char>& changed, vector<int>& cost) {
        vector<vector<int>> dis(26, vector(26, (int)1e9));
        for(int i = 0; i < cost.size(); i++) {
            int v = original[i] - 'a', w = changed[i] - 'a';
            dis[v][w] = min(dis[v][w], cost[i]);
        }
        for(int k = 0; k < 26; k++) {
            for(int i = 0; i < 26; i++) {
                for(int j = 0; j < 26; j++)
                    dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
        long long res = 0;
        for(int i = 0; i < target.size(); i++) {
            if(target[i] != source[i]) {
                int v = source[i] - 'a', w = target[i] - 'a';
                if(dis[v][w] == (int)1e9) return -1;
                res += dis[v][w];
            }
        }
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}