/**
 * @Time : 2024/9/3-10:05 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1790E 位运算 数学
 */
/*
  * a + b = 2 * num
  * a xor b = num

num中为1的位 两个数中 一个是1，一个是0，那么对和的贡献就确定了 加起来恰好就是num
num中为0的位 两个数中 都是0或者都是1，对和的贡献 2 * (2^i1 + 2^i2 ... + 2^in)
因此 2 * (2^i1 + 2^i2 ... + 2^in) = num
所以num首先得是个偶数，num / 2 的二进制必须是num中0的位的子集，同时 num / 2就是a b两个数公共的部分

例如
18：是偶数 二进制 0001 0010，取反1110 1101，9 : 0000 1001
公共的部分就是9，再将num中的1分配过去即可 18 = 16 + 2，因此两个数可以是25和11，也可以是27和9

36：是偶数 = 32 + 4，二进制0010 0100，取反 1101 1011，18: 0001 0010
公共部分18，将32和4分配 两个数可以是50和22，也可以是54和18

6 = 4 + 2, 是偶数，二进制 0110 取反 1001， 3: 0011不是num中0的位的补集合
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5, mod = 9;
typedef long long ll;
int T, num;

bool check(int x) {
    if(x % 2 == 1) return false;
    int t1 = ~x, t2 = x / 2;
    for(int i = 30; i >= 0; i--) {
        int t = 1 << i;
        if(!(t & t1) && (t & t2)) return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> num;
        if(!check(num)) cout << "-1\n";
        else {
            int a = num / 2 + num, b = num / 2;
            cout << a << " " << b << "\n";
        }
    }
};