/**
 * @Time : 2025/4/23-9:00 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2091G 2300 数学 动态规划 bitset优化 （看答案做的）
 */
/*
  * 特别地 如果 s % k = 0, 答案就是k
  * 所有可能的答案，最终到达s时，奇偶性要与k一致，因为得偶数次掉头才能回到正方向上
  * 因为给的s很大，思考较大的s是有通解的 考虑一直以k的间隔向前走 直到再走一次会超过s
  * 此时与s的距离就是 r = s % k
  *
  * 推论：向后退1步，再前进1步 相当于是退后了1的距离，那么向后退p步，再前进p步，相当于是后退了p的距离
  * 此时经历了两次方向调整，一次前进的距离为k - 2
  * 在后退p距离的情况下，距离终点的距离就是 r + p
  * 如果 r + p = k - 2, 以k - 2的距离再走一次，就到终点了
  * 同时k - 2也是除k外最大的可能答案，因此k - 2就是答案
  * 现在就是证明一定有这样的p存在, 使得p = k - 2 - r
  *
  * a. p >= 0, 要求 r <= k - 2
  * b. p <= k - 2
  * 如果s >= k ^ 2，那么一开始以k的距离走的时候 至少可以走k次
  * 往后以k-1的距离走，至少也可以走k次，能够往后走k次，就意味着最多可以退k步
  * 这样就保证了 p的取值范围是[0, k]， 那么当然存在某个p <= k - 2
  *
  * 于是在 s >= k ^ 2 的大前提下
  * 1.在 r <= k - 2 时，k - 2就是答案
  * 2.就只需要再考虑 r = k - 1 的情况，此时我们考虑后退 k - 3 步，每一步能走k - 1的距离
  * 此时距离终点的距离为 (k - 1) * (k - 3) + r = (k - 1) * (k - 2)
  * 或者 由之前的推论 后退k - 3步，换方向前进k - 3步，等于后退了 k - 3 的距离
  * 此时距离终点的距离为 k - 3 + r = 2k - 4
  * 刚好是 k - 2 的倍数 因此答案是 k - 2
  * 由此可以说明 在 s >= k ^ 2的情况下 答案一定是 k - 2
  *
  * 接下来只需要讨论 s < k ^ 2的情况，此时s比较小
  * 定义f[i][s]: 以步长i，到达s位置是否可能
  * 1.如果i与初始的k奇偶性相同 那就是正方向
  * f[i][s] = f[i][s - i] | f[i + 1][s - i]
  * 第一部分是指从 s - i 以i的步长到达s；
  * 第二部分指 以i + 1的步长到达s - i, 掉头以i的步长到达s
  * 2. 如果i与初始的k奇偶性不同 那就是反方向
  * f[i][s] = f[i][s + i] | f[i + 1][s + i]
  */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 4e2 + 15;
int T, s, k;

int solve() {
    if(s % k == 0) return k;
    if(s >= k * k) return max(1, k - 2);
    // 因为k最大为1000，s的上限是1000000，所以这里开2000010的大小 足够进行左移和右移操作
    bitset<2000010> bit, bit2, mask;
    // mask的就是在每次计算之后 清空[0,s]位之外的数据 那些数据是不该存在的 如果不处理会影响计算结果
    for(int i = 0; i <= s; i++)
        mask.set(i);
    bit.set(0);
    // 在计算过程中bit2表示步长i的结果，是正在计算的，bit表示步长i+1的结果 是上一轮计算结果
    for(int i = k; i >= 1; i--) {
        bit2.reset();
        // 正向运动，x由x - i转移，位置x，对应上一轮的x-i
        // 也就是说要将上的结果进行位运算左移i位(<<)才对应这一轮的位置
        if(i % 2 == k % 2) bit2 = bit << i;
            // 负向运动，x由x + i转移，位置x，对应上一轮的x+i
        else bit2 = bit >> i;
        // 这个循环进行f[i][s] = f[i][s - i]或者f[i][s] = f[i][s + i]的转移
        for(int j = 1; j * i <= s; j++) {
            if(i % 2 == k % 2) bit2 |= (bit2 << i);
            else bit2 |= (bit2 >> i);
        }
        bit = bit2;
        bit &= mask;
        if(bit[s]) return i;
    }
    return 1;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> T;
    while (T--) {
        cin >> s >> k;
        cout << solve() << "\n";
    }
    return 0;
}