/**
 * @Time : 2023/12/17-9:42 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    string s;
    cin >> s;
    int n = s.size();
    vector<vector<int>> arr(26);
    for(int i = 0; i < n; i++)
        arr[s[i] - 'a'].push_back(i);
    function<int(vector<int>&)> f = [](vector<int>& arr) -> int {
        int len = arr[0] + 1;
        for(int i = 0; i < arr.size() - 1; i++)
            len = max(arr[i + 1] - arr[i], len);
        return len;
    };
    int res = INT_MAX;
    for(int i = 0; i < 26; i++) {
        arr[i].push_back(n);
        res = min(res, f(arr[i]));
    }
    cout << res << endl;
}