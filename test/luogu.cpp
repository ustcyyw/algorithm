/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 100 + 5, P = 13331;
int n, q, c;
vector<vector<ll>> sum[11];

void getPreSum(vector<vector<ll>>& nums){
    for(int i = 1; i < N; i++){
        ll lineSum = 0;
        for(int j = 1; j < N; j++){
            lineSum += nums[i][j];
            nums[i][j] = nums[i - 1][j] + lineSum;
        }
    }
}

ll sumOf(vector<vector<ll>>& preSum, int x1, int y1, int x2, int y2){
    return preSum[x2][y2] - preSum[x1 - 1][y2] - preSum[x2][y1 - 1] + preSum[x1 - 1][y1 - 1];
}

void cal(int x1, int y1, int x2, int y2, int t) {
    ll ans = 0;
    for(int i = 0; i <= c; i++) {
        int cnt = sumOf(sum[i], x1, y1, x2, y2);
        ans += cnt * ((i + t) % (c + 1));
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> q >> c;
    for(int i = 0; i <= c; i++)
        sum[i] = vector(N, vector(N, 0ll));
    for(int i = 1, x, y, s; i <= n; i++) {
        cin >> x >> y >> s;
        sum[s][x][y] += 1;
    }
    for(int i = 0; i <= c; i++)
        getPreSum(sum[i]);
    for(int i = 1, x1, x2, y1, y2, t; i <= q; i++) {
        cin >> t >> x1 >> y1 >> x2 >> y2;
        if(x1 > x2) swap(x1, x2);
        if(y1 > y2) swap(y1, y2);
        cal(x1, y1, x2, y2, t);
    }
}