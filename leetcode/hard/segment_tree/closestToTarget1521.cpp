/**
 * @Time : 2022/9/11-9:40 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
/**
 *
Winston 构造了一个如上所示的函数 func 。他有一个整数数组 arr 和一个整数 target ，他想找到让 |func(arr, l, r) - target| 最小的 l 和 r 。

请你返回 |func(arr, l, r) - target| 的最小值。

请注意， func 的输入参数 l 和 r 需要满足 0 <= l, r < arr.length 。

 

示例 1：

输入：arr = [9,12,3,7,15], target = 5
输出：2
解释：所有可能的 [l,r] 数对包括 [[0,0],[1,1],[2,2],[3,3],[4,4],[0,1],[1,2],[2,3],[3,4],[0,2],[1,3],[2,4],[0,3],[1,4],[0,4]]， Winston 得到的相应结果为 [9,12,3,7,15,8,0,3,7,0,0,3,0,0,0] 。最接近 5 的值是 7 和 3，所以最小差值为 2 。
示例 2：

输入：arr = [1000000,1000000,1000000], target = 1
输出：999999
解释：Winston 输入函数的所有可能 [l,r] 数对得到的函数值都为 1000000 ，所以最小差值为 999999 。
示例 3：

输入：arr = [1,2,4,8,16], target = 0
输出：0
 

提示：

1 <= arr.length <= 10^5
1 <= arr[i] <= 10^6
0 <= target <= 10^7

来源：力扣（LeetCode）
链接：https://algorithm.cn/problems/find-a-value-of-a-mysterious-function-closest-to-target
 */
class Solution {
public:
    /**
     * 使用线段树保存区间上数字之与
     * 因为与操作满足交换律和结合律
     * 然后枚举左边界的时候，通过二分去查找大于等于target的最后一个下标
     * 可以二分查找是因为与操作 右边界越靠右，区间上的与就单调降低（或不变），因此具有单调性
     * 时间复杂度 n(logn)^2
     */
    int n, base = (1 << 30) - 1;
    vector<int> vals;
    int closestToTarget(vector<int>& arr, int target) {
        n = arr.size();
        vals = vector(4 * n, base);
        for(int i = 0; i < n; i++)
            add(1, i, 0, n - 1, arr[i]);
        int res = INT_MAX;
        for(int i = 0; i < n; i++){
            int lo = i, hi = n - 1;
            while (lo < hi){ // 找到最后一个大于等于target的下标
                int mid = (lo + hi + 1) >> 1;
                if(query(i, mid) >= target) lo = mid;
                else hi = mid - 1;
            }
            int t1 = abs(query(i, lo) - target);
            int t2 = lo == n - 1 ? INT_MAX : abs(query(i, lo + 1) - target);
            res = min(res, min(t1, t2));
        }
        return res;
    }

    void add(int x, int pos, int l, int r, int val){
        if(l == r){
            vals[x] = val;
            return;
        }
        int mid = (l + r) >> 1, ls = 2 * x, rs = 2 * x + 1;
        if(pos <= mid) add(ls, pos, l, mid, val);
        else add(rs, pos, mid + 1, r, val);
        vals[x] = vals[rs] & vals[ls];
    }
    int query(int l, int r){
        return query(1, l, r, 0, n - 1);
    }
    int query(int x, int L, int R, int l, int r){
        if(L <= l && r <= R) return vals[x];
        int mid = (l + r) >> 1, res = base;
        if(L <= mid) res &= query(2 * x, L, R, l, mid);
        if(R > mid) res &= query(2 * x + 1, L, R, mid + 1, r);
        return res;
    }
};

int main(){
    Solution s;
    vector<int> arr = {9,12,3,7,15};
//    s.closestToTarget(arr, 5);
    cout << s.closestToTarget(arr, 5) << endl;
}