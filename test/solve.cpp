#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 1e5 + 5, M = 1e6 + 5;

class Solution {
public:

};

int main() {
    vector<int> arr1 = {8, 10, 9};
    vector<int> arr2 = {10, 6, 6};
    vector<int> arr3 = {1, 2, 3};
    vector<int> w = {6, 6, 3, 9, 3, 5, 1};
    vector<string> arr5 = {"aa", "ac"};
    vector<vector<int>> arr4 = {{14, 37}};
//    vector<vector<int>> arr4 = {{1,0,8}};
//    cin >> s;
//    n = s.size();
//    while(1) {
//        cin >> m;
//        string pre = s.substr(0, m), suf = s.substr(n - m, m);
//        string mid = s.substr(m, n - 2 * m);
//        reverse(pre.begin(), pre.end()), reverse(suf.begin(), suf.end());
//        s = suf + mid + pre;
//        cout << s << "\n";
//    }
    int h[6] = {0, 1, 2, 4, 5, 7};
    cout << lower_bound(h + 1, h + 5 + 1, 3) - h;
}
