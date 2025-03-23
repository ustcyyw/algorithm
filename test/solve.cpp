#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 1e5 + 5, M = 1e6 + 5;
int n, a[N], divide[M];
vector<int> dp[505][101];

void solve() {
    dp[0][0][0] = 1;
    for(int i = 1; i <= n; i++) {
        int num = a[i];
        for(int x = 1; x <= 100; x++) {
            dp[i][x] = vector(10000 / x + 2, 0);
            for(int y = 1; y * x <= 1e4; y++) {
                dp[i][x][y] = dp[i-1][x][y];
                if(x - num >= 0) dp[i][x][y] |= dp[i-1][x - num][y];
                if(y - num >= 0) dp[i][x][y] |= dp[i-1][x][y - num];
            }
        }
    }
}

class Solution {
public:

};

int main() {
    vector<int> arr1 = {8,10,9};
    vector<int> arr2 = {10,6,6};
    vector<int> arr3 = {1, 2, 3};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr5 = {"aa","ac"};
    vector<vector<int>> arr4 = {{1,2,2,2,2},{2,2,2,2,0},{2,0,0,0,0},{0,0,2,2,2},{2,0,0,2,0}};
//    vector<vector<int>> arr4 = {{1,0,8}};
}
