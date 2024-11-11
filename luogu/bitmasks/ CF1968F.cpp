/**
 * @Time : 2024/5/9-9:31 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1968F 数学 位运算
 */
 /*
  * 可以分为k个部分 每个部分的xor都相等
  * 1.k为偶数 偶数个相等的xor 整体的xor = 0。
  * xor(l, r) == 0 那么可以分为两个部分 nums[i], nums[i + 1, j] 这两个部分xor是相等的
  * 2.k为奇数 多出一个子数组 该子数组的xor值 = xor(l, r) = a
  * 左边能找到一个等于 xor 为a的子数组 右边还能找到一个xor为a的子数组 就能确定答案
  * 假设 xor(1, l-1) = b
  * xor(1, r) = xor(1, l-1) ^ xor(l, r) = b ^ a
  * 如果存在一个下标k1使得 xor(1, k1) = xor(1, r)
  * 那么 xor(1, k1) = xor(1, l-1) ^ xor(l, k1) = b ^ xor(l, k1) = xor(1, r) = b ^ a
  * xor(l, k1) = a 就找到了一个靠左边的子数组nums[r,k1]异或值为a
  * 同理从另外一个角度查看是否有 xor(k2, r) = a
  * 如果有 xor(l, r) = xor(l, k1) ^ xor(k1+1,k2-1) ^ xor(k2,r) = a
  * a ^ xor(k1+1,k2-1) ^ a = a, xor(k1+1,k2-1) = a 这样就将l,r这个子数组分为三个部分了
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int T, n, q, nums[N], pre[N], suf[N];
map<int, vector<int>> preM, sufM;

bool check(int l, int r) {
    int a = pre[l - 1] ^ pre[r];
    if(a == 0) return true;
    vector<int>& preA = preM[pre[r]];
    int k1 = *lower_bound(preA.begin(), preA.end(), l);
    vector<int>& sufA = sufM[suf[l]];
    int k2 = *(--upper_bound(sufA.begin(), sufA.end(), r));
    return k1 + 1 <= k2 - 1;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> q;
        preM.clear(), sufM.clear();
        pre[0] = suf[n + 1] = 0;
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            pre[i] = pre[i - 1] ^ nums[i];
            preM[pre[i]].push_back(i);
        }
        for(int i = n; i >= 1; i--) {
            suf[i] = suf[i + 1] ^ nums[i];
            sufM[suf[i]].push_back(i);
        }
        for(auto& p : sufM) {
            reverse(p.second.begin(), p.second.end());
        }
        for(int i = 1, l, r; i <= q; i++) {
            cin >> l >> r;
            cout << (check(l, r) ? "YES" : "NO") << "\n";
        }
    }
};