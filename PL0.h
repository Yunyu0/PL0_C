#pragma once
/*PL/0 ����ϵͳC�汾ͷ�ļ� pl0.h*/

// note������PL/0�������ܹ�ʶ��ı���������Ϊ14
# define norw 14                 /*�ؼ��ָ���*/
# define txmax 100               /*���ֱ�����*/
# define nmax  14                /*number�����λ��*/
# define al 10                   /*���ŵ���󳤶�*/
# define amax 2047               /*��ַ�Ͻ�*/
# define levmax 3                /*����������Ƕ����������[0��lexmax]*/
# define cxmax 200               /*���������������*/
/*����*/
/* note��
enum symbol�����������з��ŵ�������������
nul���գ�����ʶ�ĵ��ʣ� 
�����֡�������������һ��һ��
��ʶ����ident�������б�ʶ����һ��
��ʶ����ǣ��޷���������
����������һ��number 
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

#define symnum 35 // note��symnum���������ܹ�ʶ������з��ŵ�����
/*-------------*/
// note�����������ֱ��ж�������ͣ����������������͹���
enum object {
	constant,
	variable,
	procedur,
};
/*--------------*/

// note:�������������ָ��������䳣�����������㡢���ء��洢�������ӹ��̵�
enum fct {
	lit, opr, lod, sto, cal, inte, jmp, jpc,
};
#define fctnum 8
/*--------------*/

//note�����������������Ľṹ������ָ�����͡���κ͵�ַ��
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
char ch;//note:���ڴ洢��ǰ��ȡ���ַ�


enum symbol sym; // note ȫ�ֱ������洢��ǰ��ȡ�ĵ��ʵ�����
char id[al + 1];// note ȫ�ֱ��������浱ǰ��ȡ�ı�ʶ����ֵ
int  num; // note ȫ�ֱ��������浱ǰ��ȡ������ֵ 

int cc, ll;//note:ȫ�ֱ�����cc��ll�����ļ���ȡ���ַ��������кż�����cx����ָ�����
int cx;
char line[81];
char a[al + 1];//note:ȫ�ֱ��������ڴ洢��ʱ��ʶ����
struct instruction code[cxmax];

/* note 
word�������ֱ�������б����ֵ���Ϣ����if��while
wsym���� word ���ף�wordsymbol ���������� 
*/
char word[norw][al];
enum symbol wsym[norw];

enum symbol ssym[256];// note: ���ַ����ʵ�����

char mnemonic[fctnum][5];
bool declbegsys[symnum];
bool statbegsys[symnum];
bool facbegsys[symnum];
/*------------------------------*/

//note:���������ֱ���ÿ����Ŀ�Ľṹ���������֡����͡���ֵ����Ρ���ַ�������������ռ䡣
struct tablestruct
{
	char name[al];                            /*����*/
	enum object kind;                         /*���ͣ�const��var��array or procedure*/
	int val;                                  /*��ֵ����constʹ��*/
	int level;                                /*�����㣬��const��ʹ��*/
	int adr;                                  /*��ַ����const��ʹ��*/
	int size;                                 /*��Ҫ������������ռ䣬��procedureʹ��*/
};
struct tablestruct table[txmax];             /*���ֱ�*/
FILE* fin;
FILE* fout;
char fname[al];
int err;                                       /*���������*/
/*�������лᷢ��fatal errorʱ�����أ�1��֪�������ĺ����������˳�����*/
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
// ��ȡ���ʺ��ַ��ĺ���
int getsym();
int getch();

void init();
int gen(enum fct x, int y, int z);//�������������ĺ���
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














