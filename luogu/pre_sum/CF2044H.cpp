/**
 * @Time : 2024/12/16-8:34 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2044H 前缀和 思维
 */
/*
  * 从一行来看 从一列来看 系数都是等差数列
  * 所以可以想到 用系数递增的序列来凑区域上的和
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, q;
// row[i][j] = base[i][j] * j 在某一行内是从左往右系数递增的
// col[i][j] = base[i][j] * i 在某一列内是从上往下系数递增的
vector<vector<int>> base, row, col;
vector<vector<ll>> sum, sumR, sumC;

vector<vector<ll>> getPreSum(vector<vector<int>>& nums){
    vector<vector<ll>> preSum(n + 1, vector(n + 1, 0ll));
    for(int i = 1; i <= n; i++){
        ll lineSum = 0;
        for(int j = 1; j <= n; j++){
            lineSum += nums[i][j];
            preSum[i][j] = preSum[i - 1][j] + lineSum;
        }
    }
    return preSum;
}

/*
 * 根据二维前缀和求原矩形区域上的和
 * 左上角坐标 x1,y1; 右下角坐标 x2,y2
 */
ll sumOf(vector<vector<ll>>& preSum, int x1, int y1, int x2, int y2){
    return preSum[x2][y2] - preSum[x1 - 1][y2] - preSum[x2][y1 - 1] + preSum[x1 - 1][y1 - 1];
}

void cal() {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    ll ans = sumOf(sumR, x1, y1, x2, y2);
    ans -= (y1 - 1) * sumOf(sum, x1, y1, x2, y2);
    ans += (y2 - y1 + 1) * (sumOf(sumC, x1, y1, x2, y2) - x1 * sumOf(sum, x1, y1, x2, y2));
    cout << ans << " ";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T-- > 0) {
        cin >> n >> q;
        base = vector(n + 1, vector(n + 1, 0));
        row = vector(n + 1, vector(n + 1, 0));
        col = vector(n + 1, vector(n + 1, 0));
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                cin >> base[i][j];
                row[i][j] = base[i][j] * j, col[i][j] = base[i][j] * i;
            }
        }
        sum = getPreSum(base), sumR = getPreSum(row), sumC = getPreSum(col);
        for(int i = 1; i <= q; i++)
            cal();
        cout << "\n";
    }
};