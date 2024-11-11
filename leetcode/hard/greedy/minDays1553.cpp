/**
 * @Time : 2022/11/30-10:30 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    /**
     * 看数据量 用记忆化搜索也会超时 得考虑如何进行贪心
     * 1.进行减1操作，从n到m，需要到操作次数为m-n
     * 2.如果先将n进行k次减1操作，得到n-k。如果(n-k) % 3 == 0，那么减小到 (n-k)/3 共使用了k+1次
     * (n-k) % 3 == 0意味着(n-k+3) % 3 == 0
     * 如果先使用k-3次减1操作，再使用一次 /3 操作得到(n-k)/3 + 1,再使用一次减1操作，得到(n-k)/3只用了k-1次
     * 因此，在能除3的时候，除以3比减1更优。一个数可能减1 (2次/1次/0次)就可以除3
     * 因此一种可能的最优解是 减去 n % 3 次后进行一次/3操作
     * 3.同理考虑/2相关路径，一种可能的最优解是 减去 n % 2 次后进行一次/2操作
     * 只要考虑2和3两种方式即可，因为他们都比减1要优
     */
    unordered_map<int, int> cache;
    int minDays(int n) {
        if(n == 0 || n == 1 || n == 2) return n;
        if(cache.count(n)) return cache[n];
        int ans = n % 2 + minDays(n / 2) + 1;
        ans = min(ans, n % 3 + minDays(n / 3) + 1);
        cache[n] = ans;
        return ans;
    }
};

int main(){
    Solution s;
    
    cout << 0 << endl;
}