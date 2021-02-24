# 1 文本处理工具

## 1.1 grep工具

> grep是行过滤工具，用于根据关键字进行过滤

**语法：**

```powershell
# grep [选项] '关键字' 文件名
```

**常见选项：**

```powershell
OPTIONS:
    -i: 不区分大小写
    -v: 查找不包含指定内容的行,反向选择
    -w: 按单词搜索
    -o: 打印匹配关键字
    -c: 统计匹配到的行数
    -n: 显示行号
    -r: 逐层遍历目录查找
    -A: 显示匹配行及后面多少行	
    -B: 显示匹配行及前面多少行
    -C: 显示匹配行前后多少行
    -l：只列出匹配的文件名
    -L：列出不匹配的文件名
    -e: 使用正则匹配
    -E:使用扩展正则匹配
    ^key:以关键字开头
    key$:以关键字结尾
    ^$:匹配空行
    --color=auto ：可以将找到的关键词部分加上颜色的显示
```

**颜色显示（别名设置）：**

```powershell
临时设置：
# alias grep='grep --color=auto'			//只针对当前终端和当前用户生效

永久设置：
1）全局（针对所有用户生效）
vim /etc/bashrc
alias grep='grep --color=auto'
source /etc/bashrc

2）局部（针对具体的某个用户）
vim ~/.bashrc
alias grep='grep --color=auto'
source ~/.bashrc
```

**举例说明：**

**Note：**不要直接使用/etc/passwd文件，将其拷贝到/tmp下做实验!

```powershell
# grep -i root passwd						// 忽略大小写匹配包含root的行
# grep -w ftp passwd 						// 精确匹配ftp单词
# grep -w hello passwd 						// 精确匹配hello单词;自己添加包含hello的行到文件
# grep -wo ftp passwd 						// 打印匹配到的关键字ftp
# grep -n root passwd 						// 打印匹配到root关键字的行号
# grep -ni root passwd 						// 忽略大小写匹配统计包含关键字root的行
# grep -nic root passwd						// 忽略大小写匹配统计包含关键字root的行数
# grep -i ^root passwd 						// 忽略大小写匹配以root开头的行
# grep bash$ passwd 							// 匹配以bash结尾的行
# grep -n ^$ passwd 							// 匹配空行并打印行号
# grep ^# /etc/vsftpd/vsftpd.conf		// 匹配以#号开头的行
# grep -v ^# /etc/vsftpd/vsftpd.conf	// 匹配不以#号开头的行
# grep -A 5 mail passwd 				 	// 匹配包含mail关键字及其后5行
# grep -B 5 mail passwd 				 	// 匹配包含mail关键字及其前5行
# grep -C 5 mail passwd 					// 匹配包含mail关键字及其前后5行
```

## 1.2 cut工具

> cut是列截取工具，用于列的截取

**语法：**

```powershell
# cut 选项  文件名
```

**常见选项：**

```powershell
-c:	以字符为单位进行分割,截取
-d:	自定义分隔符，默认为制表符\t
-f:	与-d一起使用，指定截取哪个区域
```

**举例说明:**

```powershell
# cut -d: -f1 1.txt 			以:冒号分割，截取第1列内容
# cut -d: -f1,6,7 1.txt 	以:冒号分割，截取第1,6,7列内容
# cut -c4 1.txt 				截取文件中每行第4个字符
# cut -c1-4 1.txt 			截取文件中每行的1-4个字符
# cut -c4-10 1.txt 			截取文件中每行的4-10个字符
# cut -c5- 1.txt 				从第5个字符开始截取后面所有字符
```

**小练习：**
用小工具列出你当系统的运行级别。

1. 如何查看系统运行级别
   - 命令`runlevel`
   - 文件`/etc/inittab`
2. 如何过滤运行级别

```powershell
runlevel |cut -c3
runlevel | cut -d ' ' -f2
grep -v '^#' /etc/inittab | cut -d: -f2
grep '^id' /etc/inittab |cut -d: -f2
grep "initdefault:$" /etc/inittab | cut -c4
grep -v ^# /etc/inittab |cut -c4
grep 'id:' /etc/inittab |cut -d: -f2
cut -d':' -f2 /etc/inittab |grep -v ^#
cut -c4 /etc/inittab |tail -1
cut -d: -f2 /etc/inittab |tail -1
```