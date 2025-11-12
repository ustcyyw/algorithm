/**
 * @Time : 2024/11/19-9:25 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2037D 贪心 优先队列 1300
 */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, m, L, hurdle[N][2], power[N][2];

int solve() {
    priority_queue<int> pq;
    int k = 1, cnt = 0;
    for(int i = 1, j = 1; i <= n; i++) {
        while(j <= m && power[j][0] < hurdle[i][0])
            pq.push(power[j++][1]);
        while(k < hurdle[i][1] - hurdle[i][0] + 2 && !pq.empty()) {
            k += pq.top(), cnt++;
            pq.pop();
        }
        if(k < hurdle[i][1] - hurdle[i][0] + 2) return -1;
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T--) {
        cin >> n >> m >> L;
        for(int i = 1; i <= n; i++)
            cin >> hurdle[i][0] >> hurdle[i][1];
        for(int i = 1; i <= m; i++)
            cin >> power[i][0] >> power[i][1];
        cout << solve() << "\n";
    }
};