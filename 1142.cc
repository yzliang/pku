// 2010-08-06 01:03:22
#include <iostream>
using namespace std;

int n;
int pNum;
int p[10000], d[10000];

int calcDigitSum(int n)
{
	int ret = 0;
	for (; n > 0; n /= 10)
		ret += n % 10;
	return ret;
}

void calcPrimes()
{
	int i, j;
	bool isPrime[65536];

	for (i = 0; i < 65536; i++)
		isPrime[i] = true;
	pNum = 0;
	for (i = 2; i < 65536; i++)
		if (isPrime[i])
		{
			p[pNum] = i;
			d[pNum++] = calcDigitSum(i);
			j = i + i;
			for (; j < 65536; j += i)
				isPrime[j] = false;
		}
}

bool isSmithNumber(int n)
{
	int digitSum = calcDigitSum(n);
	int primeDigitSum = 0;
	int i;
	int value = n;
	for (i = 0; i < pNum && value > 1 && primeDigitSum < digitSum; i++)
	{
		if (n == p[i]) // prime test
			return false;
		while (value % p[i] == 0)
		{
			primeDigitSum += d[i];
			value /= p[i];
		}
	}
	if (value == n)
		return false;
	if (value > 1)
		primeDigitSum += calcDigitSum(value);
	return primeDigitSum == digitSum;
}

int main()
{
	calcPrimes();
	while (true)
	{
		cin >> n;
		if (n == 0)
			break;
		int ans = n + 1;
		while (!isSmithNumber(ans))
			ans++;
		cout << ans << endl;
	}
	return 0;
}
