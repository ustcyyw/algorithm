#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int P = 13331;

class Solution {
public:
    int solve(int a, int b) {
        cout << "0: " << a << " " << b << "\n";
        int i = 1;
        while(true) {
            int c = abs(a - b);
            a = b, b = c;
            cout << i << ": " << a << " " << b << "\n";
            if(a == 0) return i;
            i++;
        }
        return -1;
    }

    int dfs(int a, int b) {
        if(a == 0) return 0;
        if(b == 0) return 1;
        if(a <= b) return 2 + dfs(b - a, a);
        int c = a / b;
        if(c == 1) return 1 + dfs(b, a - b);
        if(c % 2 == 0) {
            int t = dfs(a % b, b);
            return c / 2 * 3 + t;
        }
        else {
            int t = dfs(a % b + b, b);
            return (c - 1) / 2 * 3 + t;
        }
    }
};

int main() {
    vector<int> arr1 = {3,8,7,8,7,5};
    vector<int> arr2 = {2,3,4};
    vector<int> arr3 = {1,2,3};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr5 = {"cd", "bcd", "xyz"};
    vector<vector<int>> arr4 = {{0,1},{0,2},{0,3},{0,4}};
    vector<vector<int>> arr6 = {{0,1},{1,2},{1,3}};
    Solution s;
    int a = 101, b = 24513;
    cout << s.solve(a, b) << "\n";
    cout << s.dfs(a, b) << "\n";
//    cout << s.dfs(10000, 1);
}
