/**
 * @Time : 2024/1/23-3:29 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
 /*
  * 如果有偶数个单一数字 就各分一半
  *
  * 奇数个单一数字，可以先尽量对半分，假定a序列多一个
  * b序列中找一个出现2次以上的 留一个在b这 其余移动到a中 于是b的单一数字增加1
  * 出现2次的数字不行 因为移动一个到a 两个序列单一数字都+1，或者移动2个到a，两个序列单一数字数量保持不变
  */
#include<bits/stdc++.h>
using namespace std;

const int N = 101;
int n;
vector<vector<int>> infos;

void solve() {
    vector<int> single, three;
    for(int i = 0; i < N; i++) {
        if(infos[i].size() == 1) single.push_back(infos[i][0]);
        if(infos[i].size() > 2) three = infos[i];
    }
    string s(n, 'B');
    // 将单一数字的前一半放入a 并且保证a的单一数字数量 >= b的
    for(int i = 0; i < (single.size() + 1) / 2; i++)
        s[single[i]] = 'A';
    if(single.size() % 2 == 1) { // a 比 b多一个单一数字的情况
        if(three.size() == 0) {
            cout << "NO" << endl;
            return;
        }
        for(int i = 0; i < three.size() - 1; i++) // 将一个多于2的数字从b中拿取 给b留一个
            s[three[i]] = 'A';
    }
    cout << "YES" << endl;
    cout << s << endl;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    infos.assign(N, {});
    cin >> n;
    for(int i = 0, num; i < n; i++) {
        cin >> num;
        infos[num].push_back(i);
    }
    solve();
}