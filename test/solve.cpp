#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 1e5 + 5, P = 13331;
int l1, r1, l2, r2, pow2[32];

int init = []() -> int {
   pow2[0] = 1;
   for(int i = 1; i < 32; i++)
       pow2[i] = pow2[i - 1] * 2;
    return 0;
}();

void add(vector<int>& arr, int num) {
    for(int i = 0; i < 32; i++) {
        if((1 << i) & num)
            arr.push_back(pow2[i]);
    }
}

vector<int> cal(int l, int r) {
    vector<int> arr;
    for(int i = 0; i < 32; i++) {
        if(pow2[i] > r) {
            int mid = pow2[i - 1];
            add(arr, mid - l), add(arr, r - mid);
        }
    }
    return arr;
}

void solve() {
    vector<int> arr1 = cal(l1, r1), arr2 = cal(l2, r2);
    ll ans = 0;
    for(int n1 : arr1) {
        for(int n2 : arr2) {
            int t = min(n1, n2);
            ans += t / n1 * t / n2;
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
    vector<vector<int>> arr4 = {{1,2,2,2,2},{2,2,2,2,0},{2,0,0,0,0},{0,0,2,2,2},{2,0,0,2,0}};
//    vector<vector<int>> arr4 = {{1,0,8}};

}
