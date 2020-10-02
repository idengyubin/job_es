[TOC]

# 1、文件与文件类型

## 1.1 文件定义

文件(File)是一个具有符号名字的一组相关联元素的有序序列。文件可以包含的内容十分广泛，操作系统和用户都可以将具有一定独立功能的一个程序模块、一组数据或一组文字命名为一个文件。

文件名：这个数据有序序列集合（文件）的名称。

##　1.2 文件的分类

文件有许多种，运行的方式也各有不同，在Windows系统中我们是通过文件后缀名来对文件进行分类的，如.txt，.doc，.mp4等，而在Linux中则不是，它不以文件后缀来区别文件的类型。

在Linux中，可以使用ls -l 来查看文件的类型，在Linux中，文件主要有7种类型。

+ \-  普通文件 指ASCII文本文件、二进制文件以及硬链接文件
+ d 目录文件 包含若干文件或者子目录
+ l  符号链接  只保留所指向文件的地址而非文件本身
+ p 管道文件  用于进程间通信
+ c  字符设备文件  原始的I/O设备文件，每次操作仅操作1个字符（例如键盘）
+ b  块设备文件   按块I/O设备文件（例如硬盘）
+ s   套接字   套接字是方便进程间通信的特殊文件，与管道不同的是套接字能通过网络连接使不同的计算机的进程进行通信

## 1.3 标准IO与文件IO的区别

+ 可移植性
+ 效率（缓存）
+ 文件IO是低级IO，可以访问不同的文件类型（管道/socket）等

# 2、 标准IO

## 2.1 流的定义

标准IO的核心对象是流，用标准IO打开一个文件时，就会创建一个FILE结构体描述该文件，我们把这个FILE结构体称为“流”。标准IO函数都是基于流做各种操作的。

流的分类分为**二进制流和文本流**

例如：2020在文本流中和二进制流中的数据类型不同：

文本流：      2020 --> '2' '0' '2' '0'    --> 50 48 50 48

二进制流：  2020 --> 数字2020 --> 0000011111010101

如下时FILE结构体：

```c
typedef struct 
{
    short level;                //缓冲区满/空的状态
    unsigned flags;             //文件状态标志
    char fd;                    //文件描述符 
    unsigned char hold;         //如缓冲区无内容则不读取字符 
    short bsize;                //缓冲区的大小 
    unsigned char *buffer;      //数据缓冲区的位置 
    unsigned char *curp;        //指针当前的指向 
    unsigned istemp;            //临时文件指示器 
    short token;                //用于有效性检查 
}FILE;
```

## 2.2 流的使用

在标准IO中预定义了三块缓冲区

+ stdin          -->         标准输入
+ stdout       -->          标准输出
+ stderr       -->           标准出错

标准IO流中的缓冲有三种类型

+ 全缓冲：在这种情况下，当缓冲区满后才进行实际的IO操作，对于存放在磁盘上的普通文件用标准I/O打开时默认是全缓冲的。当缓冲区满或者执行刷新缓冲区（fflush）操作才会进行磁盘操作。
+ 行缓冲：这种情况下，当在输入/输出中遇到换行符时执行I/O操作。-->标准输入/输出流（stdin/stdout）就是使用行缓冲。
+ 无缓冲：不使用缓冲区进行I/O操作，即对流的读写操作会立即操作实际文件。标准出错流（stderr）是不带缓冲的，这就使得当发生错误时，错误信息能第一时间显示在终端上，而不管错误信息是否包含换行符。

举个栗子：

```c
// 02stdout.c
#include <stdio.h>
#include <unistd.h>
                                                                                
int main(int argc,char* argv) {
    while(1) {
        printf("Hello World"); 
        sleep(1);
    }
}
```

效果：不会立即打印内容，而是等待'\n'或者缓冲区满才输出

```c
// 03stderr.c
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    while(1) {
        perror("Hello World"); 
        sleep(1);
    }
    return 0;
}
```

效果：stderr使用无缓冲，即使不使用'\n'仍能立即输出

