/**
 * @Time : 2023/12/22-10:43 PM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * f(x + y) = f(x) + f(y) - cnt(x,y) * 9, 其中cnt是相加过程中发生了多少次进位
 *
 * sum(f(a[i] + a[j]))
 * = f(a[1] + a[j]) + f(a[2] + a[j]) + .... f(a[n], a[j]), for j in [1, n]
 *
 * 其中 f(a[1] + a[j]) = n * f(a[1]) + {f(a[j]), for j in [1, n]} - {9 * cnt(1,j) for j in [1, n]}
 * 因此
 * sum(f(a[i] + a[j]))
 * = n * f(a[1]) + n * f(a[2]) + ... + f(a[n])
 * + n * {f(a[j]), for j in [1, n]}
 * - 9 * ({cnt(1,j) for j in [1, n]} + {cnt(2,j) for j in [1, n]} + ... + {cnt(n,j) for j in [1, n]})
 * = n * (f(a[1]) + f(a[2]) + ... + f(a[n])
 * + + n * (f(a[1]) + f(a[2]) + ... + f(a[n])
 * - - 9 * ({cnt(1,j) for j in [1, n]} + {cnt(2,j) for j in [1, n]} + ... + {cnt(n,j) for j in [1, n]})
 * 即 2n * 整个数组的数位和 - 9 * (a[0]与全部元素相加进位次数和 + a[1]与全部元素相加进位次数和 + ... )
 *
 * a[0]与全部元素相加进位次数和的计算 可以进行拆位 看个位、十位...分别进位了多少次
 * 要看个位进位了多少次 就将所有个位数字取出来 排序后 找到最小的与a[0]个位相加 >= 10的元素即可
 * 要看十位进位了多少次 就将所有最低两位数字取出来 排序后 找到最小的与a[0]最低两位数字相加 >= 100的元素即可
 * a[1], a[2]也要类似计算
 * 但是已经将所有数字都取出后排序了，在枚举a[i]的时候，就能通过双指针快速计算。
 */
#include<bits/stdc++.h>
using namespace std;

const int M = 15;
long long n, num;

long long count(vector<long long>& arr, long long t) {
    sort(arr.begin(), arr.end());
    long long cnt = 0;
    for(int i = 0, j = n - 1; i < n; i++) {
        while(j >= 0 && arr[i] + arr[j] >= t) j--;
        cnt += n - 1 - j;
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    vector<vector<long long>> arr(M + 1);
    long long sum = 0, cnt = 0;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> num;
        for(int j = 1; j <= M; j++)
            arr[j].push_back(num % (long long)pow(10, j));
        while(num) {
            sum += num % 10;
            num /= 10;
        }
    }
    for(int i = 1; i <= M; i++)
        cnt += count(arr[i], (long long)pow(10, i));
    cout << sum * 2 * n - 9 * cnt << endl;
}