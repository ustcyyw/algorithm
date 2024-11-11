/**
 * @Time : 2024/1/2-12:44 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

/*
 * 回文串 考虑左半边的情况 n = s.length, half = n / 2, m = n - 1
 * 用()表示s[a, b]及其对称区间, []表示s[c, d]及其对称区间
 * 在左半边 () 和 []的位置关系分为  3  大类
 *
 * 1. 包含关系[()] 或者 ([])，令外层区间范围是[l,r]
 * 那可以将内层区间不变，只更改[l,r]的排序顺序 试图左右对称
 * 如果是[()]，就是更改s[c, d], 等价与s[c, d]不变，更改其左边的对称区间
 * 如果是([])，就更改s[a, b]
 * 如果左右能对称 充要条件是 [l,r]和右边相应区间[m - r, m - l]内 字符及出现次数相同
 * 还要求[l,r]之外的不可变区间是对称的 也就是[0,l-1]和[r, half - 1]上对称
 *
 * 2. 不相交关系 [] () 或者 () []。记左边为[l1, r1]，右边为[l2, r2]
 * 两个可变区间内 字符及出现次数相同
 * 被这两个可变区间分割出来的另外三个不可变区间 要求是对称的
 * 也就是s[0,l1 - 1], s[r1 + 1, l2 - 1], s[r2 + 1, half - 1] 上对称
 *
 * 3. 相交情况 (   [   )   ] 或 [   (   ]   )
 * 相交区间之外的两部分 同理处理。讨论相交部分如何处理
 * 3.1 将对称区间也补全
 * l1    l2       r1      r2     m-r2    m-r1     m-l2  m-l1
 * (     [        )       ]   |   [       (        ]     )
 * [m-l2+1, m-l1]上不可以变 只能通过将[l1,r1]上的字母进行调整 将相应的字母放在[l1,l2-1]上进行对称
 * 记d1为[l1,r1]上的字符集 - [m-l2+1, m-l1]上的字符集
 * 如果d1中有负数，说明[m-l2+1, m-l1]上的字符，[l1,r1]缺少
 * 那么无论[l1,r1]如何排序 都无法让[m-l2+1, m-l1]和[l1,l2-1]对称 那整个字符串就必然不是回文串
 * 假设d1中不存在负数，通过调整让[m-l2+1, m-l1]和[l1,l2-1]对称
 * 那么 d1表示的字符集就是放在[l2, r1]上的字符集
 * 令d3表示[r1+1,r2]上的字符集，d4表示[m-r2,m-l2]的字符集
 * d1 + d3表示的字符集：[l2, r1]与[r1+1,r2]的交集 即[l2, r2]的字符集
 * d4：[m-r2,m-l2]可变，与d1 + d3是对称区间
 * 只要这两个区间字符集相等就能通过调整[m-r2,m-l2]得到对称子串
 * 于是回文对称条件为 d1 + d3 = d4 为了复用代码 改写为 d1 + (d3 - d4) = 0
 * 令d2 = d3 - d4，表示[r1+1,r2]上的字符集 - [m-r2,m-l2]的字符集
 * 于是回文串的条件简写为 d1 + d2 = 0
 *
 * 3.2 类似地进行计算
 * l1    l2       r1      r2     m-r2    m-r1     m-l2  m-l1
 * [     (        ]       )   |   (       [        )     ]
 * [m-r2, m-r1-1]上不可变，要通过[l2,r2]上的字母进行调整
 * 记d1为[l2,r2]上的字符集 - [m-r2, m-r1-1]上的字符集
 * 保证d1非负后，d1表示[l2, r1]上的字符集
 * d3: [l1, l2-1]上的字符集, d4: [m-r1, m-l1]上的字符集
 * d3 + d1 = d4 -->  d1 + (d3 - d4) = 0
 * d2 = [l1, l2 - 1]上的字符集 - [m-r1, m-l1]上的字符集
 *
 * 上述讨论都涉及到了统计字符集 显然使用字符的前缀和计算
 * 还讨论到不可变区间上的原本的对称性，也可以使用前缀和。
 * 如果s[i] == s[m - i]那么这个点对称，计数+1
 * 区间内的点都是对称点，该区间才是回文对称的：r - l + 1 == sum[r + 1] - sum[l]
 */
