#include<bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int mod = 1e9 + 7, N = 1e5 + 5, M = 1e6 + 5;

// 检查 num 不断除以2 会不会变为base
bool check(int num, int base) {
    while(num > 1 && num % 2 == 0 && num != base)
        num /= 2;
    return num == base;
}

int cal(int num) {
    int cnt = 1;
    while(num % 2 == 0)
        num /= 2, cnt *= 2;
    return cnt;
}

int cal(int num, int base) {
    if(!check(num, base)) return cal(num);
    int c = num / base;
    return 1 + (c - 2) * cal(base);
}

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
    cout << cal(18, -1) << "\n";
}
