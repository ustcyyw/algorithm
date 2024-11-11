/**
 * @Time : 2023/3/28-12:55 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
     * S1是n1个s1组成，S2是n2个s2组成
     * 我们可以找到n1个s1中总共有多少个s2，记为ans， M = ans / n2
     * 并且S1和S2都有周期性，容易想到可以考虑在s1的循环序列中匹配s2，什么时候会出现重复的匹配段 match
     * S1 中含有 t 个match，但是头尾有多少个s1，暂时不确定，就记为t1和t2
     * S1 = t1 * s1 + t * match + t2 * s1
     * 如何找到匹配段，匹配段中含有多少个s2
     * 可以用index表示用了cnt1个s1时，下一个要匹配的s2中字符的索引
     * cnt2记录此时已经匹配了多少个s2
     * 如果index第二次出现，就说明这两次出现之间，s2被完整匹配了一定的次数，s1也使用了一定的数量
     * 这就出现了循环
     *
     */
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        int l1 = s1.size(), l2 = s2.size();
        if (n1 * l1 < n2 * l2) return 0;
        int index = 0, cnt1 = 0, cnt2 = 0, ans = 0, left = 0;
        unordered_map<int, vector<int>> map; // 记录index -> {cnt1, cnt2}
        while (true) {
            cnt1++;
            for(char c : s1){ // 整个s1去匹配s2，查看用完一个s1后，s2下一次应该匹配的字符串
                if(c == s2[index]) index++;
                if(index == l2) {
                    cnt2++;
                    index = 0;
                }
            }
            if(cnt1 == n1) return cnt2 / n2; // 用玩了n1个s1还没找到匹配段，那就找到了总共可以匹配cnt2个s2，返回结果
            if(map.count(index)) {
                vector<int>& pre = map[index];
                // 匹配段之前已经匹配了pre[1]个s2，使用了pre[0]个s1，还剩n1 - pre[0]个
                // 一个匹配段用了cnt1 - pre[0]个s1，可以匹配出cnt2 - pre[1]个s2
                ans = pre[1] + (n1 - pre[0]) / (cnt1 - pre[0]) * (cnt2 - pre[1]);
                left = (n1 - pre[0]) % (cnt1 - pre[0]);
                break;
            }
            map[index] = {cnt1, cnt2};
        }
        while (left-- > 0) { // 匹配段之后剩余的left个s1还能够匹配多少个s2
            for(char c : s1){
                if(c == s2[index]) index++;
                if(index == l2) {
                    ans++;
                    index = 0;
                }
            }
        }
        return ans / n2;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}