练习：编写程序实现如下功能:

> 1、向标准输出流输出HelloWorld
>
> 2、向标准错误流输出HelloWorld
>
> 3、控制输出重定向，使程序仅能输出标准输出流的字符
>
> 4、控制输出重定向，使程序仅能输出标准错误流的字符

```c
// 04exer.c
#include <stdio.h>

int main(int argc, char* argv[]) {
    fprintf(stdout, "%s", "This is stdout:HelloWorld!\n");
    fprintf(stderr, "%s", "This is stderr:HelloWorld!\n");

    return 0;
}
```

实现第三步的功能： 在执行时，执行命令 ./a.out 2 > /dev/null

实现第四步的功能： 在执行时，执行命令 ./a.out 1 > /dev/null

# 3、标准IO编程

## 3.1 打开文件

使用fopen()/fdopen()/freopen()函数可以打开一个文件，

+ fopen()，最常用的打开文件方式
+ fdopen(), 可以指定打开文件的文件描述符和模式
+ freopen()，除可以指定打开的文件与模式，还可以指定特定的流



> fopen() 功能：找到文件，打开文件，返回文件流
>
> 头文件：#include <stdio.h>
>
> 函数原型： FILE *fopen(const char *path, const char *mode);
>
> 函数参数：path ：要打开的文件的路径及文件名
>
> ​				   mode：文件打开方式
>
> 以下是mode参数允许使用的取值及说明：
>
> ```c
>     r或rb            以只读的方式打开文件，该文件必须存在
> 
>     r+或r+b          以可读可写的方式打开文件，该文件必须存在
> 
>     w或wb            以只写的方式打开文件，若文件不存在则创建该文件；若文件存在则擦除文件原始内容，从文件开头开始操作文件
> 
>     w+或w+b       以可读可写的方式打开文件，若文件不存在则创建该文件；若文件存在则擦除文件原始内容，从文件开头开始操作文件
> 
>     a或ab              以附加的方式打开只写文件，若文件不存在则创建该文件；若文件存在，写入的数据追加在文件尾，即文件的原始内容会被保留
> 
>     a+或a+b         以附加的方式打开可读可写文件，若文件不存在则创建该文件；若文件存在，写入的数据追加在文件尾，即文件的原始内容会被保留
> ```
>
> 函数返回值：成功：指向文件的FILE类型指针  失败：NULL

## 3.2 关闭文件

使用fclose()函数关闭一个文件，该函数将缓冲区内的所有内容写入相关文件中并回收相应的系统资源

> fclose() 功能： 关闭文件
>
> 函数头文件：#include <stdio.h>
>
> 函数原型：int fclose(FILE *stream)
>
> 函数参数：stream：已打开的流指针
>
> 函数返回值：成功：0
>
> ​						失败：EOF

举个栗子：

```c
// 05fopen.c
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char* argv[]) {
    FILE* fp;
    fp = fopen("test.txt","w+b");
    if(NULL == fp) {
        perror("fopen()"); 
        exit(EXIT_FAILURE);
    }

    fclose(fp);    
    return 0;
}
```

## 3.3 错误输出

如上面的例子，perror函数可以在程序出错的时候将错误信息输出到标准错误流stderr中。由于标准错误流不使用缓冲所以可以及时显示错误信息。同时也可以不使用perror()，使用strerror()，如下：

```c
// 06stderror.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc,char* argv[]) {
    FILE* fp;
    fp = fopen("test1.txt","rb");
    if(NULL == fp) {
        fprintf(stderr, "%s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    fclose(fp);    
    return 0;
}
```

## 3.4 按字符输入/输出

函数getc()/ fgetc() / getchar()

>函数头文件：#include<stdio.h>
>
>函数原型 ： int getc(FILE *stream)
>
>​					 int fgetc(FILE *stream)
>
>​					 int getchar(void)
>
>函数参数：stream：输入文件流
>
>函数返回值：成功：读到的字符 失败：EOF

Note：

