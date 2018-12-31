# 数据结构课程设计作业

2018~2019学年第一学期同济大学软件学院数据结构课程设计作业

Data Structure Course Projects, SSE, Tongji University, 2018

## 目录

- [题目1 考试报名系统](./Ex01-StudentManager/)
- [题目2 两个有序链表序列的交集](./Ex02-LinkedListIntersection/)
- [题目3 勇闯迷宫游戏](./Ex03-Maze/)
- [题目4 表达式转换](./Ex04-ExpressionConversion/)
- [题目5 银行业务](./Ex05-BankCounter/)
- [题目6 家谱管理系统](./Ex06-GenealogyBook/)
- [题目7 修理牧场](./Ex07-FixFarm/)
- [题目8 电网建设造价模拟系统](./Ex08-GridPriceCalc/)
- [题目9 关键活动](./Ex09-CriticalActivity/)
- [题目10 8种排序算法的比较案例](./Ex10-SortComparison/)

项目说明见各目录下的 `README.md`


## 编译说明

根目录下附有 `build_all.sh` 及 `build_windows.cmd` 用于构建所有题目的可执行文件.

`build_all.sh` 用于*nix上的编译操作, 其依赖于 `gcc g++ make`. 对于示例中的 Ubuntu 18.10 , 可以使用 `sudo apt-get update && sudo apt-get install build-essential` 命令安装上述工具.

`build_windows.bat` 用于Windows系统上的编译操作, 其依赖于 Microsoft Visual Studio Community 2017.

所有项目的源代码文件均采用 UTF-8 without BOM 编码, 在部分系统下中文会出现乱码的情况.


## LICENSE

WTFPL