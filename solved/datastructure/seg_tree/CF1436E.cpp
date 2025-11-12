/**
 * @Time : 2024/3/8-4:33 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 考虑mex数组中可能出现的值 因为nums[i]的范围是1～n, mex数组中值的范围就是1～n+2
 * 暴力求解：遍历nums的所有子数组 计数每个子数组的mex值，然后在mex数组中标记出该值已出现
 * 然后从小到大遍历1～n+2 看哪个值未被标记 就是答案。但枚举nums的子数组超时
 *
 * 考虑直接看某个mex值是否会被标记（用marked数组来标识） 要将marked[a]标记为1
 * 那么就需要存在一个子数组使得其mex的值为a 相当于满足两个条件
 * 1. 子数组不含a 因此如果nums中存在a 这个子数组存在与两个a之间（或者第一个a的左边，最后一个a的右边）
 * 2. 子数组中含有1～a-1的所有值
 *
 * 如果nums中存在a，有区间划分 就需要知道每个a的上一个下标是多少用last[a]表示
 * 那么在区间[last[a] + 1, i]上 如果1～a-1的值都出现了 marked[a]就会被标记
 * 假设 记录任何一个数最后一次出现的索引 将1~a-1这些数的最小索引查idx找到 idx > last[a]
 * 就说明在区间[last[a] + 1, i]上 1～a-1的值都出现了
 * （当然这个区间上还可能出现其它值 但比a大 不影响该子数组的mex值是a）
 * 为了避免边界情况 假设所有元素最开始的索引都是0 还没出现的元素就一定不会使得最小索引 > last[a]
 * 在枚举nums中元素时进行上述检查：当前值nums[i] = a 看是否能标记marked[a]
 * 注意别忘了 最后一个a的右边范围内的子数组的检查 因此遍历完后还要枚举 1～n+1
 *
 * 如果nums中不存在a，就不用区间划分 直接看 1~a-1这些数的最小索引是否 > 0
 * 这种情况和上一种情况最后的边界情况一致 就不需要单独计算了
 *
 * 要查找 1～a-1的值的最小索引 就是区间上的最小值查询
 * 更新a的最近一次出现的索引 就是单点修改 使用线段树
 */
#include<bits/stdc++.h>
#define ls x << 1
#define rs (x << 1) | 1

typedef long long ll;
using namespace std;
const int MOD = 1e9 + 7, N = 1e5 + 5;
int n, nums[N], last[N], val[4 * N], marked[N];

void add(int x, int l, int r, int pos, int v) {
    if(l == r) {
        val[x] = v;
        return ;
    }
    int mid = (l + r) >> 1;
    if(pos <= mid) add(ls, l, mid, pos, v);
    else add(rs, mid + 1, r, pos, v);
    val[x] = min(val[ls], val[rs]);
}

int search(int x, int l, int r, int a, int b) {
    if(a <= l && r <= b) return val[x];
    int mid = (l + r) >> 1, res = INT_MAX;
    if(a <= mid) res = search(ls, l, mid, a, b);
    if(b > mid) res = min(res, search(rs, mid + 1, r, a, b));
    return res;
}

int solve() {
    for(int i = 1; i <= n; i++) {
        int a = nums[i];
        if(a > 1) marked[1] = 1; // 特殊地 但凡有一个数不是1 mex数组1就会出现
        if(a > 1 && search(1, 1, n, 1, a - 1) > last[a]) marked[a] = 1;
        last[a] = i, add(1, 1, n, a, i);
    }
    // 不在nums中的值、在nums中的值的最右边区间 检查mex数组中是否会存在该值
    for(int i = 2; i <= n + 1; i++)
        if(search(1, 1, n, 1, i - 1) > last[i]) marked[i] = 1;
    // 从小到大查看mex数组中哪个值没被标记
    for(int ans = 1; ans <= n + 2; ans++)
        if(marked[ans] == 0) return ans;
    return -1;
};

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n;
    memset(val, 0, sizeof(val));
    memset(last, 0, sizeof(last)), memset(marked, 0, sizeof(marked));
    for(int i = 1; i <= n; i++)
        cin >> nums[i];
    cout << solve() << "\n";
};