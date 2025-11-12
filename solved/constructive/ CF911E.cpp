/**
 * @Time : 2024/4/19-8:52 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
 * 1.队首的数为a,队列后面存在数b，如果 b < a
 * 一定要让b进入堆后才能开始弹出 否则a先于b弹出 最终序列不是升序
 *
 * 2.存在序列 a, b, c 并且b最大 c最小 鉴于1 按abc的顺序进入堆 弹出后是cba 不是升序序列
 *
 * 3.考虑当前的数为a,队列后面存在数b，如果 b > a，并且在a之前以及a和b之间还缺失小于a的数
 * 那么这个数得安排在b之后 就会出现2中的情况 最终不是升序序列
 *
 * 用单调栈找下一个更小的数 如果下标是j，那么两个数中间比当前数大的就有 j - i - 1个
 * 然后从左向右遍历 记录左边元素出现的情况 用线段树查询其左边小于它的数有多少
 *
 * 如果没有下一个数比a大 或者在下一个比他大的数b之前已经有a-1个数小于a了
 * 那么通过合理安排 总能使这个数排到正确的顺序（多尝试例子）
 * 因此我们可以先校验原本的序列是否合法 如果不合法输出-1
 * 如果合法开始构造
 *
 * 构造要尽可能让字典序大 构造的原则同上述校验原则
 * 从后遍历，假设当前数下标是i，数为num，其左边小于num的数lower[i]
 * 还有其右边小于它的数（同样用一棵线段树来查找）有cnt个
 * 那么要保证栈处理有序性 还需要添加的数字为 num - 1 - (cnt + lower[i])个
 * 并且可以发现 需要添加的数字 一定是从num-1，num-2...并且是从大到小地添加
 * （这个结论也是看case看出来的）
 */
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 5;
int n, k, mv, nums[N], lower[N];

#define ls x << 1
#define rs (x << 1) | 1

class SegmentTree {
private:
    int n;
    vector<int> val; // 存储区域上的最小值

    void add(int x, int l, int r, int pos, int v) {
        if(l == r) {
            val[x] += v;
            return ;
        }
        int mid = (l + r) >> 1;
        if(pos <= mid) add(ls, l, mid, pos, v);
        else add(rs, mid + 1, r, pos, v);
        val[x] = val[ls] + val[rs];
    }

    int search(int x, int l, int r, int a, int b) {
        if(a <= l && r <= b) return val[x];
        int mid = (l + r) >> 1, res = 0;
        if(a <= mid) res = search(ls, l, mid, a, b);
        if(b > mid) res += search(rs, mid + 1, r, a, b);
        return res;
    }

public:
    SegmentTree(int n) {
        this-> n = n;
        val = vector(4 * (n + 1), 0);
    }

    void add(int pos, int v) {
        add(1, 0, n, pos, v);
    }

    int search(int a, int b) {
        return search(1, 0, n, a, b);
    }
};

bool check() {
    stack<int> stack;
    for(int i = k; i >= 1; i--) {
        while(!stack.empty() && nums[stack.top()] < nums[i])
            stack.pop();
        if(!stack.empty() && stack.top() - i + lower[i] < nums[i])
            return false;
        stack.push(i);
    }
    return true;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> k;
    SegmentTree tree(n);
    for(int i = 1; i <= k; i++) {
        cin >> nums[i];
        mv = max(nums[i], mv);
        lower[i] = tree.search(1, nums[i]);
        tree.add(nums[i], 1);
    }
    if(!check()) {
        cout << -1;
        return 0;
    }
    SegmentTree rt(n);
    for(int i = k; i >= 1; i--) {
        int num = nums[i], need = num - 1 - (lower[i] + rt.search(1, num));
        for(int j = 1; j <= need; j++) {
            nums[++k] = num - j;
            rt.add(nums[k], 1);
        }
        rt.add(num, 1);
        if(nums[i] == mv) break;
    }
    for(int i = k + 1, t = n; i <= n; i++, t--)
        nums[i] = t;
    for(int i = 1; i <= n; i++)
        cout << nums[i] << " ";
};