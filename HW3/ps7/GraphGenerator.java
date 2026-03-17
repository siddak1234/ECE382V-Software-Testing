package ee360t.pset7;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.HashSet;
import java.util.Set;

public class GraphGenerator {
  public static Set<Graph> generateAllGraphs(int num) {
    // 2.1: Generating all graphs with given size
    // pre: num >= 0
    // post: returns a set of all graphs that have num nodes
    if (num < 0) throw new IllegalArgumentException("num must be non-negative");

    Set<Graph> allGraphs = new HashSet<>();
    boolean[] encoding = new boolean[num * num];
    generateAllGraphsFromEncoding(num, 0, encoding, allGraphs);
    return allGraphs;
  }

  public static Set<Graph> generateAllGraphs(int num, String property) {
    // pre: num >= 0 and
    //      property is the name of a valid boolean method in class Graph
    // post: returns a set of all graphs (with num nodes) that represent binary
    //       relations with the given property

    return generateAllGraphs(num, new String[] {property});
  }

  public static Set<Graph> generateAllGraphs(int num, String[] properties) {
    // 2.2: Generating all graphs with given size and properties
    // pre: num >= 0 and
    //      each element of properties is the name of a valid boolean method in class Graph
    // post: returns a set of all graphs (with num nodes) that represent binary
    //       relations with all the given properties
    if (num < 0) throw new IllegalArgumentException("num must be non-negative");
    if (properties == null) throw new IllegalArgumentException("properties must not be null");

    Set<Graph> allGraphs = generateAllGraphs(num);
    Set<Graph> filteredGraphs = new HashSet<>();

    for (Graph graph : allGraphs) {
      boolean satisfiesAll = true;

      for (String property : properties) {
        try {
          Method method = Graph.class.getMethod(property);
          Object result = method.invoke(graph);
          if (!(result instanceof Boolean) || !((Boolean) result)) {
            satisfiesAll = false;
            break;
          }
        } catch (NoSuchMethodException
            | IllegalAccessException
            | InvocationTargetException
            | SecurityException e) {
          throw new IllegalArgumentException("invalid property method: " + property, e);
        }
      }

      if (satisfiesAll) filteredGraphs.add(graph);
    }

    return filteredGraphs;
  }

  private static void generateAllGraphsFromEncoding(
      int num, int index, boolean[] encoding, Set<Graph> allGraphs) {
    if (index == encoding.length) {
      Graph graph = new Graph(num);
      for (int pos = 0; pos < encoding.length; pos++) {
        if (encoding[pos]) {
          int from = pos / num;
          int to = pos % num;
          graph.addEdge(from, to);
        }
      }
      allGraphs.add(graph);
      return;
    }

    encoding[index] = false;
    generateAllGraphsFromEncoding(num, index + 1, encoding, allGraphs);

    encoding[index] = true;
    generateAllGraphsFromEncoding(num, index + 1, encoding, allGraphs);
  }
}
