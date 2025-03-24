#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 1e5 + 5, M = 1e6 + 5;
ll p4[20];

int init = []() -> int {
    p4[0] = 1;
    for(int i = 1; i < 20; i++)
        p4[i] = p4[i - 1] * 4;
    return 0;
}();

class Solution {
public:
    long long minOperations(vector<vector<int>>& queries) {
        ll ans = 0;
        for(auto& q : queries) {
            ans += cal(q[0], q[1]);
        }
        return ans;
    }

    ll cal(int l, int r) {
        int lo = find(l), hi = find(r);
        ll ans = 0;
        if(lo == hi) ans = (ll)(r - l + 1) * (lo + 1);
        else {
            ans = (p4[lo + 1] - l) * (lo + 1) + (r - p4[hi] + 1) * (hi + 1);
            for(int i = lo + 1; i <= hi - 1; i++)
                ans = ans + (p4[i + 1] - p4[i]) * (i + 1);
        }
        return (ans + 1) / 2;
    }

    int find(int num) {
        for(int i = 19; i >= 0; i--)
            if(num >= p4[i]) return i;
        return -1;
    }
};

int main() {
    vector<int> arr1 = {8,10,9};
    vector<int> arr2 = {10,6,6};
    vector<int> arr3 = {1, 2, 3};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr5 = {"aa","ac"};
    vector<vector<int>> arr4 = {{14,37}};
//    vector<vector<int>> arr4 = {{1,0,8}};
    Solution s;
    s.minOperations(arr4);
}
