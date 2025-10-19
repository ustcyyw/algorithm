/**
 * @Time : 2024/1/30-12:59 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc :
 */
 /*
  * 如果区间[l,r]已经固定，要找区间上一共有多少个不同的数
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 5, M = 1e6 + 5, mod = 1e9 + 7;
int T, n, nums[N];

string solve() {

}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        cout << solve() << "\n";
    }
}