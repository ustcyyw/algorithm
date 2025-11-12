/**
 * @Time : 2024/11/30-12:15 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1981C 1800 构造 位运算 自己想了绝大部分找不到bug 参考答案的写法
 */
/*
  * 除开全是-1的特殊情况（1和2交替排列即可）
  * 以及最左端、最右端（用端点的数一直乘以2，除以2交替排列即可）
  * 其余地方非-1的数将数组分割成多个子数组 需要填写一系列的数让b[lo]...b[hi]两个端点满足条件
  *
  * bi = b[i+1] / 2, b[i+1] = b[i] / 2
  * 已知bi，b[i+1]的可能的值为 2*bi, 2*bi+1, b[i] / 2，都是乘除2相关
  * 从二进制的角度上看 分别是bi左移1位，bi左移1位并且最低位置1，bi右移1位
  * 如果有充足的变换次数 bi可以变为任何数 最粗暴的做法就是先通过多次右移操作变为1
  * 然后根据目标选择两个左移操作即可。
  *
  * 填写b[lo]...b[hi]时，就是如何使b[lo]在 cnt = hi - lo次操作下变成b[hi]
  * (lo, hi)上一共有hi - lo - 1个1，所以可以操作hi - lo次
  * 假设通过k次操作可以使b[lo]变为b[hi]，但是还没有填满cnt个位置
  * 此时让b[hi]先左移再右移，或者先右移再左移动 想最终依旧是b[hi] 向两个放心的移动次数相同
  * 也就是说k次操作后，还想保持为b[hi]，操作次数一定是 k + 2, k + 4...
  * 如果k不是最快使b[lo]变为b[hi]的值，根据上述的结论 k0 = k - 2 * t
  * 由于cnt是有限的，那么应该首先找到最小的k使得b[lo]变为b[hi]
  * 如果 k > cnt，说明次数限制下做不到，返回false
  * 如果 k <= cnt，但是 cnt - k 不是偶数，在消耗剩余次数时，b[lo]没法刚好再变为b[hi]，返回false
  * 其余情况下都能完成填数，填数的方案就是先找到b[lo]最快变为b[hi]的方案
  * 然后剩余的位置用b[hi]不断进行左移/右移的交替操作即可
  *
  * 如何找到a最快变为b的方案?
  * 只有一种情况a可以只使用左移的两个操作变为b,就是二进制表示下除开前导0，a是b的前缀
  * 例如
  * b = 101101
  * a = 101: a*2 + 1(1011), a * 2(10110), a*2+1(101101)
  * 但a不是b的前缀呢
  * a = 1010: a/2(101) 就转换成b的前缀了。
  * 因此最少的操作就是先找a和b的最长前缀 然后将a先转换为b的前缀 再逐步转换为b
  */
#include<bits/stdc++.h>

using namespace std;
typedef unsigned long long ull;
typedef long long ll;
const int N = 1e6 + 5, mod = 1e9 + 7;
int T, n, nums[N], lo, hi;

vector<int> path(int a, int b) {
    vector<int> lp, rp;
    if(a == b) return lp;
    rp.push_back(b);
    while(a != b) {
        if(a > b) a /= 2, lp.push_back(a);
        else b /= 2, rp.push_back(b);
    }
    rp.pop_back(); // a == b 条件触发时 lp, rp中都添加了那个相同的值 所以要弹出一个
    reverse(rp.begin(), rp.end());
    for(int num : rp)
        lp.push_back(num);
    return lp;
}

void fill_between(int l, int r, int sign) {
    bool ope = true;
    for(int i = sign == 1 ? l + sign : r + sign; i > l && i < r; i += sign) {
        int num = nums[i - sign];
        nums[i] = ope ? num * 2 : num / 2;
        ope = !ope;
    }
}

bool solve() {
    if(lo == -1) {
        nums[1] = 1, fill_between(1, n + 1, 1);
        return true;
    }
    for(int i = lo; i <= hi; ) {
        int j = i + 1;
        while(j <= hi && nums[j] == -1) j++;
        if(j <= hi) {
            vector<int> aux = path(nums[i], nums[j]);
            int sz = aux.size(), cnt = j - i;
            if(sz > cnt || (cnt - sz) % 2 == 1)
                return false;
            for(int k = 0; k < sz; k++)
                nums[i + k + 1] = aux[k];
            fill_between(i + sz, j, 1);
        }
        i = j;
    }
    fill_between(0, lo, -1), fill_between(hi, n + 1, 1);
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
//    T = 1;
    while(T--) {
        cin >> n;
        lo = hi = -1;
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            if(nums[i] != -1 && lo == -1) lo = i;
            if(nums[i] != -1) hi = i;
        }
        if(!solve()) cout << -1;
        else {
            for(int i = 1; i <= n; i++)
                cout << nums[i] << " ";
        }
        cout << "\n";
    };
};