# Huffman_Compress
## 数据结构课程设计：哈夫曼压缩软件设计，男女运动员匹配问题
本目录下（..\Huffman_Compress）是使用vs编写的核心代码部分，main.cpp是测试程序。
..\Huffman_Compress\QTHuffman_Compress目录下是结合利用QT编写的多个界面文件的最终可视化版本。

### A
#### 5、哈夫曼压缩软件设计
##### 【问题描述】  
采用哈夫曼树求得的用于通信的二进制编码称为哈夫曼编码。利用哈夫曼编码对文本或图像进行数据压缩，设计数据压缩软件。  
##### 【设计要求】  
设计基于哈夫曼编码的文本和图像压缩软件。  
（1）采用静态链表的二叉树等数据结构。  
（2）可以随机、文件及人工输入数据。  
（3）创建哈夫曼树，生成哈夫曼编码和译码。  
（4）源码、编码和压缩后的信息均以文件形式保存。  
（5）可以查询和更新数据。  
（6）其它完善性或扩展性功能。  

### B
#### 4、男女运动员最佳组合
##### 【问题描述】
设有N个男羽毛球运动员和N个女羽毛球运动员，现组成N对男女混合最佳组合。每个男运动员对每个女运动员都有一个满意度排序，用矩阵mf[0:n-1][0:n-1]表示。mf[i][j]表示第i个男运动员对第j个女运动员的满意度，满意度值越高，满意程度越高。同理，每个女运动员对每个男运动员也有一个满意度排序，用矩阵fm[0:n-1][0:n-1]表示。男女运动员之间的一个完全匹配称为一个组合。
##### 【设计要求】
设计对于给定的满意度，求最佳组合的程序，使得满意度总和达到最大。  
（1）采用STL的一维向量类构造构造二维向量矩阵。  
（2）应用基本运算，设计算法求解。
