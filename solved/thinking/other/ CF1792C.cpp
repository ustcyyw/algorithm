/**
 * @Time : 2023/10/17-3:51 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 本身已经有序 操作0次
 *
 * 如果只需要操作一次就能完成排序
 * 说明1.除开这一对操作的数 其它数都已经有序了
 * 2.且最后操作的数一定是1和n 否则最小的数 or 最大的数不在正确的位置
 *
 * 如果只需要操作2次就能完成排序
 * 那除了最后操作的1和n，倒数第二次操作同理是2和n-1
 * 并且除开这两对数 其它都已经有序
 *
 * 如果(1,n)有序 但是(2,n-1)不有序 那么(2,n-1)需要一次调整
 * 调整完后(1,n)必然不在正确位置 那就还需要对(1,n)调整一次 共2次
 * 因此应该先检查较小的数对 从(half, half - 1)，对应n是偶数 或者 (half, half)对应n是奇数的
 *
 * 先找到中间对的位置 然后从里向外查看 检查有序子序列的情况
 * 比如 先检查了 (4,4) 接下来该向外看(3,5), (2,6), (1,7)是否还构成有序子序列
 * 检查过程中发现了未构成子序列的数对，那么它一定要调整一次，并且它调整完后比它靠外侧的数对得依次进行调整
 */
#include<bits/stdc++.h>
using namespace std;
int T;

int solve(int n) {
    vector<int> arr(n, 0);
    for(int i = 0; i < n; i++)
        cin >> arr[i];
    int a = (n + 1) / 2, b = n % 2 == 0 ? a + 1 : a;
    int lo = 0, hi = 0;
    while (arr[lo] != a) lo++;
    while (arr[hi] != b) hi++;
    if(hi < lo) return n / 2; // 最靠里的一对数就不有序，那么它就要调整 其余也都需要调整
    int p = 1; // 记录有序子序列中数的对数
    while (true) {
        a--, b++;
        while (lo >= 0 && arr[lo] != a) lo--;
        while (hi < n && arr[hi] != b) hi++;
        if(lo >= 0 && hi < n) p++;
        else break;
    }
    return (n + 1) / 2 - p;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    for(int i = 1, n = 0; i <= T; i++) {
        cin >> n;
        cout << solve(n) << endl;
    }
}