> **EOF只能作为文本文件（流）的结束符，因为若该文件（流）是二进制形式文件则会有-1的出现，因此无法使用EOF来表征文件结束**。为解决这个问题，在C语言中提供了一个feof()函数，若遇到文件结尾，函数feof()返回1，否则返回0。这个函数既可以判断二进制文件也可以判断文本文件。

函数putc() / fputc() / putchar() 

> 函数头文件：#include <stdio.h>
>
> 函数原型： int fputc(int c, FILE *stream);
>
>  					int putc(int c, FILE *stream);
>
> ​					int putchar(int c);
>
> 函数参数：c：待输出的字符（的ASCII码）
>
> ​				stream：输入文件流
>
> 函数返回值：
>
> ​			成功：输出字符c   失败：EOF 

举个栗子：从文件test.txt中读取字符然后输出到显示屏上

```c
// 07fgetc.c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    FILE* fp;
    char c;
    fp = fopen("test.txt","r");
    if(NULL == fp) {
        perror("fopen()"); 
        exit(EXIT_FAILURE);
    }
    while((c = fgetc(fp)) != EOF)
        fputc(c, stdout);

    fclose(fp);
    return 0;
}
```

练习：文件test.txt 中存放了各种符号(大写字符/小写字母/数字/特殊符号等)，将文件中的字母输出，非字母不输出

```c
// 08exer.c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int is_alpha(char c) {
    if((c > 'a' && c < 'z') || (c > 'A' && c < 'Z')) 
        return 1;
    else 
        return 0;
}

int main(int argc, char* argv[]) {
    FILE* fp;
    char c;
    fp = fopen("test.txt", "r");
    if(NULL == fp) {
        perror("fopen()"); 
        exit(EXIT_FAILURE);
    }

    while((c = (char)fgetc(fp)) != EOF) {
        if(is_alpha(c)) 
            fputc(c, stdout);
    }

    fclose(fp);

    return 0;
}
```

## 3.5 按行输入/输出

如果我们每次都按字符一个一个字符操作的话，程序执行效率会大大降低。因此标准I/O中提供了按行输入/输出的操作函数。

函数gets()/fgets()

> 函数头文件：#include <stdio.h>
>
> 函数原型：char *fgets(char *s, int size, FILE *stream);
>
> ​					 char *gets(char *s);
>
> 函数参数：s：存放输入字符的缓冲区地址
>
> ​					size：输入的字符串长度
>
> ​					stream：输入文件流
>
> 函数返回值：成功：s    失败或读到文件尾：NULL

> 简单来说gets()的执行逻辑是寻找该输入流的'\n'并将'\n'作为输入结束符，但是若输入流数据超过存储空间大小的话会覆盖掉超出部分的内存数据，**因此gets()函数十分容易造成缓冲区的溢出，不推荐使用**。而fgets()函数的第二个参数指定了一次读取的最大字符数量。当fgets()读取到'\n'或已经读取了size-1个字符后就会返回，并在整个读到的数据后面添加'\0'作为字符串结束符。因此fgets()的读取大小保证了不会造成缓冲区溢出，但是也意味着fgets()函数可能不会读取到完整的一行（即可能无法读取该行的结束符'\n'）。

函数fputs() / puts()

> 函数头文件： #include <stdio.h>
>
> 函数原型：int puts(const char *s)
>
> ​				int fputs(conse char *s,FILE *stream)
>
> 函数参数：s：存放输出字符的缓冲区地址
>
> ​				  stream：输出文件流
>
> 函数返回值：成功：非负数  失败：EOF

举个例子：使用fgets()函数，依次读取文件内的内容并输出。

```c
// 09fgets.c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    FILE* fp;
    char buf[1024] = {0};

    fp = fopen("test.txt", "r");
    if(NULL == fp) {
        perror("fopen()"); 
        exit(EXIT_FAILURE);
    }

    while(fgets(buf, sizeof(buf), fp) != NULL)
        fputs(buf, stdout);

    fclose(fp);
    return 0;
}
```

练习：使用fgets()函数统计某个文本文件有多少行

