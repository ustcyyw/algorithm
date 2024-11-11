/**
 * @Time : 2023/12/7-12:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    int n, k;
    vector<vector<int>> infos;
    cin >> n >> k;
    for(int i = 1, a, b; i <= n; i++) {
        cin >> a >> b;
        infos.push_back({a, b});
    }
    sort(infos.begin(), infos.end(), [](auto& a, auto& b) -> bool {return a[1] < b[1];});
    priority_queue<int, vector<int>, greater<>> pq;
    long long sum = 0, res = 0;
    for(int i = n - 1, j; i >= 0; ) {
        j = i;
        while(j >= 0 && infos[j][1] == infos[i][1]) {
            pq.push(infos[j][0]);
            sum += infos[j][0];
            if(pq.size() > k) {
                sum -= pq.top();
                pq.pop();
            }
            j--;
        }
        res = max(res, sum * infos[i][1]);
        i = j;
    }
    cout << res << endl;
}