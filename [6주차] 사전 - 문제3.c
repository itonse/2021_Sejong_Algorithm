#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>

int main() {
	int a, b, m, cnt, i;
	char ch;

	scanf("%d %d %d", &a, &b, &cnt);  // Á¶°Ç a < b
	getchar();

	for (i = 0; i < cnt; i++) {
		m = (a + b) / 2;
		scanf("%c", &ch);

		if (ch == 'Y')
			a = m + 1;
		if (ch == 'N')
			b = m;
	}

	printf("%d", a);
	return 0;
}