```c
// 10exer.c                                                      3,1            
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    FILE* fp;
    char buf[1024];
    int cnt = 0;

    fp = fopen("test.txt", "r");
    if(NULL == fp) {
        perror("fopen()"); 
        exit(EXIT_FAILURE);
    }

    while(fgets(buf, sizeof(buf), fp) != NULL) {
        if(buf[strlen(buf)-1] == '\n') 
            cnt++;
    }

    printf("cnt = %d\n", cnt);

    fclose(fp);
    return 0;
}
```

## 3.6 使用格式化输入/输出操作文件

```c
函数scanf()、fscanf()、sscanf()

    需要头文件：#include<stdio.h>

    函数原型：int scanf(const char *format,...);

              int fscanf(FILE *fp,const char *format,...);

              int sscanf(char *buf,const char *format,...);

    函数参数：format：输入的格式

             fp：待输入的流

             buf：待输入的缓冲区

    函数返回值：成功：读到的数据个数

              失败：EOF

函数 printf()、fprintf()、sprintf()

    需要头文件：#include<stdio.h>

    函数原型：int printf(const char *format,...);

              int fprintf(FILE *fp,const char *format,...);

              int sprintf(char *buf,const char *format,...);

    函数参数：format：输出的格式

            fp：待输出的流

            buf：待输出的缓冲区

    函数返回值：成功：输出的字符数

              失败：EOF
```

举个栗子：使用sscanf()函数读取一个字符串中指定数据

```c
// 11sscanf.c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    int a,b,c,d;
    char* ip = "192.168.1.1";
    FILE* fp = fopen("test1.txt", "w+");
    if(fp == NULL) {
        perror("fopen()"); 
        exit(EXIT_FAILURE);
    }

    sscanf(ip, "%d.%d.%d.%d",&a, &b, &c, &d);
    fprintf(fp, "%d %d %d %d", a, b, c, d);
    fclose(fp);

    return 0;
}
```

## 3.7 指定大小读/写文件

```c
 函数 fread()

    需要头文件：#include<stdio.h>

    函数原型：size_t fread(void *ptr,size_t size,size_t nmemb,FILE *stream);

    函数参数：ptr：存放读入数据的缓冲区

             size：读取的每个数据项的大小（单位字节）

             nmemb：读取的数据个数

             stream：要读取的流

    函数返回值：成功：实际读到的nmemb数目

              失败：0
--------------------------------------------------------------
函数 fwrite()

    需要头文件：#include<stdio.h>

    函数原型：size_t fwrite(void *ptr,size_t size,size_t nmemb,FILE *stream);

    函数参数：ptr：存放写入数据的缓冲区

              size：写入的每个数据项的大小（单位字节）

              nmemb：写入的数据个数

              stream：要写入的流

    函数返回值：成功：实际写入的nmemb数目

              失败：0
```

举个栗子：将一个整形数组{0,1,2,3,4,5,6,7,8,9}写入一个文件

```c
// 12fwrite.c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    FILE* fp;
    int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    char buf[64] = {0};

    int i;
    fp = fopen("test.txt", "w+b");
    if(fp == NULL) {
        perror("fopen()"); 
        exit(EXIT_FAILURE);
    }

    fwrite(a, sizeof(a[0]), sizeof(a) / sizeof(a[0]), fp);

    fclose(fp);
    return 0;
}
```

练习：实现文件拷贝

```c
// 13cp.c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    FILE* fp1; // --> FILE* fp1, *fp2 
    FILE* fp2;
    int len;
    char buf[1024];
    if(argc != 3) {
        fprintf(stderr, "Usage: %s <srcfile> <dstfile>\n",argv[0]); 
        exit(EXIT_FAILURE);
    }

    fp1 = fopen(argv[1], "r");
    if(fp1 == NULL) {
        perror("fopen()"); 
        exit(EXIT_FAILURE);
    }

    fp2 = fopen(argv[2], "w");
    if(fp2 == NULL) {
        perror("fopen()"); 
        exit(EXIT_FAILURE);
    }
    
    while((len = fread(buf, sizeof(char), sizeof(buf), fp1)) != 0)
        fwrite(buf, sizeof(char), len, fp2);

    fclose(fp1);
    fclose(fp2);

    return 0;
}
```

