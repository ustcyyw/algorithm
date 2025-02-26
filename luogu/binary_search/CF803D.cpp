/**
 * @Time : 2025/2/25-8:25 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF803D 1900 二分答案
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 1e3 + 5, M = 400;
int n, k;
string s;
vector<int> arr;

bool check(int len) {
    int cnt = 0;
    for(int i = 0, j = 0, pre = 0; i < n && cnt <= k; i = j, cnt++) {
        while(j < n && arr[j] - pre + 1 <= len)
            j++;
        if(i == j) return false;
        pre = arr[j - 1] + 1;
    }
    return cnt <= k;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> k;
    getline(cin, s);
    getline(cin, s);
    for(int i = 0; i < s.size(); i++)
        if(s[i] == '-' || s[i] == ' ') arr.push_back(i);
    arr.push_back(s.size() - 1);
    n = arr.size();
    int lo = 1, hi = s.size();
    while(lo < hi) {
        int mid = (lo + hi) >> 1;
        if(check(mid)) hi = mid;
        else lo = mid + 1;
    }
    cout << lo << "\n";
}