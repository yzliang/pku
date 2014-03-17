import java.math.BigInteger;
import java.util.Arrays;
import java.util.Scanner;

public class Main {
  
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    int n = in.nextInt();
    int m = in.nextInt();
    // Get prime factors (less than 10).
    int[] factors = getFactors(m);
    int numStates = 1 << factors.length;
    // Euler function based transitions.
    BigInteger[][] base = new BigInteger[numStates][numStates];
    for (int i = 0; i < numStates; i++) {
      for (int j = 0; j <= i; j++) {
        if ((i | j) != i) continue;
        int value = m;
        for (int k = 0; k < factors.length; k++) {
          if ((i & (1 << k)) != 0) {
            if ((j & (1 << k)) == 0)
              value = value / factors[k] * (factors[k] - 1);
            else
              value /= factors[k];
          }
        }
        base[i][j] = BigInteger.valueOf(value);
      }
    }
    // DP.
    BigInteger[][] f = new BigInteger[n][numStates];
    for (int i = 0; i < numStates; i++)
      f[0][i] = base[numStates - 1][i];
    for (int i = 1; i < n; i++)
      for (int j = 0; j < numStates; j++)
        f[i][j] = BigInteger.ZERO;
    for (int i = 0; i < n - 1; i++) {
      for (int j = 0; j < numStates; j++) {
        for (int k = 0; k <= j; k++) {
          // k should be a subset of j.
          if ((j | k) != j) continue;
          f[i + 1][k] = f[i + 1][k].add(f[i][j].multiply(base[j][k]));
        }
      }
    }
    System.out.println(f[n - 1][0]);
  }
  
  static int[] getFactors(int x) {
    int[] factors = new int[10];
    int total = 0;
    for (int i = 2; x > 1; i++) {
      if (x % i == 0) {
        factors[total++] = i;
        for (x /= i; x % i == 0; x /= i);
      }
    }
    return Arrays.copyOf(factors, total);
  }
}