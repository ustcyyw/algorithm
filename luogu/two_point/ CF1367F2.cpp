/**
 * @Time : 2024/6/30-9:39 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : CF1367F2 双指针 排序（贪心） 线段树
 */
/*
  * 移动到序列头部到操作次数是cnt1, 移动到序列尾部的操作次数是cnt2
  * 与简单版本类似 移动到头部和尾部的元素分别是相对较小的、相对较大的数
  * 排序位置位于[1, cnt1]的数都放在序列头 排序位置位于[m - cnt2 + 1, m]的数都放在序尾部
  * 并且他们都已经局部有序
  * 为了尽可能排序 对于相同大小的数
  * 1.移动到头部的数下标应该尽可能大
  * 2.移动到尾部的数下标应该尽可能小
  * 因此移动到头部到数应该按此顺序进行 数值大小不同 先移动小的
  * 数值大小相同时 则是先移动下标大的 因为这样能尽可能避免出现逆序对
  *
  * 随着cnt1越大，未排序的数越少，出现大的数在小的数前面的可能性越小，那么需要cnt2的次数就越小
  * 而随着cnt2减小，假定被放在队尾的元素要重新拿回来 并且大小顺序是由小到大的
  * 相同数值大小，则按原数组中的位置顺序是大到小拿回，因为此时先拿靠后的 不容易出现逆序对
  * 那么我们就需要查看是否可以将其拿回 也就是说该数所在位置的右侧 没有更小的数
  *
  * 发现移动到队头的元素 是大小顺序是由小到大的，位置顺序从大到小
  * 将队尾元素放回的顺序也是相同的
  * 那么按这个顺序排序后，用i表示移动到头部的元素的下标，j表示要从队尾移动回原位置的下标
  */
#include<bits/stdc++.h>

using namespace std;
const int N = 2e5 + 5;
typedef long long ll;
int T, n, m;
vector<vector<int>> arr;


#define ls x << 1
#define rs (x << 1) | 1
const int MIN_VAL = -2e9, MAX_VAL = 2e9;

class SegmentTree {
private:
    int n;
    vector<int> val;
    // 单点修改
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
        int mid = (l + r) >> 1, res = MAX_VAL;
        if(a <= mid) res = search(ls, l, mid, a, b);
        if(b > mid) res = min(res, search(rs, mid + 1, r, a, b));
        return res;
    }

public:
    SegmentTree(int n) {
        this-> n = n;
        val = vector(4 * (n + 1), MAX_VAL);
    }

    void add(int pos, int v) {
        add(1, 0, n, pos, v);
    }

    int search(int a, int b) {
        return search(1, 0, n, a, b);
    }
};

void solve() {
    sort(arr.begin(), arr.end(), [](auto& a, auto& b) -> bool {
        if(a[0] != b[0]) return a[0] < b[0];
        return a[1] > b[1];
    });
    int ans = n;
    SegmentTree tree(n + 1);
    for(int i = 0, j = 0; i < n; i++) {
        if(i > 0) { // 移走到头部
            int idx = arr[i - 1][1];
            tree.add(idx, MAX_VAL);
        }
        while(j < n) { // 将队尾局部有序的数放回序列原位置
            int num = arr[j][0], idx = arr[j][1];
            int t = tree.search(idx + 1, n);
            if(t < num) break;
            j++;
            tree.add(idx, num);
        }
        ans = min(ans, i + n - j);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> T;
    while(T-- > 0) {
        cin >> n;
        arr = {};
        for(int i = 1, num; i <= n; i++) {
            cin >> num;
            arr.push_back({num, i});
        }
        solve();
    }
};