## 3.8 流的定位

 每次使用流打开文件并对文件进行操作后，都会让操作文件数据的位置发生偏移。在打开流的时候，偏移位置为0（即文件开头），随着读写的进行，偏移位置会不断向后，每次偏移量自动增加实际读写的大小。可以使用fseek()函数和ftell()函数对当前流的偏移量进行定位操作

```c
函数 fseek()

    需要头文件：#include<stdio.h>

    函数原型：int fseek(FILE *stream,long offset,int whence);

    函数参数：stream：要定位的流
            offset：相对于基准点whence的偏移量，正数表示向前（向文件尾方向）移动，负数表示向后（向文件头方向）移动，0表示不移动
			whence：基准点（取值见下）

    函数返回值：成功：0，改变读写位置
			  失败：EOF，不改变读写位置

    其中第三个参数whence的取值如下：

        SEEK_SET：代表文件起始位置，数字表示为0

        SEEK_CUR：代表文件当前的读写位置，数字表示为1

        SEEK_END：代表文件结束位置，数字表示为2
-------------------------------------------------------------------------       
函数ftell()

    需要头文件：#include<stdio.h>

    函数原型：int ftell(FILE *stream);

    函数参数：stream：要定位的流

    函数返回值：成功：返回当前的读写位置

              失败：EOF
```

举个栗子：获取文件的大小

```c
// 14ftell.c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    FILE* fp;
    int size;
    fp = fopen("test.txt", "r");
    if(fp == NULL) {
        perror("fopen()"); 
        exit(EXIT_FAILURE);
    }

    fseek(fp, 0, SEEK_END);
    size = ftell(fp);

    printf("size = %d\n", size);
    fclose(fp);
    return 0;
}
```

## 3.9 其他常用标准IO操作函数

```c
函数 fflush()

    需要头文件：#include<stdio.h>

    函数原型：int fflush(FILE *stream);

    函数参数：stream：操作的流  // 若fflush()的参数为0（或NULL）则会刷新所有已经打开的流的输出缓冲区。

    函数返回值：成功：0

              失败：EOF
/*
Note:
1、fflush()函数可能会执行失败，当fflush()函数执行失败时会返回EOF，这可能由于缓冲区数据意外丢失或其他未知原因。因此当某些重要文件需要设置时，若使用fflush()刷新缓冲区失败，则应考虑使用文件I/O相关操作（open()、close()、read()、write()等）来代替标准I/O操作

2、不要试图使用fflush()刷新stdin
*/
----------------------------------------------
函数 feof()

    需要头文件：#include<stdio.h>

    函数原型：int feof(FILE *stream);

    函数参数：stream：操作的流

    函数返回值：文件结束：非0的值

              文件未结束：0

    // feof()函数可以检测流上的文件结束符，若文件结束则返回一个非0值，否则返回0。
----------------------------------------------
函数rewind()

    需要头文件：#include<stdio.h>

    函数原型：void rewind(FILE *stream);

    函数参数：stream：操作的流

    函数返回值：无

// rewind()函数会将当前读写位置返回至文件开头（rewind原意为"（磁带等）回滚，倒带"），其等价于

// (void)fseek(stream, 0L, SEEK_SET)
```

小练习：循环记录系统的时间

```c
// 15time.c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

int main(int argc, char* argv[]) {
    FILE* fp;
    char buf[64];
    time_t t;
    if((fp = fopen("test.txt","w+")) == NULL) {
        perror("fopen()"); 
        exit(EXIT_FAILURE);
    }

    while(1) {
        t = time(NULL);
        fprintf(fp, "%s",asctime(localtime(&t)));
        fflush(NULL);
        printf("%s",asctime(localtime(&t)));
        sleep(1);
    }
    fclose(fp);

    return 0;
}
```

