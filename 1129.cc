// 2009-02-27 22:14:00
#include <iostream>
using namespace std;

int n;
bool adj[26][26];
int ans;
int channel[26];

bool ReadData()
{
	int i, j;
	char st[50];

	cin >> n;
	cin.getline(st, 50);
	if (n == 0)
		return false;
	memset(adj, false, sizeof(adj));
	for (i = 0; i < n; i++)
	{
		cin.getline(st, 50);
		for (j = 2; j < strlen(st); j++)
		{
			adj[i][st[j] - 'A'] = true;
			adj[st[j] - 'A'][i] = true;
		}
	}
	return true;
}

void SetChannel(int p, int tot)
{
	if (tot >= ans)
		return;
	else if (p == n)
		ans = tot;
	else
	{
		for (int i = 0; i < tot; i++)
		{
			int j;
			for (j = 0; j < p; j++)
				if (adj[j][p] && channel[j] == i)
					break;
			if (j == p)
			{
				channel[p] = channel[i];
				SetChannel(p + 1, tot);
			}
		}
		channel[p] = tot;
		SetChannel(p + 1, tot + 1);
	}
}

void Process()
{
	ans = n;
	SetChannel(0, 0);
	if (ans == 1)
		cout << "1 channel needed.\n";
	else
		cout << ans << " channels needed.\n";
}

int main()
{
	while (ReadData())
		Process();
	return 0;
}
