/**
 * @Time : 2024/2/28-10:15 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 按题意模拟即可
  */
#include<bits/stdc++.h>
using namespace std;

const int N = 1e6, dx[8] = {0,0,1,-1,1,1,-1,-1}, dy[8] = {1,-1,0,0,1,-1,1,-1};
int isPrime[N + 5];
int init = []() {
    fill(isPrime, isPrime + N + 1, 1);
    vector<int> prime;
    for (int i = 2; i <= N; ++i) {
        if (isPrime[i] == 1) prime.push_back(i);
        for (int j = 0; j < prime.size() && i * prime[j] <= N; ++j) {
            isPrime[i * prime[j]] = 0;
            if (i % prime[j] == 0)
                break;
        }
    }
    return 0;
}();
class Solution {
public:
    int mostFrequentPrime(vector<vector<int>>& mat) {
        int n = mat.size(), m = mat[0].size();
        unordered_map<int, int> map;
        function<void(int,int,int,int,int)> f = [&](int x, int y, int dx, int dy, int num) -> void {
            if(num > 10 && isPrime[num]) map[num]++;
            int nx = x + dx, ny = y + dy;
            if(nx >= 0 && ny >= 0 && nx < n && ny < m)
                f(nx, ny, dx, dy, num * 10 + mat[nx][ny]);
        };
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                for(int k = 0; k < 8; k++)
                    f(i, j, dx[k], dy[k], mat[i][j]);
            }
        }
        int cnt = 0, res = -1;
        for(auto& p : map) {
            if(p.second > cnt) cnt = p.second, res = p.first;
            if(p.second == cnt && p.first > res) res = p.first;
        }
        return res;
    }
};