#include <stdio.h>
#include <string.h>
#include <malloc.h>

int * createBC(char *p);
int * createGS(char *p);
int * createSS(char *p);
int bmBc(char *p, char *t);
int bmGs(char *p, char *t);


int main(void)
{
	char *t = "Hello world yalewhj yalewoo com";
	char *p = "yale";

	int n = bmGs(p, t);

	printf("%s\n", t+n);

	return 0;
}


int * createBC(char *p)
{
	int n = strlen(p);
	int *bc = (int *)malloc(sizeof(int) * 256);
	int i;
	for (i = 0; i < 256; ++i)
		bc[i] = -1;
	for (i = 0; i < n; ++i)
		bc[p[i]] = i;

	return bc;
}
int * createGS(char *p)
{
	int i, j;
	int *ss = createSS(p);
	int m = strlen(p);
	int *gs = (int *)malloc(sizeof(int)*m);
	for (i = 0; i < m; ++i)
		gs[i] = m;
	for (i = 0, j = m-1; j >= 0; --j)
	{
		if (j + 1 == ss[j])
			while (i < m-j-1)
				gs[i++] = m-j-1;
	}
	for (j = 0; j < m-1; ++j)
		gs[m-ss[j]-1] = m-j-1;

	free(ss);
	return gs;
}
int * createSS(char *p)
{
	int lo, hi;
	int m = strlen(p);
	int *ss = (int *)malloc(sizeof(int)*m);
	ss[m-1] = m;
	int j;

	for (lo = m-1, hi = m-1, j = lo-1; j >= 0; --j)
	{
		if ((lo < j) && (ss[m-hi+j-1] <= j-lo))
		{
			ss[j] = ss[m-hi+j-1];
		}
		else
		{
			hi = j;
			lo = lo < hi ? lo : hi;
			while ((0 <= lo) && (p[lo] == p[m-hi+lo-1]))
				--lo;
			ss[j] = hi - lo;
		}
	}
	return ss;
}
int bmBc(char *p, char *t)
{
	int m = strlen(p);
	int n = strlen(t);

	int *bc = createBC(p);
	int i = 0, j;

	while (i < n-m)
	{
		for (j = m-1; j >= 0; --j)
		{
			if (p[j] != t[i+j])
			{
				if (bc[t[i+j]] < j)
					i += j - bc[t[i+j]];
				else
					++i;
				break;
			}
		}
		if (j < 0)
			return i;
	}
	return -1;
}

int bmGs(char *p, char *t)
{
	int m = strlen(p);
	int n = strlen(t);

	int *bc = createBC(p);
	int *gs = createGS(p);
	int i = 0, j;

	while (i < n-m)
	{
		// j = m - 1;
		// while (p[j] == t[i+j])
		// 	if (0 > --j) break;

		// if (0 > j)
		// 	break;
		// else
		// 	i += gs[j] > j-bc[t[i+j]] ? gs[j] : j-bc[t[i+j]];


		for (j = m-1; j >= 0; --j)
		{
			if (p[j] != t[i+j])
			{
				i += gs[j] > j-bc[t[i+j]] ? gs[j] : j-bc[t[i+j]];
				break;
			}
		}
		if (j < 0)
			return i;
	}
	return -1;
}