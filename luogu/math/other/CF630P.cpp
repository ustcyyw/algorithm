/**
 * @Time : 2024/3/18-10:49 AM
 * @Author : yyw@ustc
 * @E-mail : yang0@mail.ustc.edu.cn
 * @Github : https://github.com/ustcyyw
 * @desc : 
 */

/*
 * 用整圆的面积s - n个类似小扇形的面积(s1)
 * s1的计算 = 一个三角形的面积(s2) + 圆弧和一条直线组成的边缘部分(s3)
 * s3的计算 = 1 / n的大圆扇形 - 对应的等腰三角形面积s4
 * s4的计算：是等腰三角形 r * cos(c4) * r * sin(c4)
 * s2的计算：
 * 是等腰三角形 并且2个底角 + 3个star的顶角 = 180度
 * star的顶角度数：顶角是圆周角，所有顶角对应的圆心角刚好是360度，那么所有顶角度数和为180，一个顶角为 180 / n
 * 所以等腰三角形的底角为 c2 = (180 - 540 / n) * 0.5
 * s2 = 1 / 4 * 底边长l的平方 * tan(c2)
 * 底边长l的计算：2r * sin(180 / n)
 *
 * cpp中三角函数传参是弧度制。角度制转弧度制：用角度 * pai / 180
 */
#include<bits/stdc++.h>
typedef long double ld;
using namespace std;
const int N = 60; // 26 * 2的大小就足够
const ld pai = acos(-1.0);
int n, r;

int main() {
    ios::sync_with_stdio(0); cin.tie(0), cout.tie(0); // 加速cin, cout
    cin >> n >> r;
    ld s = pai * r * r;
    ld c4 = pai / n;
    ld s4 = r * cos(c4) * r * sin(c4);
    ld s3 = s / n - s4;
    ld c2 = (180 - 540.0 / n) * 0.5 * pai / 180;
    ld l = 2 * r * sin(c4), s2 = 0.25 * l * l * tan(c2);
    ld s1 = s2 + s3, ans = s - n * s1;
    printf("%.12Lf\n", ans);
};