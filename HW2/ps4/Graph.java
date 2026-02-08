package ee360t.pset4;

import java.util.ArrayDeque;
import java.util.Arrays;
import java.util.Set;

public class Graph {
  private int numNodes; // number of nodes in the graph
  private boolean[][] edges;
  // edges[i][j] is true if and only if there is an edge from node i to node j
  // class invariant: edges != null; edges is a square matrix;
  // numNodes >= 0; numNodes is number of rows in edges

  // size cannot be negativs, edges is 2d matrix
  public Graph(int size) {
    if (size < 0) throw new IllegalArgumentException();
    numNodes = size;
    edges = new boolean[size][size];
  }

  @Override
  public String toString() {
    return "numNodes: " + numNodes + "\n" + "edges: " + Arrays.deepToString(edges);
  }

  @Override
  public boolean equals(Object o) {
    if (o.getClass() != Graph.class) return false;
    return toString().equals(o.toString());
  }

  public void addEdge(int from, int to) {
    // postcondition: adds a directed edge "from" -> "to" to this graph
    // Invalidates from and to if not in range
    if (from < 0 || from >= numNodes || to < 0 || to >= numNodes) {
      throw new IllegalArgumentException();
    }
    edges[from][to] = true;
  }

  public boolean reachable(Set<Integer> sources, Set<Integer> targets) {
    if (sources == null || targets == null) throw new IllegalArgumentException();
    // postcondition: returns true if (1) "sources" does not contain an illegal node,
    // (2) "targets" does not contain an illegal node, and
    // (3) for each node "m" in set "targets", there is some
    // node "n" in set "sources" such that there is a directed
    // path that starts at "n" and ends at "m" in "this"; and
    // false otherwise

    // boolean array tracks visited nodes
    // array deque is nodes to visit
    boolean[] visited = new boolean[numNodes];
    ArrayDeque<Integer> worklist = new ArrayDeque<>();

    // add source node to worklist and mark as visited
    for (Integer s : sources) {
      if (s == null || s < 0 || s >= numNodes) return false;
      if (!visited[s]) {
        visited[s] = true;
        worklist.addLast(s);
      }
    }

    // find all reachable nodes from source with BFS
    while (!worklist.isEmpty()) {
      int current = worklist.removeFirst();
      for (int next = 0; next < numNodes; next++) {
        if (edges[current][next] && !visited[next]) {
          visited[next] = true;
          worklist.addLast(next);
        }
      }
    }

    // check if visited
    for (Integer t : targets) {
      if (t == null || t < 0 || t >= numNodes) return false;
      if (!visited[t]) return false;
    }

    return true;
  }
}
