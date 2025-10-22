/**
 * @Time : 2022/5/7-11:05 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */
#include<bits/stdc++.h>

using namespace std;
/*
 * cpp的全局变量
 * 定义在class之外 并且通过匿名函数进行初始化
 * 这种全局变量初始化的匿名函数的写法为
 * int init = []() {
 *      <xxxx>
 *      return 0;
 * }();
 * 例子见下方
 */

// 预处理 [1-max_num]范围内所有数的因子
// 预处理每个数的所有因子，时间复杂度 O(MlogM)，M=1e5
// 外循环先枚举因子，内循环j代表包含该因子的数，显然是成倍增加的 j += i
//const int max_num = 100001;
//vector<int> divisors[max_num];
//int init = []() {
//    for (int i = 1; i < max_num; ++i)
//        for (int j = i; j < max_num; j += i)
//            divisors[j].push_back(i);
//    return 0;
//}();

/*
 * 预处理小于等于n的所有素数
 */
/*
 * 埃氏筛
 */
//const int n = 10000;
//vector<int> prime;
//int init = []() {
//    vector<int> isPrime(n + 1, 1);
//    for(int i = 2; i <= n; i++){
//        if(isPrime[i] == 0) continue; // 不是素数 跳过
//        if((long)i * i >= LONG_LONG_MAX) continue;
//        for(int j = i + i; j <= n; j += i) // 将素数的所有倍数标记成合数
//            isPrime[j] = 0;
//    }
//    for(int i = 2; i <= n; i++)
//        if(isPrime[i] == 1) prime.push_back(i);
//    return 0;
//}();

/*
 * 线性筛 又叫欧拉筛
 */
//const int n = 10000;
//vector<int> prime;
//int init = []() {
//    vector<int> isPrime(n + 1, 1);
//    for (int i = 2; i <= n; ++i) {
//        if (isPrime[i] == 1) prime.push_back(i);
//        for (int j = 0; j < prime.size() && i * prime[j] <= n; ++j) {
//            isPrime[i * prime[j]] = 0;
//            if (i % prime[j] == 0)
//                break;
//        }
//    }
//    return 0;
//}();

// 最大公约数 但cpp已经自带了，可以直接调用
int gcd(int a, int b) {
    if (a < b) return gcd(b, a);
    if (b == 0) return a;
    return gcd(b, a % b);
}

// 二维平面的方向
const int dx[4] = {0, 0, -1, 1}, dy[4] = {1, -1, 0, 0};
// 二维平面的八个方向
//const int dx[8] = {0, 0, 1, 1, 1, -1, -1, -1};
//const int dy[8] = {1, -1, 0, 1, -1, 0, 1, -1};
int n, m;

void bfs(int x, int y) {
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
    }
}


// 获取整型数中二进制的1
int bit_count(int i) {
    i = i - ((i >> 1) & 0x55555555);
    i = (i & 0x33333333) + ((i >> 2) & 0x33333333);
    i = (i + (i >> 4)) & 0x0f0f0f0f;
    i = i + (i >> 8);
    i = i + (i >> 16);
    return i & 0x3f;
}
// 内置函数 针对int数据类型
//__builtin_popcount(1);
// 针对long long数据类型的是
//__builtin_popcountll(1ll);

/*
 lcp[i][j]表示在字符串 s 中，以i开始的后缀s[i,n-1]与 以j开始的后缀s[j,n-1]的「最长公共前缀」的长度
 算法竞赛，学习过「后缀数组」，那么上述的lcp是可以通过后缀数组 +ST 表在O(nlogn) 的时间内预处理得到的。

 时间复杂度不高的情况下，可以使用动态规划 n^2地处理得到
*/

vector<vector<int>> get_lcp(string &s) {
    int n = s.size();
    vector<vector<int>> lcp = vector(n, vector(n, 0));
    for (int j = n - 1; j >= 0; j--) {
        for (int i = j; i >= 0; i--) {
            if (s[i] != s[j]) continue;
            if (i != n - 1 && j != n - 1)
                lcp[i][j] = 1 + lcp[i + 1][j + 1];
            else lcp[i][j] = 1;
        }
    }
    return lcp;
}

// 遍历 u 的非空子集, s 是 u 的一个非空子集
//for (int s = u; s; s = (s - 1) & u) {

//}
//

/*
* 优先队列
* priority_queue
* 默认是大顶堆，直接声明为priority_queue<T>
* 要使用小顶堆，可以声明为priority_queue<T, vector<T>, greater<>>
*/
// 优先队列自定义 以元素为pair为例子
struct cmp{
    bool operator()(pair<int, int>& a, pair<int, int>& b){
        return a.second > b.second;
    }
};
priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq;

/*
 * 将数组进行离散化
 */
vector<int> scatter(vector<int>& num) {
    vector<int> pos = num;
    sort(pos.begin(), pos.end());
    pos.erase(unique(pos.begin(), pos.end()), pos.end());
    return pos;
}
/*
 * 离散化之后查询某个数在第几个位置 可以同时记录该位置对应的数
 */
int find(vector<int>& pos, int val) {
    return lower_bound(pos.begin(), pos.end(), val) - pos.begin();
}


class Solution {
    /**
     * int的最大值 0x7FFFFFFF
     * 取模运算    mod = 1000000007
     */

    // 求vector最大值的简单写法
    // int mv = *max_element(nums.begin(), nums.end());

    /**
     * lambda 格式
     * [ capture-list ] ( params ) -> return_type { body }
     *
     * 在比较类的时候写lambda表达式 要使用引用来做，否则很慢
     * 例如 对一个vector<vector<int>>比较的时候
     * [](const auto& a, const auto& b) -> bool {return a[0] < b[0];}
     */

    /**
     * map 中找到比指定key更小的最大键
     * auto it = map1.lower_bound(5); lower_bound 找到小于等于key的键的指针
     * cout << (--it)->first << endl; 然后指针左移得到比key小的最大键对应的指针
     */

    /**
     * 通过时间戳的方法来帮助确定树中结点的父子关系：
     * 具体做法是用in, out两个数组来存储访问结点相关的时间
     * 访问某结点的时候将其in时间设置为t，然后t+1
     * 当某个结点的子树都访问完毕，要返回时，将其时间设置out设置为t，然后t+1
     * （这里t是个全局变量）
     * 当满足 in[a] < in[b] < out[a] 时，说明
     * 先访问了a，然后访问b；而且访问了b之后，a才访问完所有子结点，因此a是b的祖先结点
     */

    /**
     * 二分查找
     * lower_bound(arr.begin(), arr.end(), val)
     * 找到有序数组中大于等于val的最小位置
     * 要得到索引 就用 int index = lower_bound(arr.begin(), arr.end(), val) - arr.begin()
     * upper_bound(arr.begin(), arr.end(), val)
     * 找到有序数组中大于val的最小位置
     */
public:

};

int main() {
    vector<int> arr = {1, 2, 3, 4};
    auto t = lower_bound(arr.begin(), arr.end(), 5);
    cout << (t == arr.end()) << endl;
}