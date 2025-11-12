/**
 * @Time : 2025/4/2-12:52 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF990D 1700 构造 思维
 */
 /*
  * 但凡正图中有两个分量 (a1,a2,a3), (b1, b2)
  * 反图中一定有边 a1-b1, a1-b2, a2-b1, a2-b2, a3-b1, a3-b2
  * a1,a2,a3通过b1在一个分量，b1,b2通过a1在同一个分量 所有点在一个分量中
  * 正图中有更多分量的情况下 反图也一定只有一个分量
  * 正图和反图 不可能同时出现2个及以上分量
  *
  * 假设正图只有1个分量（有多个就和反图交换以下矩阵即可）
  * 反图有b个分量，画图发现 可以将一个点与其它点全部连起来 这个点在反图中就是单独一个分量
  * 因此需要将b-1个点分别与其它点都连起来
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
const int N = 1e5 + 15, M = 30;
int n, a, b;

bool check() {
    if(a > 1 && b > 1) return false;
    if(n == 1) return true;
    if(n <= 3 && a == 1 && b == 1) return false;
    return true;
}

void solve(){
    vector<string> matrix(n, string(n, '0'));
    int flag = 0;
    if(a > b) swap(a, b), flag = 1;
    for(int i = 0; i < n - 1; i++)
        matrix[i][i + 1] = matrix[i + 1][i] = '1';
    for(int i = 1; i <= b - 1; i++) {
        for(int j = 0; j < n; j++)
            if(i != j) matrix[i][j] = matrix[j][i] = '1';
    }
    if(flag == 1) {
        for(int i = 0; i < n; i++) {
            for(int j = i + 1; j < n; j++) {
                if(matrix[i][j] == '1')
                    matrix[i][j] = matrix[j][i] = '0';
                else matrix[i][j] = matrix[j][i] = '1';
            }
        }
    }
    for(string& line : matrix)
        cout << line << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> a >> b;
    if(!check()) cout << "NO";
    else {
        cout << "YES\n";
        solve();
    }
}