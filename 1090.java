import java.math.BigInteger;
import java.util.Scanner;

public class Main {
	static final BigInteger ZERO = BigInteger.ZERO;
	static final BigInteger ONE = BigInteger.ONE;
	static final BigInteger TWO = ONE.add(ONE);

	static int n;
	static int[] o;
	static BigInteger ans;
	static BigInteger[] f;

	static void clean(int p) {
		int i = p - 1;
		while (i >= 0 && o[i] == 0)
			i--;
		if (i >= 0) {
			// clean downwards.
			int j = i - 1;
			while (j >= 0 && o[j] == 0)
				j--;
			if (j >= 0)
				clean(j);
			while (i < p - 1) {
			  ans = ans.add(ONE);
			  ans = ans.add(f[i]);
			  i++;
			}
			ans = ans.add(ONE);
			ans = ans.add(f[p - 1]);
		} else {
			ans = ans.add(f[p]);
		}
	}

	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		n = in.nextInt();
		// Grab all ones' indices.
		o = new int[n];
		for (int i = 0; i < n; i++)
			o[i] = in.nextInt();
		// Precompute.
		// f[0]~f[i-1] = 0, #moves to flip f[i].
		f = new BigInteger[n];
		f[0] = BigInteger.ONE;
		for (int i = 1; i < n; i++)
			f[i] = f[i - 1].multiply(TWO).add(ONE);
		// Clear all ones.
		ans = ZERO;
		int i = n - 1;
		while (i >= 0 && o[i] == 0)
			i--;
		if (i >= 0)
			clean(i);
		System.out.println(ans);
	}
}