class Solution {
public:
    int n, half, m;
    vector<int> sum;
    vector<vector<int>> counts;
    vector<bool> canMakePalindromeQueries(string s, vector<vector<int>>& queries) {
        n = s.length(), half = n / 2, m = n - 1;
        sum.assign(half + 1, 0);
        for(int i = 1; i <= half; i++)
            sum[i] = sum[i - 1] + (s[i - 1] == s[n - i]);
        counts = vector(26, vector(n + 1, 0));
        for(int i = 1; i <= n; i++) {
            for(int j = 0; j < 26; j++)
                counts[j][i] = counts[j][i - 1];
            counts[s[i - 1] - 'a'][i]++;
        }
        vector<bool> res;
        for(vector<int>& q : queries) {
            int a = q[0], b = q[1], c = q[2], d = q[3];
            int ct = m - d, dt = m - c; // s[c,d]对称到左半边的对称区间s[ct, dt]
            if(ct > b || dt < a) { // 不相交的情况
                if(ct >= b) res.push_back(check1(a, b, ct, dt));
                else res.push_back(check1(ct, dt, a, b));
            } else if((a <= ct && b >= dt) || (ct <= a && dt >= b)) { // 包含的情况
                res.push_back(check2(min(a, ct), max(b, dt)));
            } else { // 相交的情况
                if(dt < b) res.push_back(check3(ct, dt, a, b, false));
                else res.push_back(check3(a, b, ct, dt, true)); // 情况3.1
            }
        }
        return res;
    }

    bool check1(int l1, int r1, int l2, int r2) {
        if(!is_pali(0, l1 - 1)) return false;
        if(!is_pali(r1 + 1, l2 - 1)) return false;
        if(!is_pali(r2 + 1, half - 1)) return false;
        return cnt_equal(l1, r1) && cnt_equal(l2, r2);
    }

    bool check2(int l, int r) {
        if(!is_pali(0, l - 1)) return false;
        if(!is_pali(r + 1, half - 1)) return false;
        return cnt_equal(l, r);
    }

    bool check3(int l1, int r1, int l2, int r2, bool flag) {
        if(!is_pali(0, l1 - 1)) return false;
        if(!is_pali(r2 + 1, half - 1)) return false;
        vector<int> d1, d2;
        if(flag) {
            d1 = diff(l1, r1, m - l2 + 1, m - l1);
            d2 = diff(r1 + 1, r2, m - r2, m - l2);
        } else {
            d1 = diff(l2, r2, m - r2, m - r1 - 1);
            d2 = diff(l1, l2 - 1, m - r1, m - l1);
        }
        for(int j = 0; j < 26; j++)
            if(d1[j] < 0 || d1[j] + d2[j] != 0) return false;
        return true;
    }
    // 计算两个区间上字母的数量差
    vector<int> diff(int l1, int r1, int l2, int r2) {
        vector<int> ans;
        for(int j = 0; j < 26; j++) {
            int c1 = counts[j][r1 + 1] - counts[j][l1], c2 = counts[j][r2 + 1] - counts[j][l2];
            ans.push_back(c1 - c2);
        }
        return ans;
    }
    // 计算对称区间内字符的统计情况是否相同
    bool cnt_equal(int l1, int r1) {
        int l2 = n - 1 - r1, r2 = n - 1 - l1;
        for(int j = 0; j < 26; j++) {
            int c1 = counts[j][r1 + 1] - counts[j][l1], c2 = counts[j][r2 + 1] - counts[j][l2];
            if(c1 != c2) return false;
        }
        return true;
    }
    // 检查区间[l,r]和其对称区间是否是回文
    bool is_pali(int l, int r) {
        if(l > r) return true;
        return r - l + 1 == sum[r + 1] - sum[l];
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}