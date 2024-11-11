/**
 * @Time : 2024/1/30-5:05 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 4e5 + 5;
int n, a, b, arr1[N], arr2[N];

bool check_in(int l, int w, int x, int y) {
    return (x <= l && y <= w) || (x <= w && y <= l);
}

bool check(vector<int>& l, vector<int>& w, int x, int y) {
    for(int i = 0; i < 4; i++)
        if(check_in(l[i], w[i], x, y)) return true;
    return false;
}

void solve() {
    int res = 0;
    for(int i = 0; i < n; i++) {
        int s1 = arr1[i] * arr2[i];
        // 第一个矩形 两种放置方式。每种放置方式 剩下的面积可以有两种划分方式得出剩余的可能最大矩形
        int l1 = a - arr1[i], w1 = b >= arr2[i] ? b : -1;
        int l2 = a - arr2[i], w2 = b >= arr1[i] ? b : -1;
        int l3 = a >= arr2[i] ? a : -1, w3 = b - arr1[i];
        int l4 = a >= arr1[i] ? a : -1, w4 = b - arr2[i];
        vector<int> ls = {l1, l2, l3, l4}, ws = {w1, w2, w3, w4};
        for(int j = i + 1; j < n; j++) {
            if(check(ls, ws, arr1[j], arr2[j]))
                res = max(s1 + arr1[j] * arr2[j], res);
        }
    }
    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> a >> b;
    for(int i = 0; i < n; i++)
        cin >> arr1[i] >> arr2[i];
    solve();
};