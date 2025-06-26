#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 1e5 + 5, M = 1e6 + 5;

class Solution {
public:
    int solve(string s) {
        map<char, int> mp;
        for(char c : s)
            mp[c]++;
        for(int i = 0; i < s.size(); i++)
            if(mp[s[i]] == 1) return i + 1;
        return -1;
    }

    int solve(vector<int> stocksProfits, int target) {
        map<int, int> map;
        for(int num : stocksProfits)
            map[num]++;
        int cnt = target % 2 == 0 && map[target / 2] > 1;
        for(auto& p : map) {
            int num = p.first, c = p.second;
            if(map[target - num] > 0 && num < target - num) cnt++;
        }
        return cnt;
    }
};

int main() {
    vector<int> arr1 = {8, 10, 9};
    vector<int> arr2 = {10, 6, 6};
    vector<int> arr3 = {1, 2, 3};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr5 = {"aa", "ac"};
    vector<vector<int>> arr4 = {{14, 37}};
}
