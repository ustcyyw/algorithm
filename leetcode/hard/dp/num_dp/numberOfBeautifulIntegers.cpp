/**
 * @Time : 2023/8/20-4:28 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 给你正整数 low ，high 和 k 。

如果一个数满足以下两个条件，那么它是 美丽的 ：

偶数数位的数目与奇数数位的数目相同。
这个整数可以被 k 整除。
请你返回范围 [low, high] 中美丽整数的数目。



示例 1：

输入：low = 10, high = 20, k = 3
输出：2
解释：给定范围中有 2 个美丽数字：[12,18]
- 12 是美丽整数，因为它有 1 个奇数数位和 1 个偶数数位，而且可以被 k = 3 整除。
- 18 是美丽整数，因为它有 1 个奇数数位和 1 个偶数数位，而且可以被 k = 3 整除。
以下是一些不是美丽整数的例子：
- 16 不是美丽整数，因为它不能被 k = 3 整除。
- 15 不是美丽整数，因为它的奇数数位和偶数数位的数目不相等。
给定范围内总共有 2 个美丽整数。
示例 2：

输入：low = 1, high = 10, k = 1
输出：1
解释：给定范围中有 1 个美丽数字：[10]
- 10 是美丽整数，因为它有 1 个奇数数位和 1 个偶数数位，而且可以被 k = 1 整除。
给定范围内总共有 1 个美丽整数。
示例 3：

输入：low = 5, high = 5, k = 2
输出：0
解释：给定范围中有 0 个美丽数字。
- 5 不是美丽整数，因为它的奇数数位和偶数数位的数目不相等。


提示：

0 < low <= high <= 109
0 < k <= 20
 */
#include<bits/stdc++.h>

using namespace std;

class Solution {
public:
    /*
     * 关键在于怎么判断能否除尽
     * 如果已经取了的数是pre
     * 1.pre如果刚好是k的倍数，假设 pre / k = t, 且 pre % k == 0
     * 那么接下来选数，这一部分数位增高1，仍然有pre % k == 0，只是pre / k = t
     * 在整个过程中 并不会影响是否会被k整除
     *
     * 2.只有pre不是k的倍数时，假设 pre / k = t, 且 pre % k = c1
     * 接下来选数, pre - c1 以为的部分如同情况1，是不会影响的
     * 只有c1，位数增高1，实际变为10 * c1，并且新选择了一个数字 i
     * 10 * c1 + i, 这部分可能会被k除尽, 也可能不会
     * 所以计算过程中要带着 10 * c1 + i 走
     */
    int numberOfBeautifulIntegers(int low, int high, int k) {
        return count(high, k) - count(low - 1, k);
    }

    int count(int num, int k) {
        string s = to_string(num);
        int n = s.size();
        vector<vector<vector<vector<int>>>> cache(n, vector(n, vector(n, vector(k * 10, -1))));
        function<int(int, int, int, int, bool, bool)> dfs = [&](int m, int even, int odd, int pre, bool is_limit,
                                                                bool is_num) -> int {
            if (m == n) return is_num && pre % k == 0 && even == odd;
            if (abs(even - odd) > n - m) return 0;
            if (is_num && !is_limit && cache[m][even][odd][pre] != -1)
                return cache[m][even][odd][pre];
            int res = 0;
            if (!is_num) res = dfs(m + 1, 0, 0, 0, false, false); // 当前位依旧不选数字的情况
            int up = is_limit ? s[m] - '0' : 9, down = is_num ? 0 : 1;
            for (int i = down; i <= up; i++) {
                int temp = (pre % k * 10) + i;
                res += dfs(m + 1, even + (i % 2 == 0), odd + (i % 2 != 0), temp, is_limit && i == up, true);
            }
            if (is_num && !is_limit) cache[m][even][odd][pre] = res;
            return res;
        };
        return dfs(0, 0, 0, 0, true, false);
    }
};

int main() {
    Solution s;

    cout << 0 << endl;
}