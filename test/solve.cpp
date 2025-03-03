#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 1e5 + 5, P = 13331;

vector<vector<ll>> matrixMul(vector<vector<ll>>& A, vector<vector<ll>>& B){
    int N = A.size(), M = B[0].size(), K = A[0].size();
    vector<vector<ll>> ans(N, vector(M, 0ll));
    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            for(int k = 0; k < K; k++)
                ans[i][j] = ((ll)ans[i][j] + (A[i][k] * B[k][j]));
        }
    }
    return ans;
}

vector<vector<ll>> quickPower(vector<vector<ll>>& a, int b){
    int n = a.size(); // 能进行快速幂的矩阵 是一个方阵
    vector<vector<ll>> ans(n, vector(n, 0ll));
    for(int i = 0; i < n; i++)
        ans[i][i] = 1;
    while (b != 0){
        if((b & 1) == 1) ans = matrixMul(ans , a);
        a = matrixMul(a, a);
        b >>= 1;
    }
    return ans;
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
    vector<vector<ll>> base = {{1, 1, 1, 1, 1, 1, 1},
                               {0, 1, 1, 1, 1, 1, 1},
                               {0, 0, 1, 1, 1, 1, 1},
                               {0, 0, 0, 1, 1, 1, 1},
                               {0, 0, 0, 0, 1, 1, 1},
                               {0, 0, 0, 0, 0, 1, 1},
                               {0, 0, 0, 0, 0, 0, 1}};
    vector<vector<ll>> t = base;
    for(int i = 1; i <= 2000000; i++) {
        t = matrixMul(t, base);
        cout << t[0][5] << "\n";
        if(t[0][5] > 1e18) {
            cout << i << "\n";
            break;
        }
    }
}
