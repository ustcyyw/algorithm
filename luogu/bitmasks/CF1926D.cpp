/**
 * @Time : 2024/12/11-4:40 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1926D 1300 位运算
 */
/*
  * 任意两个数都不能在二进制位上有重复 集合上的数必须刚好 0、1互补 否则就只能自己在一组
  * 而且每个组最多有2个数 因为一个位上就只有0和1，第三个数0和1都不能选
  * 0、1互补意味着 异或为 full = (1 << 31) - 1
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5, full = (1ll << 31) - 1;
int T, n;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        multiset<int> set;
        int cnt = 0;
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            if(set.count(full ^ num)) {
                set.erase(set.find(full ^ num));
                cnt++;
            }
            else set.insert(num);
        }
        cout << cnt + set.size() << "\n";
    }
};