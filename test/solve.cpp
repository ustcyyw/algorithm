#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, N = 3e4 + 5, P = 13331;

void cal(string str) {
    int u = (1 << str.size()) - 1;
    ll ans = 0;
    for(int s = 1; s <= u; s++) {
        string temp;
        for(int i = 0; i < str.size(); i++) {
            if((1 << i) & s) temp.push_back(str[i]);
        }
        for(int i = 0, pre = -1; i < temp.size(); i++) {
            if(temp[i] != pre) ans++;
            pre = temp[i];
        }
    }
    cout << ans << "\n";
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
    vector<vector<int>> arr4 = {{3,0,5},{3,1,6},{2,3,5}};
//    vector<vector<int>> arr4 = {{1,0,8}};
    Solution s;
    cal("101");
    cal("1011");
    cal("10110");
    cal("101110101");
}
