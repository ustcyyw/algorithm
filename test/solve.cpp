#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 1e5 + 5, P = 13331;

class Solution {
public:
    long long maxSubarrays(int n, vector<vector<int>>& conflictingPairs) {

    }
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
