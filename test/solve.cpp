#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 1e5 + 5, M = 1e6 + 5;
int l1, r1, l2, r2, divide[M];

int init = []() -> int {
    for(int i = 1; i < M; i++) {
        for(int j = 1; j * i < M; j++)
            divide[j * i]++;
    }
    return 0;
}();

int cal(int num) {
    int cnt = 0;
    while(divide[num] != num) {
        cnt++;
        num = divide[num];
    }
    return cnt;
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
    int v = 0;
    for(int i = 1; i < M; i++) {
        v = max(cal(i), v);
    }
    cout << v;
}
