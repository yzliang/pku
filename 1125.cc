// 2008-12-15 13:24:03
#include <iostream>
using namespace std;

#define MAXINT 1000000

int n;
int d[101][101];

bool ReadData()
{
	int i, j, k, tot;

	cin >> n;
	if (n == 0)
		return false;
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
			d[i][j] = MAXINT;
	for (i = 1; i <= n; i++)
	{
		cin >> tot;
		for (j = 1; j <= tot; j++)
		{
			cin >> k;
			cin >> d[i][k];
		}
	}
	return true;
}

void Process()
{
	int i, j, k, start, ans;

	for (k = 1; k <= n; k++)
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				if (d[i][k] != MAXINT && d[k][j] != MAXINT && d[i][k] + d[k][j] < d[i][j])
					d[i][j] = d[i][k] + d[k][j];
	ans = MAXINT;
	for (i = 1; i <= n ; i++)
	{
		k = 0;
		for (j = 1; j <= n; j++)
			if (j != i && d[i][j] > k)
				k = d[i][j];
		if (k < ans)
		{
			start = i;
			ans = k;
		}
	}
	if (ans == MAXINT)
		cout << "disjoint\n";
	else
		cout << start << ' ' << ans << endl;
}

int main()
{
	while (ReadData())
		Process();
	return 0;
}
