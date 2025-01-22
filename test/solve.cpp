#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 1e9 + 7, N = 1e5 + 5;

vector<int> divisors[N];
int init = []() {
    for (int i = 1; i < N; ++i)
        for (int j = i; j < N; j += i)
            divisors[j].push_back(i);
    return 0;
}();

class Solution {
public:
    int maxAdjacentDistance(vector<int>& nums) {
        int n = nums.size(), ans = abs(nums[0] - nums[n - 1]);
        for(int i = 0; i < n - 1; i++)
            ans = max(ans, abs(nums[i] - nums[i + 1]));
        return ans;
    }
};

void dfs(vector<map<int, int>>& fac, vector<int>& arr, int num) {
    if(num == 1) {
        map<int, int> mp;
        for(int m : arr)
            mp[m]++;
        fac.push_back(mp);
        return;
    }
    int pre = arr.empty() ? -1 : arr.back();
    for(int d : divisors[num]) {
        if(d == 1 || d < pre) continue;
        if(num / d < d && num / d != 1) continue;
        arr.push_back(d);
        dfs(fac, arr, num / d);
        arr.pop_back();
    }
}

int main() {
    vector<int> arr1 = {2,2,2,1};
    vector<ll> arr2 = {5,3,1,0};
    vector<int> arr3 = {1, 2, 3};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr5 = {"cd", "bcd", "xyz"};
    vector<vector<int>> arr4 = {{3,0,5},{3,1,6},{2,3,5}};
//    vector<vector<int>> arr4 = {{1,0,8}};
    Solution s;
    vector<map<int, int>> fac;
    vector<int> arr;
    dfs(fac, arr, 2);
    cout << fac.size() << "\n";

    multimap<int, ll> mp;
    mp.insert({1, 100}), mp.insert({1, 123}), mp.insert({2, 1});
    for(auto& p : mp)
        cout << p.first << " " << p.second << "\n";
}
