/**
 * @Time : 2024/12/12-9:19 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1758D 1800 构造 数学
 */
/*
  * a是最大值 b是最小值 a - b = sqrt(sum)
  * a和b的差为sqrt(sum)，也就是说a和b之间能填sqrt(sum)个数
  * 为了让a和b之间再填n-2个数 并且有调整的空间（因为要保证求和为sum）取sqrt(sum) = 10n
  * a = b + 10n
  * 填数如果先假设为等差数量（有足够的空间调整） sum = (b + b + 10n) / 2 * n = 100n*n
  * 解得b = 95n, a = 105a
  * 由于等差数量两两一组平均值都相等，因此avg = (a + b) / 2
  * 这n-2个数就围绕这avg取即可
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int T, n;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        cout << 95 * n << " " << 105 * n << " ";
        int base = 100 * n;
        n -= 2;
        if(n % 2 == 1) {
            cout << base << " ";
            n--;
        }
        for(int i = 1; n > 0; n -= 2, i++)
            cout << base - i << " " << base + i << " ";
        cout << "\n";
    }
};