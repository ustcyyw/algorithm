#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int P = 13331;

void solve(int num) {
    map<int, vector<int>> mp;
    for(int i = 1; i <= num; i++) {
        mp[num / i].push_back(i);
    }
    cout << mp.size() << "\n";
    for(auto& [val, arr] : mp) {
        sort(arr.begin(), arr.end());
        cout << val << ": " << arr[0] << "," << arr.back() << "\n";
    }
}

class Solution {
public:

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
    solve(9999);
}
