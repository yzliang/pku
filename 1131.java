import java.math.BigDecimal;
import java.util.Scanner;

public class Main {
  public static void main(String[] args) {
    final BigDecimal FACTOR = new BigDecimal("0.125");
    Scanner sc = new Scanner(System.in);
    String line;
    while (sc.hasNextLine()) {
      line = sc.nextLine();
      BigDecimal figure = BigDecimal.ZERO;
      for (int i = line.length() - 1; i >= 2; i--) {
        figure = figure.add(new BigDecimal(line.charAt(i) - '0'));
        figure = figure.multiply(FACTOR);
      }
      System.out.printf("%s [8] = %s [10]\n", line, figure);
    }
  }
}
