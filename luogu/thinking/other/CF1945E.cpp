/**
 * @Time : 2024/4/1-2:47 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
/*
  * 按题目描述的二分方式进行二分 记录整个过程中比较过的下标
  * 二分最后下标l，该下标对应的数为 pl
  * 1.如果最终结果刚好就是x 就不用操作
  * 2.不是1的情况，但是x的索引idx 没有出现在比较过程中 那么就x直接换到最终结果处即可
  * 3.pl != x，但是x的索引idx又出现在了比较过程中
  *   3a. pl < x，在二分过程中会出现 nums[idx] <= x, l更新为idx
  *       如果将l和idx的数互换 new_nums[idx] < x, l更新为idx
  *       也就是说交换之后 不影响查询过程 最终下标处被换成了x
  *   3b. pl > x，在二分过程中会出现 nums[idx] <= x, l更新为idx
  *       这一次更新后pl == x，后续的查找过程中
  *       用于对比的数pm > x更新的是r； pm <= x才更新l，就使得pl只会更小
  *       因此不可能出现 pl > x 的情况
  *
  */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int N = 2e5 + 5;
ll T, n, x, nums[N], idx;

void solve() {
    int l = 1, r = n + 1;
    while(r - l > 1) {
        int mid = (l + r) >> 1;
        if(nums[mid] <= x) l = mid;
        else r = mid;
    }
    if(idx == l) {
        cout << "0" << "\n";
        return;
    }
    // idx不出现在比较过程中 或者 pl小于x的情况 都是进行一次交换即可
    cout << "1" << "\n";
    cout << idx << " " << l << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n >> x;
        for(int i = 1; i <= n; i++) {
            cin >> nums[i];
            if(nums[i] == x) idx = i;
        }
        solve();
    }
};