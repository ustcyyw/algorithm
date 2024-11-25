/**
 * @Time : 2024/11/24-4:34 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1374E1 贪心 1600
 */
 /*
  * 先选两人都喜欢的书 然后考虑是否能将其中最耗时的书 替换为两本a和b单独喜欢的书
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, k;
vector<int> a, b, both;

int solve() {
    int m1 = a.size(), m2 = b.size(), m3 = both.size();
    if(m1 + m3 < k || m2 + m3 < k) return -1;
    sort(both.begin(), both.end());
    sort(a.begin(), a.end()), sort(b.begin(), b.end());
    int sum = 0;
    for(int i = 0; i < min(k, m3); i++)
        sum += both[i];
    for(int i = 0, j = min(k, m3) - 1; i < min(m1, m2); i++) {
        if(j + 1 + i + 1 <= k) sum += a[i] + b[i];
        else if(j >= 0 && a[i] + b[i] < both[j]) {
            sum = sum - both[j] + a[i] + b[i];
            j--;
        }
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    T = 1;
    while(T--) {
        cin >> n >> k;
        for(int i = 1, time, f1, f2; i <= n; i++) {
            cin >> time >> f1 >> f2;
            if(f1 && f2) both.push_back(time);
            else if(f1) a.push_back(time);
            else if(f2) b.push_back(time);
        }
        cout << solve() << "\n";
    };
};