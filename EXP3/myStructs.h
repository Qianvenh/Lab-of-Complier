#if !defined(MYSTRUCT_H)
#define MYSTRUCT_H

#define N 100010
#define M 1010

char buf[M]; // 当作一个缓冲区，buf的内容最终将存入Result outp[N]里
int idx;			 // buf的当前长度

typedef struct
{
	int type; // type是单词的类型
	// 0：暂时无法区分，1：保留字，2：普通单词 3：数字 4：操作符 5：括号或分隔符
	char str[M]; // str是单词的内容
} Splited;
Splited outp[N]; // 所有被分割出来的词将被存储在其中
int rt;			 // outp的当前长度

char reserve[][20] = {
	"if", "int", "for", "while", "do",
	"return", "break", "continue"
}; // 存储保留字

char polishRev[M][M];
int pr;

Splited stk[M];
int tt = -1;
void stkPop() {
	strcpy(polishRev[pr++], stk[tt--].str);
}


#endif // MYSTRUCT_H
