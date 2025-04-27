/**
 * @Time : 2025/4/27-9:16 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF2106E 1762 贪心 思维
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 2e5 + 5, mod = 998244353;
int T, n, q, nums[N], l, r, k, pos[N];

int solve() {
    int less = 0, more = 0, moreUse = 0, lessUse = 0, x = pos[k];
    if(x < l || x > r) return -1;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(mid == x) break;
        if(x < mid) { // 要让二分落在左边
            if(nums[mid] < k) more++; // 表示比k大的数需要增加1个
            else moreUse++;
            r = mid - 1;
        } else { // 要让二分落在右边
            if(nums[mid] > k) less++;
            else lessUse++;
            l = mid + 1;
        }
    }
    if(less == more) return less * 2;
    // comm表示要交换的更小数、更大数的位置相互之间优先交换的组数，need表示还需要交换的数
    int need = abs(less - more), comm = min(less, more);
    if(less > more) { // 需要换更多更小的数来
        // 比k小的数一共k-1个，还要减去已经交换了的comm，以及本来就在正确位置不可以交换的lessUse
        // 如果不足所需的need个
        if(need <= k - 1 - comm - lessUse) return need * 2 + more * 2;
        else return -1;
    } else {
        if(need <= n - k - comm - moreUse) return need * 2 + less * 2;
        else return -1;
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> T;
    while(T-- > 0) {
        cin >> n >> q;
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            pos[nums[i]] = i;
        }
        for(int i = 1; i <= q; i++) {
            cin >> l >> r >> k;
            cout << solve() << " ";
        }
        cout << "\n";
    }
}