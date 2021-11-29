#if !defined(REVERSENOTION_H)
#define REVERSENOTION_H

#include "myStructs.h"

int checkOutp() {
	for (int i = 0; i < rt; i++) {
		Splited *p = &outp[i];
		if (p->type == 3)
			continue;
		if (strlen(p->str) > 1)
			return 0;
		if (p->type == 4 && p->str[0] != '=')
			continue;
		if (p->str[0] == '(' || p->str[0] == ')')
			continue;
		return 0;
	}
	return 1;
}

int operVal(char x) {
	if (x == '+' || x == '-')
		return 1;
	if (x == '*' || x == '/')
		return 2;
	return 3;
}

int operCmp(Splited *a, Splited *b) {
	return operVal(a->str[0]) < operVal(b->str[0]);
}

void creatReverse() {
	for (int i = 0; i < rt; i++) {
		Splited *p = &outp[i];
		if (p->type == 3) {
			strcpy(polishRev[pr++], p->str);
		} else if (p->type == 4 || p->str[0] == '(') {
			while (~tt && stk[tt].str[0] != '(' && operCmp(p, &stk[tt]))
				stkPop();
			strcpy(stk[++tt].str, p->str);
			stk[tt].type = p->type;
		} else {
			while (~tt && stk[tt].str[0] != '(')
				stkPop();
			tt--;
			if (~tt && stk[tt].str[0] != '(')
				stkPop();
		}
	}
	while (~tt)
		stkPop();
}

#endif // REVERSENOTION_H
