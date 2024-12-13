/**
 * @Time : 2024/12/12-1:14 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : LC3326 数学 思维
 */
 /*
  * 将一个数因式分解 然后最大真因素 = num / 最小质因子
  * 并且质数不能操作
  * 也就是说每个数最多被操作一次
  *
  * 考虑当前数nums[j]，其前面已经保持非递减了
  * 如果nums[j] >= nums[j-1]，就先不管它 等后续再看是否要回过头来操作它
  * 否则得将前面的数进行操作，每次操作后要检查更前面的数是否依旧保持非递减
  *
  * 由于每个数最多操作一次 因此向前操作的这个过程最多每个数扫描一次 时间复杂度是n
  */
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5, mod = 1e9 + 7, P = 13331;
typedef long long ll;
int f[N];

vector<int> prime, isPrime(N, 1);
int init = []() {
    for (int i = 2; i < N; ++i) {
        if (isPrime[i] == 1) prime.push_back(i);
        for (int j = 0; j < prime.size() && i * prime[j] < N; ++j) {
            isPrime[i * prime[j]] = 0;
            if (i % prime[j] == 0)
                break;
        }
    }
    return 0;
}();

int find(int num) {
    if(f[num] != 0) return f[num];
    if(isPrime[num]) return -1;
    for(int k : prime) {
        if(num % k == 0) {
            return f[num] = num / k;
        }
    }
    return -1;
}

class Solution {
public:
    int minOperations(vector<int>& nums) {
        int n = nums.size(), ans = 0;
        for(int i = 1; i < n; i++) {
            int j = i;
            while(j > 0 && nums[j] < nums[j - 1]) {
                int k = find(nums[j - 1]);
                if(k == -1 || nums[j - 1] / k > nums[j]) return -1;
                nums[j - 1] /= k, ans++, j--;
            }
        }
        return ans;
    }
};