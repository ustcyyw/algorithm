/**
 * @Time : 2024/4/2-8:52 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 第一次询问某个数x 到第二次询问x之间的每一次添加 都会对A[x]有贡献
  * 第二次询问到第三次询问之间 对A[x]无贡献
  * 第三次到第四次询问之间 对A[x]有贡献
  * ....
  * 注意最后一次询问的边界处理
  */
#include<bits/stdc++.h>

typedef long long ll;
using namespace std;
const int N = 2e5 + 5;
ll T, q, n, picked[N], sum[N] = {0};
vector<int> aux[N];

ll cal(vector<int>& arr) {
    arr.push_back((int)q + 1);
    ll res = 0;
    for(int i = 0; i < arr.size() - 1; i += 2) {
        int lo = arr[i], hi = arr[i + 1] - 1;
        res += sum[hi] - sum[lo - 1];
    }
    return res;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> q;
    memset(aux, {}, sizeof(aux)), memset(picked, 0, sizeof(picked));
    for(int i = 1, x, cnt = 0; i <= q; i++) {
        cin >> x;
        aux[x].push_back(i); // 记录询问同一个数的顺序信息
        if(!picked[x]) picked[x] = 1, cnt++;
        else picked[x] = 0, cnt--;
        sum[i] = sum[i - 1] + cnt;
    }
    for(int i = 1; i <= n; i++)
        cout << cal(aux[i]) << " ";
};