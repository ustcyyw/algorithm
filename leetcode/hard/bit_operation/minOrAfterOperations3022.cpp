/**
 * @Time : 2024/1/28-9:14 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 周赛382 t4
 */

/*
 * 与位运算相关 首先考虑拆位
 * 要使最后进行或运算值最小 优先将二进制高位的1消除
 * 先考虑最高位是否能被消除，如果可以 最终答案中该位为0，否则最终答案中该位是1 (res += 1 << j)
 * 在高位已经确定的情况下，考虑更低位是否可以消除时，高位也要继续校验
 *
 * 假设当前在考虑的二进制位是lowD（尝试看lowD是否能为0，比lowD高的位已经确定了），所有数中二进制最高位是maxD
 * target二进制位[lowD, maxD]上某一位j为1, 也就是(1 << j) & target > 0
 * 就是不消除这一位，那么针对这一位不用做任何处理
 * 反之，就得消除这一位，要将所有这一位为1的数都通过与运算消除 并且最多操作k次
 *
 * 通过check函数来校验：满足target在二进制位[lowD, maxD]上的要求，最少操作数是否 <= k
 * 要知道最少操作数 定义dp[i]:截止第i个元素，满足二进制位要求的最少操作次数
 * dp[i] = min{dp[j] + i - j - 1}, j属于[0, l - 1]
 * = min{dp[j] - j - 1} + i, j属于[0, l - 1]
 * dp[j]:截止第j哥元素，满足二进制位要求的最少操作次数
 * i - j - 1:就是将[j + 1, i]上的数进行与运算的操作次数
 * 其中l是使得二进制条件得到满足的最大边界，即将[l, i]上的数进行与运算，能将这个区域上不该存在的1消除
 * 这里l有2个区间性质：
 * 1. 由于与运算某位存在一个0，则整个与运算都是0。
 * 因此 将[l, i]上的数进行与运算，满足二进制要求，就一定有[l - 1, i]上的数进行与运算，也满足二进制要求
 * 所以找到这个边界l，就可以对j进行枚举 j属于[0, l - 1]
 * 2. 随着i的增大，l不变或者增大，原因同样来源于与运算的性质
 * nums[i]的某些二进制位是0，就可能导致去掉nums[l]，也可以满足二进制要求
 * 因此l的变化 就用双指针的方法去维护即可。
 *
 * 由于l不变或者递增，每当l增加 j枚举的位置也增加来，要取val = min{dp[j] - j - 1}
 * 只需要考虑j可枚举到的新位置的影响，即 val = min(val, dp[lt - 2] - (lt - 2) - 1)
 * (l = lt - 1, j属于[0, l - 1], 也就是j属于[0, lt - 2],
 * 新增的选项dp[j] - j - 1也就是 dp[lt - 2] - (lt - 2) - 1)
 *
 * 最后 如何校验[l, i]上的数进行与运算，能满足二进制要求
 * 就相当于所有要消除1的位，在区间[l, i]上存在1个0即可，与区间和有关 使用前缀和做优化即可。
 */

#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;

class Solution {
public:
    int n, k, dSum[N][32] = {0}, maxD = 0; // 二进制位中1的前缀和
    int minOrAfterOperations(vector<int>& nums, int k) {
        this->n = nums.size(), this->k = k;
        for(int i = 1; i <= n; i++) {
            for(int j = 0; j < 30; j++)
                dSum[i][j] = dSum[i - 1][j];
            for(int j = 0; j < 30; j++)
                if((1 << j) & nums[i - 1])
                    dSum[i][j]++, maxD = max(maxD, j);
        }
        int res = 0;
        for(int j = maxD; j >= 0; j--) {
            if(!check(res, j)) res += (1 << j);
        }
        return res;
    }

    bool digit_check(int target, int l, int i, int lowD) {
        for(int j = lowD; j <= maxD; j++) {
            if((1 << j) & target) continue;
            int cnt = dSum[i][j] - dSum[l - 1][j];
            if(cnt == i - l + 1) return false; // 说明这个区间上 每个数在该二进制上都是1 没法消除
        }
        return true;
    }

    bool check(int target, int lowD) {
        vector<int> dp(n + 1, 1e9);
        // 双指针 维护最大的lt, 使得l = lt - 1是最大边界
        for(int i = 1, lt = 1, val = -1; i <= n; i++) {
            while(lt <= i && digit_check(target, lt, i, lowD)) {
                lt++;
                if(lt - 2 >= 0) val = min(val, dp[lt - 2] - (lt - 2) - 1);
            }
            if(lt - 1 > 0 ) dp[i] = val + i;
        }
        return dp[n] <= k;
    }
};

/*
 * 解法2 简单的优雅解
 * 拆位、从高位开始考虑的试填法思路一致 但check函数不同
 *
 * 从nums[0]开始考虑 如果nums[0]不满足二进制位限定但要求
 * 将nums[0] & nums[1]，但如果还不能满足要求，就得继续 nums[0] & nums[1] & nums[2]
 * 假设一直到 nums[0] & nums[1] & nums[2] & ... & nums[i]才满足要求
 * 这个子数组长度为len, 那么操作了len - 1次
 * 然后考虑nums[i + 1]是否满足要求，如果不满足 nums[i + 1] & nums[i + 2]
 * 重复上述过程，不断地找到可以满足要求的子数组
 * 注意 可能会出现最后一个子数组 nums[j] & nums[j + 1] & ... & nums[n - 1] 无法满足要求的情况
 * 此时就需要将这个子数组和上一个子数组进行and操作剩下的数 再进行一次操作
 * 操作次数就是子数组的长度len 而非 len-1
 *
 * 满足二进制位限定的要求：指的就是在某些二进制位上不能出现1，也就是进行位与操作后 指定的二进制位上都是0
 * 可以使用mask将不校验的位抹去来简化计算。
 * 假设当前考虑的二进制位是d 不校验的位有两个部分：
 * a.比d小的位
 * b.比d大的位且确定没法操作为0的位。
 * 将mask的这些位设置为0 并且于nums中的数字先进行与运算 就能排除这些位
 */
class Solution2 {
public:
    int minOrAfterOperations(vector<int>& nums, int k) {
        int n = nums.size(), res = 0, mask = 0;
        function<bool()> check = [&]() -> bool {
            int cnt = 0;
            for(int i = 0, j, temp; i < n; ) {
                temp = nums[i] & mask, j = i + 1;
                while(j < n && temp)
                    temp &= nums[j++] & mask;
                cnt += temp == 0 ? j - i - 1 : j - i;
                if(cnt > k) return false;
                i = j;
            }
            return true;
        };
        for(int j = 29; j >= 0; j--) {
            int t = 1 << j;
            mask |= t;
            if(!check()) // 某一位无法设置为0，答案中该位为1，并且mask中不再校验该位
                res += t, mask ^= t;
        }
        return res;
    }
};