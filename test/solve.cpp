#include<bits/stdc++.h>

using namespace std;
const int N = 1e5 + 5;

map<int, int> mp;

int pre_num(int num) {
    auto it = mp.lower_bound(num);
    it--;
    return it->first;
}

class Solution {
public:

};

int main() {
    vector<int> arr1 = {14,-1,-1,46};
    vector<int> arr3 = {7, 19, 19, 20, 33};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr2 = {"000", "000"};
    vector<string> arr5 = {"cd", "bcd", "xyz"};
    vector<vector<int>> arr4 = {{-2,3},{2,3},{2,1}};
    vector<vector<int>> arr6 = {{0,0}};
    Solution s;
    mp[1] = 10, mp[5] = 12, mp[2] = 3;
    cout << pre_num(10);
}
