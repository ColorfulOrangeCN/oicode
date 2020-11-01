# ZJOI2006 物流运输
## Algorithm
DP, 最短路
## Mind
$ f(i) $ 表示前 $ i $ 天的最小花费
$ f(i) = min \{ f(j - 1) + 除去i ~ j天不可走的港口的最短路 \} + k $
## Inspiration
注意时间复杂度的准确计算
