#include <stdio.h>
#include <string.h>
#include <malloc.h>

int * createNextTable(char *p);
int kmp(char *p, char *t);

int main(void)
{
	char *t = "Hello world yalewhj yalewoo com";
	char *p = "yalewoo";

	int n = kmp(p, t);

	printf("%d%c%c%c%c\n", n, t[n], t[n+1], t[n+2],t[n+3]);

	return 0;
}

int * createNextTable(char *p)
{
	int i = 0;
	int len = strlen(p);
	int *next = (int *)malloc(len*sizeof(int));
	int t;
	memset(next, 0, len*sizeof(int));

	t = next[0] = -1;

	while (i < len)
	{
		if (t == -1 || p[i] == p[t])
		{
			next[++i] = ++t;
		}
		else
		{
			t = next[t];
		}
	}

	return next;
}
int kmp(char *p, char *t)
{
	int m = strlen(p);
	int n = strlen(t);

	int i = 0;
	int j = 0;

	int *next = createNextTable(p);

	while (i < n && j < m)
	{
		if (j == -1 || p[j] == t[i])
		{
			++i;
			++j;
		}
		else
		{
			j = next[j];
		}
	}

	free(next);
	return i-j;
}