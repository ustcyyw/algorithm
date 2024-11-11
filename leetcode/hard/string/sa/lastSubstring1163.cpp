/**
 * @Time : 2023/2/27-4:20 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6;
int x[N], y[N], c[N], sa[N];

void get_sa(string &s) {
    memset(x, 0, sizeof(x)), memset(y, 0, sizeof(y));
    memset(c, 0, sizeof(c)), memset(sa, 0, sizeof(sa));
    int n = s.size(), m = 26; // m表示字符集的大小，也是桶的个数
    s = " " + s; // 因为后缀编号从1开始取，因此设置一个哨兵
    int i, w; // w表示倍增法中区间的长度
    // 初始化
    // 初始排名x[i]就是s[i]这个字符在字符集中的排序，并且进行桶排序的计数。x[i] = s[i] - 'a' + 1可能要换成字符排序映射
    for (i = 1; i <= n; i++) c[x[i] = s[i] - 'a' + 1]++;
    // 计数后求前缀和，得出key1对应的排序范围
    for (i = 1; i <= m; i++) c[i] += c[i - 1];
    // 根据key2的排序，倒着放入key1的范围，得到初始化的sa
    // x[i] 字符i的排序，c[x[i]]该字符的排序范围，倒序占用一个位置后，要减少1。
    // sa[c[x[i]]--] = i, c[x[i]]--这个排序对应的字符下标就是i
    for (i = n; i >= 1; i--) sa[c[x[i]]--] = i;

    // 倍增法
    for (w = 1; w <= n; w <<= 1) {
        int num = 0;
        // s[n - w + 1, n]这一部分后缀，没有key2，理解为key2无穷小
        // 因此key2最小从1开始，依次对应这部分后缀
        for (i = n - w + 1; i <= n; i++) y[++num] = i;
        // 除开无穷小的key2, 后缀排序从小到大查看，看对应的下标sa[i]，sa[i]如果在[w + 1, n]上，它就可以做为key2
        // 倍增区间长为w，这个key2对应的key1的位置就是sa[i] - w
        for (i = 1; i <= n; i++)
            if (sa[i] > w) y[++num] = sa[i] - w;

        // 更新了key2排名对应的后缀编号y后，进行与初始化类似的桶排序
        // step1 : 清空桶, 桶的个数为m
        for (i = 1; i <= m; i++) c[i] = 0;
        // step2 : 对key1的排序序号进行计数
        for (i = 1; i <= n; i++) c[x[i]]++;
        // step3 : 计数数组的前缀和，确定key1对应的排序区间
        for (i = 1; i <= m; i++) c[i] += c[i - 1];
        // step4 : 根据key2找到对应的后缀编号，在相应的排序区间上，倒序占用一个位置
        // y[i]: key2排序为i的后缀编号，x[y[i]]该后缀对应的key1的排序序号
        // c[x[y[i]]]: 此时应该占用的位置，也就是排序序号。
        // 那么这个排序序号对应的后缀编号（字符下标）就是y[i]
        for (i = n; i >= 1; i--) sa[c[x[y[i]]]--] = y[i];

        // 要更新x，且y已经没用了（因为倍增区间的长度变了，key2的信息要更新），就先用y来存x
        swap(x, y);
        int p = 0; // 表示key1的排名, 现在y表示key1的排序数组
        for (i = 1; i <= n; i++) {
            // sa[i]排序为i的后缀编号，y[sa[i]]该后缀key1的排名
            // sa[i] + w 这个后缀对应的第二个关键字的索引，y[sa[i] + w]就是该后缀的key2的排名
            // 如果key1和key2的排序都相等，这一轮排序后，新排序序列里，他们的排名都是p
            // 否则 新序列里排名会增加1
            if (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + w] == y[sa[i - 1] + w]) x[sa[i]] = p;
            else x[sa[i]] = ++p;
        }
        if (p == n) break; // 排序完成
        m = p; // 更新字符集大小
    }
}

class Solution {
public:
    string lastSubstring(string s) {
        int n = s.size();
        get_sa(s);
        int lo = sa[n]; // 排序最后的后缀的开始下标
        return s.substr(lo, s.size() - lo);
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}