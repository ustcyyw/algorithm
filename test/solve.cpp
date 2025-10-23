#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 1e5 + 5;

vector<int> divide[N];

int init = []() -> int {
    for(int i = 1; i < N; i++) {
        for(int j = i; j < N; j += i)
            divide[j].push_back(i);
    }
    return 0;
}();


class Solution {
public:
    int diff = INT_MAX;
    vector<int> ans;
    vector<int> minDifference(int n, int k) {
        vector<int> arr;
        dfs(arr, n, k);
        return ans;
    }

    void dfs(vector<int>& arr, int num, int k) {
        if(num == 1 || arr.size() >= k) {
            if(num == 1 && check(arr, k)) ans = arr;
            return;
        }
        for(int d : divide[num]) {
            if(arr.empty() || arr.back() <= d) {
                arr.push_back(d);
                dfs(arr, num / d, k);
                arr.pop_back();
            }
        }
    }

    bool check(vector<int>& arr, int k) {
        if(arr.size() != k) return false;
        int v1 = arr[0], v2 = arr[0];
        for(int num : arr)
            v1 = min(num, v1), v2 = max(num, v2);
        if(v2 - v1 < diff) {
            diff = v2 - v1;
            return true;
        }
        return false;
    }
};

int main() {
    vector<int> arr1 = {14,8,9,10,13,5,15,15,1,14,3,15,2,2,15};
    vector<int> arr3 = {42,24,35};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr5 = {"aa", "ac"};
    vector<vector<int>> arr4 = {{0,1},{2,0},{1,2}};
    Solution s;
}
