#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

class Solution{
public:

};

int match1(char *t, char *p)
{
	int m = strlen(p), j = 0;
	int n = strlen(t), i = 0;
	
	while (j < m && i < n)
	{
		if (p[j] == t[i])
		{
			++i;
			++j;
		}
		else
		{
			i  = i - j + 1;
			j = 0;
		}
	}

	return i - j;
}
int match2(char *t, char *p)
{
	int n = strlen(t), i;
	int m = strlen(p), j = 0;
	
	for (i = 0; i < n - m + 1; ++i)
	{
		for (j = 0; j < m; ++j)
		{
			if (p[j] != t[i+j]) break;
		}
		if (m <= j) break;
	}
	return i;
}

int main(void)
{
	char *t = "hello world yalewoo rrresf 2333";
	char *p = "yalewoo";

	cout << match1(t, p);
	cout << match2(t, p);
	return 0;
}