import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Main {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    List<String> lines = readLines(sc);
    Map<String, Integer> query = parseLines(lines);
    while ((lines = readLines(sc)) != null) {
      Map<String, Integer> document = parseLines(lines);
      double score = 0;
      for (Map.Entry<String, Integer> entry : query.entrySet()) {
        Integer count = document.get(entry.getKey());
        if (count == null) {
          continue;
        }
        score += Math.sqrt(entry.getValue() * count);
      }
      System.out.format("%.2f\n", score);
    }
  }
  
  private static Pattern punct = Pattern.compile("[^a-z0-9]");
  
  private static Map<String, Integer> parseLines(List<String> lines) {
    Map<String, Integer> map = new HashMap<String, Integer>();
    for (String line : lines) {
      for (String token : line.split("\\s+")) {
        Matcher matcher = punct.matcher(token.toLowerCase());
        String term = matcher.replaceAll("");
        if (term.isEmpty()) {
          continue;
        }
        Integer count = map.get(term);
        if (count == null) {
          map.put(term, 1);
        } else {
          map.put(term, count + 1);
        }
      }
    }
    return map;
  }
  
  private static List<String> readLines(Scanner sc) {
    String line = sc.nextLine();
    if (line.equals("----------")) {
      return null;
    }
    List<String> lines = new ArrayList<String>();
    lines.add(line);
    while (true) {
      line = sc.nextLine();
      if (line.equals("----------")) {
        break;
      }
      lines.add(line);
    }
    return lines;
  }
}
