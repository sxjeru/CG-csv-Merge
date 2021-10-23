# CG csv Merge 
Merge some Galgame CG images, which often include a large original picture and some small pictures with only difference parts, and a csv file. 

此程序可用于批量合并某些带有 csv 文件的 Galgame CG 差分图，使其仅包含差异部分的图片与原图合并成一张新图片并存储。
# 适用范围
由于本程序是以合并『俺の恋天使がポンコツすぎてコワ～い。』的CG为目的开发，因此适用范围有限，需满足以下条件：

- 源文件包含一张原图与至少一张差分图（图片均为jpg格式），还有一个csv文件。
- 所有文件名均以“l”结尾，且均为小写字母。（例如`ea01_01l`）<br>
原图举例：[Origin](https://file.sxjeru.top/%E5%9B%BE%E5%BA%8A/ea01_01l.jpg)<br>
差分图举例：[Diff](https://file.sxjeru.top/%E5%9B%BE%E5%BA%8A/ea01_02l.jpg)
- csv文件名字数 <= 9 (包含后缀名)；
- csv总数 <= 1000；
- 每张CG所包含的差分数 <= 100；
# 用法

# 编译
（应该没人会看上咱的辣鸡代码吧……）

开发环境：
- VS 2019
- OpenCV 4.5.4

其余条件参考上方“适用范围”。
#### 可以说这是咱这辈子第一个编程项目，在此纪念下，并谈点感想——
从 10.20 下午的“新建文件夹”开始，到现在刚好是两天。在这两天里，我深刻感受到新项目带来的压力。

一切都是新的开始，新的IDE，新的lib，新的代码，乃至新的想法。

不想去麻烦别人，因此遇到问题能用的便只有 Google 与网页翻译。

在此简单列举下本人遇到的麻烦：
- vscode 不支持链接外部库文件，或者至少不支持 OpenCV 的引用；（困扰了咱一夜，第二天决定换成 VS）
- 
