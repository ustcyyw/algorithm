/**
 * @Time : 2024/5/6-9:32 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 偶数 必须4个一组
  *
  * 奇数：
  * n - 1 个2个一组
  * 1个单独一组
  * 其余4个一组
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int n, grid[21][21];
unordered_map<int, int> cnt;
vector<int> a4, a2, a1;

bool solve() {
    for(auto& p : cnt) {
        int num = p.first, t = p.second;
        for(; t >= 4; t -= 4)
            a4.push_back(num);
        for(; t >= 2; t -= 2)
            a2.push_back(num);
        if(t > 0) a1.push_back(num);
    }
    int flag = n % 2, m = (n + 1) / 2;
    // 如果是偶数矩阵 所有元素都是4个一组出现
    if(!flag && a4.size() * 4 != n * n) return false;
    // 如果是奇数矩阵 允许出现n-1组2个数，1个单一的数
    if(flag && (a1.size() > 1 || a2.size() > n - 1)) return false;
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < m; j++) {
            int down = n - 1 - i, right = n - 1 - j;
            if(flag && i == m - 1 && j == m - 1) grid[i][j] = a1.back();
            else if(flag && (i == m - 1 || j == m - 1)) {
                if(a2.empty()) { // 两两成对的组不够时 用4个一组的来补充
                    a2.push_back(a4.back());
                    a2.push_back(a4.back());
                    a4.pop_back();
                }
                if(i == m - 1) grid[i][j] = grid[i][right] = a2.back();
                else grid[i][j] = grid[down][j] = a2.back();
                a2.pop_back();
            } else {
                grid[i][j] = grid[i][right] = grid[down][j] = grid[down][right]= a4.back();
                a4.pop_back();
            }
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    for(int i = 1, num; i <= n * n; i++) {
        cin >> num;
        cnt[num]++;
    }
    if(solve()) {
        cout << "YES" << "\n";
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                cout << grid[i][j] << " ";
            }
            cout << "\n";
        }
    } else cout << "NO";
};