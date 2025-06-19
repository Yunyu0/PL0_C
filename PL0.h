#pragma once
/*PL/0 编译系统C版本头文件 pl0.h*/

// note：定义PL/0编译器能够识别的保留字数量为14
# define norw 14                 /*关键字个数*/
# define txmax 100               /*名字表容量*/
# define nmax  14                /*number的最大位数*/
# define al 10                   /*符号的最大长度*/
# define amax 2047               /*地址上界*/
# define levmax 3                /*最大允许过程嵌套声明层数[0，lexmax]*/
# define cxmax 200               /*最多的虚拟机代码数*/
/*符号*/
/* note：
enum symbol：定义了所有符号的类名，包括：
nul：空（不认识的单词） 
保留字、运算符、界符：一符一类
标识符（ident）：所有标识符是一类
能识别的是：无符号正整数
所有正数是一类number 
*/
enum symbol {
	nul, ident, number, plus, minus,
	times, slash, oddsym, eql, neq,
	lss, leq, gtr, geq, lparen,
	rparen, comma, semicolon, period, becomes,
	beginsym, endsym, ifsym, thensym, whilesym,
	writesym, readsym, dosym, callsym, constsym,
	varsym, procsym, elsesym, exclamation, plusequal,
};

#define symnum 35 // note：symnum：编译器能够识别的所有符号的总数
/*-------------*/
// note：定义了名字表中对象的类型，包括常量、变量和过程
enum object {
	constant,
	variable,
	procedur,
};
/*--------------*/

// note:定义了虚拟机的指令，包括分配常量、算术运算、加载、存储、调用子过程等
enum fct {
	lit, opr, lod, sto, cal, inte, jmp, jpc,
};
#define fctnum 8
/*--------------*/

//note：定义了虚拟机代码的结构，包含指令类型、层次和地址。
 struct instruction 
{
	enum fct f;
	int l;
	int a;
};

FILE* fas;
FILE* fa;
FILE* fa1;
FILE* fa2;

bool tableswitch;
bool listswitch;
char ch;//note:用于存储当前读取的字符


enum symbol sym; // note 全局变量，存储当前读取的单词的类名
char id[al + 1];// note 全局变量，储存当前读取的标识符的值
int  num; // note 全局变量，储存当前读取整数的值 

int cc, ll;//note:全局变量，cc和ll用于文件读取的字符计数和行号计数，cx用于指令计数
int cx;
char line[81];
char a[al + 1];//note:全局变量，用于存储临时标识符。
struct instruction code[cxmax];

/* note 
word：保留字表，存放所有保留字的信息，如if、while
wsym：和 word 配套，wordsymbol 保留字类名 
*/
char word[norw][al];
enum symbol wsym[norw];

enum symbol ssym[256];// note: 单字符单词的类名

char mnemonic[fctnum][5];
bool declbegsys[symnum];
bool statbegsys[symnum];
bool facbegsys[symnum];
/*------------------------------*/

//note:定义了名字表中每个条目的结构，包括名字、类型、数值、层次、地址和所需数据区空间。
struct tablestruct
{
	char name[al];                            /*名字*/
	enum object kind;                         /*类型：const，var，array or procedure*/
	int val;                                  /*数值，仅const使用*/
	int level;                                /*所处层，仅const不使用*/
	int adr;                                  /*地址，仅const不使用*/
	int size;                                 /*需要分配的数据区空间，仅procedure使用*/
};
struct tablestruct table[txmax];             /*名字表*/
FILE* fin;
FILE* fout;
char fname[al];
int err;                                       /*错误计数器*/
/*当函数中会发生fatal error时，返回－1告知调用它的函数，最终退出程序*/
#define getsymdo                              if(-1==getsym())return -1
#define getchdo                               if(-1==getch())return -1
#define testdo(a,b,c)                         if(-1==test(a,b,c))return -1
#define gendo(a,b,c)                          if(-1==gen(a,b,c))return -1
#define expressiondo(a,b,c)                   if(-1==expression(a,b,c))return -1
#define factordo(a,b,c)                       if(-1==factor(a,b,c))return -1
#define termdo(a,b,c)                         if(-1==term(a,b,c))return -1
#define conditiondo(a,b,c)                    if(-1==condition(a,b,c))return -1
#define statementdo(a,b,c)                    if(-1==statement(a,b,c))return -1
#define constdeclarationdo(a,b,c)             if(-1==constdeclaration(a,b,c))return -1
#define vardeclarationdo(a,b,c)               if(-1==vardeclaration(a,b,c))return -1
void error(int n);
// 获取单词和字符的函数
int getsym();
int getch();

void init();
int gen(enum fct x, int y, int z);//生成虚拟机代码的函数
int test(bool* s1, bool* s2, int n);
int inset(int e, bool* s);
int addset(bool* sr, bool* s1, bool* s2, int n);
int subset(bool* sr, bool* s1, bool* s2, int n);
int mulset(bool* sr, bool* s1, bool* s2, int n);
int block(int lev, int tx, bool* fsys);
void interpret();
int factor(bool* fsys, int* ptx, int lev);
int term(bool* fsys, int* ptx, int lev);
int condition(bool* fsys, int* ptx, int lev);
int expression(bool* fsys, int* ptx, int lev);
int statement(bool* fsys, int* ptx, int lev);
void listcode(int cx0);
int vardeclaration(int* ptx, int lev, int* pdx);
int constdeclaration(int* ptx, int lev, int* pdx);
int position(char* idt, int tx);
void enter(enum object k, int* ptx, int lev, int* pdx);
int base(int l, int* s, int b);














