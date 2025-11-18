#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 1e5 + 5;

class Solution {
public:
    int minLengthAfterRemovals(string s) {
        int c1 = 0, c2 = 0;
        for(char c : s) {
            if(c == 'a') c1++;
            else c2++;
        }
        return abs(c1 - c2);

        set<int> st;
        upper_bound(st.begin(), st.end(), val);
    }
};

int main() {
    vector<int> arr1 = {3,1,2};
    vector<int> arr2 = {2,3};
    vector<int> arr3 = {17};
    vector<string> arr5 = {"aa", "ac"};
    vector<vector<int>> arr4 = {{0,1},{1,2},{0,2}};
    Solution s;
}
