#include<bits/stdc++.h>

using namespace std;
const int N = 1e5 + 5;
typedef long long ll;

class Solution {
public:

};

int main() {
    vector<int> arr1 = {1,2,3};
    vector<int> arr2 = {2,3,4};
    vector<int> arr3 = {1,2,3};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr5 = {"cd", "bcd", "xyz"};
    vector<vector<int>> arr4 = {{0,1},{0,2},{0,3},{0,4}};
    vector<vector<int>> arr6 = {{0,1},{1,2},{1,3}};
    Solution s;
    map<int, int> mp;
    mp[1] = 1, mp[3] = 2, mp[5] = 3;
    int k = (--mp.upper_bound(1))->first;
    cout << k;
}
