/**
 * @Time : 2025/2/20-10:48 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF710C 1500 构造
 */
 /*
  * 每行每列和主对角线 奇数的个数c1, c1是一个奇数
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 3e5 + 5;
int n, matrix[50][50];

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    cin >> n;
    int mid = (n + 1) / 2, num = 1;
    for(int i = 1; i <= n; i++, num += 2)
        matrix[mid][i] = num;
    for(int j = 1; mid + j <= n; j++) {
        for(int i = 1 + j; i <= n - j; i++) {
            matrix[mid + j][i] = num;
            num += 2;
            matrix[mid - j][i] = num;
            num += 2;
        }
    }
    for(int i = 1, num = 2; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(matrix[i][j] == 0) {
                matrix[i][j] = num;
                num += 2;
            }
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
};