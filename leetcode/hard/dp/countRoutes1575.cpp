/**
 * @Time : 2022/10/18-11:42 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n, fuel, start, mod = 1e9 + 7;
    vector<vector<int>> cache; // cache[i][f]从start到达点i处，还剩f的油的方案数
    int countRoutes(vector<int>& locations, int start, int finish, int fuel) {
        n = locations.size();
        this->fuel = fuel, this->start = start;
        cache = vector(n, vector(fuel + 1, -1));
        long long res = 0;
        for(int f = 0; f <= fuel; f++){
            res = (res + count(locations, finish, f)) % mod;
        }
        return (int)res;
    }

    long long count(vector<int>& locations, int i, int f){
        if(i == start && f == fuel) return 1;
        if(cache[i][f] != -1) return cache[i][f];
        long long res = 0;
        for(int j = 0; j < n; j++){
            int add = abs(locations[i] - locations[j]);
            if(j == i || f + add > fuel) continue;
            res = (res + count(locations, j, f + add)) % mod;
        }
        cache[i][f] = res;
        return res;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}