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
    vector<int> arr1 = {1,2,3};
    vector<int> arr2 = {2,3,4};
    vector<int> arr3 = {1,2,3};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr5 = {"cd", "bcd", "xyz"};
    vector<vector<int>> arr4 = {{-2,3},{2,3},{2,1}};
    vector<vector<int>> arr6 = {{0,0}};
    Solution s;
    cout << (arr1 == arr3);
    cout << (arr1 == arr2);
}
