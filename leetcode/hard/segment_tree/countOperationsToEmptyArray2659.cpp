/**
 * @Time : 2023/5/2-11:50 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

#include<bits/stdc++.h>
using namespace std;
/*
     * 如果数组第一个元素不是最小元素，就将它移动到最后面
     * 相当于这个数组是一个循环数组 如果将该数组重复n次
     * 从左往右在第一个周期内，可以删掉最小元素，至多在第二个周期内，可以删掉第二小的元素
     * ...
     * 比如 数组 {2,4,1,3} 重复4次是
     * 2,4,1,3; 2,4,1,3; 2,4,1,3; 2,4,1,3
     * 在第一个周期内找到最小的1
     * 2,4,[1,3; 2,4],1,3; 2,4,1,3; 2,4,1,3
     * 中括号的序列刚好对应移动操作后的数组
     * 将1标识为已删除，继续找当前最小的2
     * 2,4,1,3; [2,4,1,3;] 2,4,1,3; 2,4,1,3
     * 中括号的序列，除去标识过的1，刚好就是删掉1后，再进行移动操作让2在数组第一个位置的数组
     * 由此可以发现 移动元素的过程，就是在长度为n的数组中移动头指针 head
     * 删除操作，就是将元素标识为已删除
     * 那么区间[head, head + n - 1]上，就是按模拟得到的数组本身
     *
     * 在移动head的过程中，如果下一个元素没有被删除，就对应了一次移动操作
     * 那么我们就记录 有哪些位置的元素被删除了
     * 并且利用循环数组，将这些位置都映射到[0,n-1]上，维护[0,n-1]有哪些元素被删除即可
     *
     * 头指针前置位置记为pre，如果下一个要删除的元素位置为i，记区间[a,b]上被删除的元素个数为sum[a,b]
     * 1.pre <= i，那么pre向右移动到i即可，区间中共有 i - pre + 1个元素，但是其中有一些元素被删除了 sum[pre, i]
     * 区间中实质上还剩余的元素只有 i - pre + 1 - sum[pre, i] 个，对应需要移动i - pre - sum[pre, i]次
     * 2.pre > i，那么pre需要向右移动到n-1，然后回到0，再从0移动到i
     * 这两部分区间中共有元素 n - 1 - pre + 1 + i - 0 + 1 = n - pre + i + 1
     * 其中被删除的元素个数为 sum[pre, n - 1] + sum[0, i]
     * 对应需要移动 n - pre + i - (sum[pre, n - 1] + sum[0, i]) 次
     *
     * sum[a,b] 区间上被删数的个数之和：区间求和
     * 标识一个被删除的数，相当于将单个点设置为1，单点修改
     * 所以可以使用线段树来维护
     */
#define ls (x << 1)
#define rs (x << 1 | 1)
class Solution {
public:
    int n;
    vector<int> sum;
    long long countOperationsToEmptyArray(vector<int>& nums) {
        this->n = nums.size();
        sum = vector(4 * n, 0);
        vector<vector<int>> infos;
        for(int i = 0; i < n; i++)
            infos.push_back({nums[i], i});
        sort(infos.begin(), infos.end());
        long long ans = n;
        for(int k = 0, pre = 0; k < n; k++) {
            int i = infos[k][1];
            if(i >= pre) ans += i - pre - get_sum(pre, i);
            // 第k小的数，那么前置被删除了k个元素（k从0开始）
            // get_sum(pre, n - 1) + get_sum(0, i) = k - get_sum(i + 1, pre - 1)
            else ans += n - pre + i - (k - get_sum(i + 1, pre - 1));
            add(1, 0, n - 1, i);
            pre = i;
        }
        return ans;
    }

    int get_sum(int a, int b) {
        return get_sum(1, 0, n - 1, a, b);
    }

    int get_sum(int x, int l, int r, int a, int b) {
        if(a <= l && r <= b) return sum[x];
        int mid = (l + r) >> 1, cnt = 0;
        if(mid >= a) cnt += get_sum(ls, l, mid, a, b);
        if(mid < b) cnt += get_sum(rs, mid + 1, r, a, b);
        return cnt;
    }

    void add(int x, int l, int r, int pos) {
        if(l == r) {
            sum[x] = 1;
            return;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) add(ls, l, mid, pos);
        else add(rs, mid + 1, r, pos);
        sum[x] = sum[ls] + sum[rs];
    }
};

int main(){
    Solution s;
    vector<int> arr = {3,4,-1};
    s.countOperationsToEmptyArray(arr);
    cout << 0 << endl;
}