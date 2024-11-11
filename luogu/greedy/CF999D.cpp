/**
 * @Time : 2024/4/15-10:15 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 每个余数的出现的数量都等于 cnt = n / m
  * 一开始会有些余数不足cnt，有些多于cnt，有些刚刚好等于cnt。 不足的总数 = 多余的总数
  * 可以先按照余数分组 方便判断是多于cnt需要改变，还是少于cnt等着其它数变化后补足
  *
  * 由于只能进行+1操作，对于出现次数多余cnt的某个余数 m2
  * 要将他们进行+1操作，变为大于m2且最接近他的不足cnt的某个余数 m1
  * （如果没有大于m2的m1，就从最小的不足的余数开始取 因此mod运算是周期性的）
  * 为什么是改变为最接近的m1
  * 可以假设四个余数 a < b < c < d。并且 a和b多出来了，c和d不足 数量都与cnt相差1
  * 1. a -> c, b -> d。操作次数为 c - a + d - b
  * 2. a -> d, b -> c。操作次数为 c - b + d - a
  * 二者相等 所以找最接近的至少不会差
  */
#include<bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;
const int N = 2e5 + 5;
int T, n, m, nums[N];
queue<int> mod[N];

void solve() {
    int cnt = n / m;
    map<int, int> less; // 存放欠缺的小的余数 及缺的个数
    map<int, queue<int>> more; // 记录数目多了的余数和对应数的索引
    for(int i = 0; i < m; i++) {
        if(mod[i].size() < cnt) {
            int lc = cnt - mod[i].size();
            less[i] = lc;
        }
        if(mod[i].size() > cnt)
            more[i] = mod[i]; // 记录要修改的数当前的余和索引
    }
    ll ans = 0;
    for(auto& [m2, queue] : more) {
        while(queue.size() - cnt > 0) {
            auto it = less.upper_bound(m2);
            if(it == less.end()) it = less.begin();
            int m1 = (*it).first, cnt1 = (*it).second, cnt2 = queue.size() - cnt;
            int t = min(cnt1, cnt2), add = m1 > m2 ? m1 - m2 : m - m2 + m1;
            ans += t * add;
            for(int i = 0; i < t; i++) {
                nums[queue.front()] += add;
                queue.pop();
            }
            cnt1 -= t;
            if(cnt1 == 0) less.erase(it);
            else less[m1] = cnt1;
        }
    }
    cout << ans << "\n";
    for(int k = 1; k <= n; k++)
        cout << nums[k] << " ";
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> m;
    for(int i = 1; i <= n; i++) {
        cin >> nums[i];
        mod[nums[i] % m].push(i);
    }
    solve();
};