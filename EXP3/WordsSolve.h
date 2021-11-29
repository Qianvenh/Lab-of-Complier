#if !defined(WORDSSOLVE_H)
#define WORDSSOLVE_H

#include "myStructs.h"

int isLetter(char c) // 判断是否是字母
{
	return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z';
}
int isDigit(char c) // 判断是否是数字
{
	return c >= '0' && c <= '9';
}
int isStop(char c) // 判断是否是制表符
{
	return c == ' ' || c == '\t' || c == '\r' || c == '\n';
}
int isBraket(char c) // 判断是否是括号或者分隔符
{
	return c == '(' || c == ')' || c == '[' || c == ']' ||
		   c == '{' || c == '}' || c == ',' || c == ';';
}
int isOperator(char c) // 判断是否是操作符
{
	return c == '+' || c == '-' || c == '*' || c == '/' ||
		   c == '=' || c == '<' || c == '>';
}
int kindWord() // 判断一下当前buf数组中存储的是什么类型的单词
{
	for (int i = 0; i < 8; i++)
		if (!strcmp(buf, reserve[i]))
			return 1;
	for (int i = 0; i < idx; i++)
		if (buf[i] < '0' || buf[i] > '9')
			return 2;
	return 3;
}

int getType(char c) // 判断char c是什么类型的字符
{
	if (!c)
		return kindWord();
	if (isOperator(c))
		return 4;
	if (isBraket(c))
		return 5;
	return 0;
}

// 应该先阅读函数processChar再阅读这里
void interrupt(char c) // 处理中断。c一般为各单词之间的中断符
{	
	// 本函数主要插入buf内的单词以及字符c进入Result outp[N]
	if (idx) // 如果buf为空则放弃此次插入
	{
		buf[idx] = 0;
		strcpy(outp[rt].str, buf);
		outp[rt++].type = getType(0);
	}
	idx = 0; // 清空buf
	if (!isStop(c)) // 如果字符c是制表符，则不存储字符c
	{
		outp[rt].str[0] = c;
		outp[rt++].type = getType(c);
	}
}

int processChar(char c) // 从数据流读到的每一个字符都需要调用此函数处理
{	
	// 如果新读入的c是字母、数字或者下划线，则认为c是buf缓冲区正在存储单词的一个字符，因此加入buf中
	if (isLetter(c) || isDigit(c) || c == '_') 
	{
		buf[idx++] = c;
		return 1; // 返回true,可以继续循环
	}
	// 当c不是字母、数字或者下划线时，则认为c是一个中断符
	// 此时读到了中断符c，意味着c与buf里暂存的字母已经不属于同一个单词，此时可以分别存储一下buf和c
	interrupt(c); // 处理中断（即存储buf和c）
	return 0; // 返回false，退出循环 
}

void funcfile(FILE *fp) // 从文件流里读取**一个**单词存入Result outp[N]
{
	char c;
	while (c = fgetc(fp), c != EOF) // 从文件指针中读取字符，fget会自动移指针到下一位，读到文件尾则不继续循环
		if (!processChar(c))
			break;
}

void funcstr(char **sp) // 从字符流里读取**一个**单词存入Result outp[N]
{
	char c;
	while (c = **sp, *sp = *sp + 1, c) // 从sp中读取字符，并将sp移动到下一个位置，c为字符尾‘\0'则不继续循环
		if (!processChar(c))
			break;
}

#endif
