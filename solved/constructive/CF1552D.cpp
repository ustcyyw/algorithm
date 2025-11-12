/**
 * @Time : 2025/1/9-7:44 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1552D 1800 构造 参考了答案
 */
/*
  * a[i] = bj - bk,  bk - bj = -a[i]
  * 能通过b数组的得到a[i], 就能通过b数组得到-a[i]
  * 因此a中元素的正负不重要 假设将a中一些元素取反后得到c数组
  * 如果b数组有n+1个元素 那完全可以令b[1] = 0
  * 然后b[2] = c[1], b[3] = c[1] + c[2], .. b[n+1] = c[1] + c[2] + ... + c[n]
  * 这样就能完成构造
  * 但是b中只能有n个元素 那还是按上述规则构造 b[n] = c[1] + c[2] + ... + c[n-1]
  * 现在仅有c[n]不能通过 b[j] - b[j-1]的方式得到
  * 用上述方式构造出b数组， b[j] - b[k] 就是c[k+1, j]上的子数组和
  * 因此能完成构造的条件就是 c[n] = sum[k + 1, j] （某一个k、j使得等式成立即可）
  * 因为a数组（c数组）的顺序是可以任意调换的，因此上式的意义就是
  * 取出a中的一些元素 然后这些元素里面部分取相反数后 和为0
  * 那将取相反数的那部分移动到另外一边 就相当于是a中取了两个和相同集合 s1和s2
  * 这两个集合中的元素没有交集
  *
  * 如果从a中找到了两个和相同的集合 集合有交集
  * 只需要将交集元素剔除就能得到没有交集的两个和相同的元素 也就完成了构造
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5000 + 5, mod = 998244353;
int T, n, a[11];

bool solve() {
    if(n == 1) return a[0] == 0;
    map<int, int> cnt;
    for(int s = 0; s <= (1 << n) - 1; s++) {
        int sum = 0;
        for(int j = 0; j < n; j++) {
            if((1 << j) & s)
                sum += a[j];
        }
        cnt[sum]++;
        if(cnt[sum] == 2) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(0);cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while (T-- > 0) {
        cin >> n;
        for(int i = 0; i < n; i++)
            cin >> a[i];
        cout << (solve() ? "YES" : "NO") << "\n";
    }
};