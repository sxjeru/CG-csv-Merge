# CG csv Merge 
Merge some Galgame CG images, which often include a large original picture and some small pictures with only difference parts, and a csv file. 

此程序可用于批量合并某些带有 csv 文件的 Galgame CG 差分图，使其仅包含差异部分的图片与原图合并成一张新图片并存储。
# 适用范围
由于本程序是以合并『俺の恋天使がポンコツすぎてコワ～い。』的CG为目的开发的，因此适用范围有限，通常需满足以下条件：

- Windows 7+ x64；
- Microsoft Visual C++ 2015-2019 Redistributable 运行库（[点此下载](https://aka.ms/vs/16/release/vc_redist.x64.exe)）；
- 源文件包含一张原图与至少一张差分图（图片均为jpg格式），还有一个csv文件；
- 所有文件名均以字母“l”结尾，且均为小写字母。（例如`ea01_01l`）<br>
原图举例：[Origin](https://file.sxjeru.top/%E5%9B%BE%E5%BA%8A/ea01_01l.jpg)<br>
差分图举例：[Diff](https://file.sxjeru.top/%E5%9B%BE%E5%BA%8A/ea01_02l.jpg)<br>
csv文件举例：![csv](https://file.sxjeru.top/%E5%9B%BE%E5%BA%8A/csv-simple.png)<br>
- csv文件名字数 <= 9 (包含后缀名)；
- csv总数 <= 1000；
- 每张CG所包含的差分数 <= 100。
# 用法
1. 前往 [Release](https://github.com/sxjeru/CG-csv-Merge/releases) 下载编译好的文件；
2. 解压后将待处理的 jpg 与 csv 文件粘贴到“event”文件夹中；
3. 双击“cg_csv_merge.exe”，开始合并；
4. 等待合并完成后，读取处理报告，并前往“result”文件夹获得成品CG；
5. ~~得到了好多涩图，好耶！！！~~
# 编译
（应该没人会看上咱的辣鸡代码吧……）

开发环境：
- VS 2019 x64
- OpenCV 4.5.4

其余条件参考上方“适用范围”。
<br><br>
### 可以说这是咱这辈子第一个编程项目，在此纪念下，并谈点感想——
从 10.20 下午的“新建文件夹”开始，到现在刚好是两天。在这两天里，我深刻感受到新项目带来的压力。

一切都是新的开始，新的IDE，新的lib，新的代码，乃至新的想法。

不想去麻烦别人，因此遇到问题能用的便只有 Google 与网页翻译。

在此简单列举下本人遇到的麻烦：
- vscode 不支持链接外部库文件，或者至少不支持 OpenCV 的引用；（困扰了咱一夜，第二天决定换成 VS）
- 如何用 OpenCV 实现图片合并；
- 由于把字符串变量加了引号，调试半天都报错，还以为是自己的OpenCV坏了；（现在想想怕不是当时被⑨附体了……）
- 如何批量获得csv文件名与文件数量；（system函数不支持读取cmd输出的结果，然后想到把输出存成txt文件，这样处理就简单了。）
- 字符串数组问题，包括：
  - 数组声明必须用常量；（因此才会有处理数量限制）
  - char*无从下手；（最后用了char二维数组才解决问题）
- 如何获得并处理多行字符串；（包括csv文件名批量获取与csv文件内容的处理）
- 如何拼接字符串；（+=）
- 如何获得模块化的 OpenCV dll文件用于分发；（原dll文件有约70MB，现在选用了部分模块，共计13.3MB）
- ~~如何把程序写成好多cpp文件用来装X~~  `诶嘿嘿 v`

我曾问自己，为什么要写这么个程序啊？还是之前从来没尝试过的东西，肯定写不出来的。

真的吗？难道咱学编程，真就只是为了应付考试，解决点数学问题，然后去仰望那些做项目的大佬吗？

不。编程是咱的兴趣所向，如果这条路都不去闯，就更别说其他路子了。我要迈出这一步。

好像… 是成功了诶。

---
当然，也感谢『俺の恋天使がポンコツすぎてコワ～い。』这部优秀的作品，让咱能产生这样的想法。

如果你对这部作品感兴趣，可以前往咱的[博客](https://wp.me/p9GKBL-8O)看看，有惊喜哦~

（若上方的博客无法访问，请前往[备用站点](https://blog.sxjeru.top/post/6/)）
