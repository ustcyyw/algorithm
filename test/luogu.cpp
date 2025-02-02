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
const int N = 100 + 5, M = 2 * N;
int n, nums[N];

void solve() {
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            for(int k = 1; k <= n; k++) {
                if(i != k && i != j && j != k && nums[i] == nums[j] + nums[k]) {
                    cout << i << " " << j << " " << k;
                    return;
                }
            }
        }
    }
    cout << -1;
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
//    cin >> T;
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> nums[i];
    solve();
};