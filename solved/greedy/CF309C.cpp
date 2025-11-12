/**
 * @Time : 2024/1/26-10:08 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 很明显 物品的重量 提示要从二进制位的角度考虑
 * 那么我们统计背包的二进制位1的情况
 * 由于二进制位的1可以从高位向下借（相当于背包空间拆分成更小的一些 2^k 的空间）
 * 所以应该贪心地先安排体积小的物品 没有刚好相等的空间时 就从大的空间进行拆分
 * 拆分后有零散的空间也不怕
 * 比如有一个大小为 8 背包。有大小为1的物品a 大小为8的物品b
 * 将背包8拆分成 4 2 1 1 四个子空间，用大小1的子空间放a
 * 会有零散的4 2 1三个子空间，放不了b了。但是和不拆分直接放b效果一样
 * 因此将大空间拆分后优先放小物品 至少不会差。
 * 如果还有一个物品c的体积为1 2 4，那么拆分后能装的物品就更多了
 */
#include<bits/stdc++.h>
using namespace std;
int n, m, box[31], w[31];
// 尝试向高位借 借不到就说明再也没有背包余量了
bool change(int wi, int bi) {
    while(bi < 31 && box[bi] == 0) bi++;
    if(bi == 31) return false;
    if(bi == wi) return true;
    box[bi]--;
    for(int j = bi - 1; j > wi; j--)
        box[j]++;
    box[wi] += 2;
    return true;
}

void solve() {
    int res = 0;
    for(int i = 0; i < 31; ) {
        while(i < 31 && w[i] == 0) i++;
        if(i == 31) break;
        if(!change(i, i)) break;
        int t = min(box[i], w[i]);
        box[i] -= t, w[i] -= t, res += t;
    }
    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    memset(box, 0, sizeof(box)), memset(w, 0, sizeof(w));
    cin >> n >> m;
    for(int i = 0, num; i < n; i++) {
        cin >> num;
        for(int j = 0; j < 31; j++)
            if((1 << j) & num) box[j]++;
    }
    for(int i = 0, num; i < m; i++) {
        cin >> num;
        w[num]++;
    }
    solve();
}