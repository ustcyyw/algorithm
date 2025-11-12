/**
 * @Time : 2024/1/11-9:35 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 置换环
 */

/*
 * 要使一个排列中只有一个逆序对 并且元素是从1~n
 * 那么只有1个逆序对 就等价于只能有相邻的两个数互换位置 其余数应该在排序后的正确位置
 * 考虑枚举(k, k+1)互换位置
 * 对于指定的(k, k+1) 所有元素都有一个指定的最终位置 如果不在最终位置就需要进行置换
 * 因此想到了置换环（元素a如果不在自己的最终位置ia 那么a指向其nums[ia]这个数）。
 * 交换次数 = n - 置换环数量
 * 找置换环需要的时间复杂度是n，再算上枚举k 整体时间复杂度n^2
 *
 * 但是枚举k的时候，只有(k, k+1)的位置特殊处理 其余数都是放在升序排序的位置
 * 那么如果预处理出所有元素按升序排序的置换环 再单独考虑(k, k+1)对调位置的影响
 * 假设在原本置换环中 有边 i -> k, j -> k + 1， 现在对调(k, k+1)的位置
 * 边变为 i -> k + 1, j -> k
 * 1. k, k+1本身就在一个置换环中 比如原本环是 i -> k -> j -> k + 1 -> i
 * 边改变后变为 i -> k + 1 -> i; j -> k -> j 成为两个环
 * 2. k, k+1本身不在一个置换环中 比如原本环是 i -> k -> i; j -> k + 1 -> j
 * 边改变后变为 i -> k + 1 -> j -> k -> i 两个环变为1个
 *
 * 所以 可以先找到总共有多少个置换环（记为m） 并且标记每个元素在哪个置换环中
 * 最终答案就是枚举 (k, k+1) 如果他们在一个环中 可能的答案就是 n - m + 1
 * 如果他们不在一个环中 可能的答案就是 n - m - 1
 */

#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;
int T, n, nums[N], id[N], marked[N], m;

void cycle() {
    m = 0;
    memset(marked, 0, sizeof(marked));
    function<void(int)> dfs = [&](int v) -> void {
        marked[v] = 1, id[v] = m;
        if(!marked[nums[v]])
            dfs(nums[v]);
    };
    for(int i = 1; i <= n; i++) {
        if(!marked[i]) {
            m++;
            dfs(i);
        }
    }
}

int main(){
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> nums[i];
        cycle();
        int res = N;
        for(int k = 1; k < n; k++) {
            int t = id[k] == id[k + 1] ? -1 : 1;
            res = min(res, n - m + t);
        }
        cout << res << endl;
    }
}

int main(){
    Solution s;
    
    cout << 0 << endl;
}