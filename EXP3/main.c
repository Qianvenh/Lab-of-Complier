#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "WordsSolve.h"
#include "ReverseNotion.h"

int getAnswer() {
	if (!checkOutp())
		return 0;
	creatReverse();
	return 1;
}

int main()
{
	// 文件流读入
	/*
	FILE *fp = fopen("./test.txt", "rt");
	while (!feof(fp))
		funcfile(fp);
	*/

	// 字符流读入
	char c[200] = "1+((2-3)*4";
	char *p = c;
	while (*p)
		funcstr(&p);
	interrupt(' '); // 将buf清空
	int succ = getAnswer();
	printf("\"%s\" is a %s sentence.\n\n", c, succ ? "right" : "wrong");
	if (succ) {
		puts("The Polish Reverse Notion is here:");
		for (int i = 0; i < rt; i++)
			printf("%s ", polishRev[i]);
		puts("");
	}
	return 0;
}
