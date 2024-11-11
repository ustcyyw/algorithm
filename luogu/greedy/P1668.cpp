/**
 * @Time : 2023/5/9-9:57 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

int n, t;

int max_range(vector<int>& range, int lo, int hi) {
    int ans = -1;
    for(int i = lo; i <= hi; i++)
        ans = max(ans, range[i]);
    return ans;
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); // 加速cin, cout
    cin >> n >> t;
    vector<int> range(t + 1, -1);
    for(int i = 0, s, e; i < n; i++) {
        cin >> s >> e;
        range[s] = max(range[s], e);
    }
    if(range[1] == -1) {
        cout << -1 << endl;
        return 0;
    }
    int cnt = 1;
    for(int lo = 1, hi = range[1]; hi < t; cnt++) {
        int temp = max_range(range, lo, hi + 1);
        if(temp == -1) {
            cout << -1 << endl;
            return 0;
        }
        lo = hi + 1, hi = temp;
    }
    cout << cnt << endl;
}