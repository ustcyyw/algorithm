/**
 * @Time : 2023/11/27-11:57 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

/*
 * 如果两个元素相同且相邻，可以将其视为也能进行交换 或者不能交换
 * （反正换不换 结果都一致 字符串还是长那样）
 * 1.只有01的字符串 将相同且相邻元素视为可交换，那么整个序列就是任意交换，直接排序成最小字典序列即可
 * 2.只有12的字符串 同上
 * 3.只有02的字符串 将相同且相邻元素视为不可交换，那么整个序列压根不能变换 直接返回即可
 * 4.012都包含的字符串
 *   4.1假设第一个2出现的位置是i，s[0,i-1]上仅有0和1，按情况1来处理
 *   4.2如果s[i+1, n-1]存在1，由于0是不可能跨越这个2的 i这个位置无论如何都不能变成0
 *   要让字典序小，就应该让1来占i这个位置，1可以任意交换，
 *   于是将任意一个1移动到i，其余数字相对位置保持不变。
 *   现在第i+1个位置变成了2，又回到了上述情况，查看s[i+2,n-1]上是否存在1，如果则继续移动到i+2
 *   发现这个过程中2和0的相对位置没有改变
 */

string solve() {
    string s;
    cin >> s;
    vector<string> infos(3);
    for(char c : s)
        infos[c - '0'].push_back(c);
    int m0 = infos[0].size(), m1 = infos[1].size(), m2 = infos[2].size();
    if(m2 == 0) return infos[0] + infos[1]; // case1 只有0和1这两种字符
    if(m0 == 0) return infos[1] + infos[2]; // case2 只有1和2这两种字符
    if(m1 == 0) return s; // case3 只有0和2这两种字符
    int n = s.size(), i = 0;
    infos[0].clear(), infos[1].clear();
    for(; s[i] != '2'; i++) // 对第一个2之前的字符进行处理
        infos[s[i] - '0'].push_back(s[i]);
    string res = infos[0] + infos[1], temp; // temp 存放0和2
    for(; i < n; i++) {
        if(s[i] == '1') res.push_back('1');
        else temp.push_back(s[i]); // 保持0和2的相对位置
    }
    return res + temp;
}
int main() {
    cout << solve() << endl;
}