#include<bits/stdc++.h>

using namespace std;
const int N = 1e5 + 5, mod = 1e9 + 7;
typedef long long ll;

class Solution {
public:
    int get_gcd(int i, int num) {
        return i == 0 ? num : gcd(i, num);
    }

    int subsequencePairCount(vector<int>& nums) {
        int n = nums.size();
        if(n == 1) return 0;
        unordered_map<int, unordered_map<int, ll>> pre, cur;
        pre[0][0] = 1;
        for(int num : nums) {
            cur.clear();
            for(auto& p1 : pre) {
                int i = p1.first, g1 = get_gcd(i, num);
                for(auto& p2 : p1.second) {
                    int j = p2.first, g2 = get_gcd(j, num);
                    ll cnt = p2.second;
                    cur[i][j] = (cur[i][j] + cnt) % mod;
                    cur[g1][j] = (cur[g1][j] + cnt) % mod;
                    cur[i][g2] = (cur[i][g2] + cnt) % mod;
                }
            }
            swap(cur, pre);
        }
        ll ans = 0;
        for(int i = 1; i <= 200; i++)
            ans = (pre[i][i] + ans) % mod;
        return ans;
    }
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
