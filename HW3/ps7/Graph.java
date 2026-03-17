package ee360t.pset7;

import java.util.Arrays;

public class Graph {
  private int numNodes; // number of nodes in the graph
  private boolean[][] edges;
  // edges[i][j] is true if and only if there is an edge from node i to node j

  // class invariant: edges != null; edges is a square matrix;
  //                  numNodes >= 0; numNodes is number of rows in edges

  public Graph(int size) {
    if (size < 0) throw new IllegalArgumentException("size must be non-negative");
    numNodes = size;
    edges = new boolean[size][size];
  }

  @Override
  public String toString() {
    return "numNodes: " + numNodes + "; " + "edges: " + Arrays.deepToString(edges);
  }

  @Override
  public boolean equals(Object o) {
    if (o == null || o.getClass() != ee360t.pset7.Graph.class) return false;
    return toString().equals(o.toString());
  }

  @Override
  public int hashCode() {
    // 1.1: Implementing hashCode
    return toString().hashCode();
  }

  public void addEdge(int from, int to) {
    // postcondition: adds a directed edge "from" -> "to" to this graph
    edges[from][to] = true;
  }

  public int numEdges() {
    // 1.2: Implementing numEdges
    // post: returns the number of edges in this
    int count = 0;
    for (int i = 0; i < numNodes; i++) {
      for (int j = 0; j < numNodes; j++) {
        if (edges[i][j]) count++;
      }
    }
    return count;
  }

  public boolean hasExactlyOneEdge() {
    // 1.3: Implementing hasExactlyOneEdge
    // post: returns true if and only if there is exactly one edge in this
    int count = 0;
    for (int i = 0; i < numNodes; i++) {
      for (int j = 0; j < numNodes; j++) {
        if (edges[i][j]) {
          count++;
          if (count > 1) return false;
        }
      }
    }
    return count == 1;
  }

  public boolean isReflexive() {
    // 1.4: Implementing isReflexive
    // Every node must have an edge to itself.
    // post: returns true if this represents a reflexive relation
    for (int i = 0; i < numNodes; i++) {
      if (!edges[i][i]) return false;
    }
    return true;
  }

  public boolean isSymmetric() {
    // 1.5: Implementing isSymmetric
    // edge from a to b should imply edge from b to a for all nodes.
    // post: returns true if and only if this represents a symmetric relation
    for (int i = 0; i < numNodes; i++) {
      for (int j = 0; j < numNodes; j++) {
        if (edges[i][j] != edges[j][i]) return false;
      }
    }
    return true;
  }

  public boolean isTransitive() {
    // 1.6: Implementing isTransitive
    // if edge from a to b and edge b to c, then a to c must exist for all
    // post: returns true if and only if this represents a transitive relation
    for (int i = 0; i < numNodes; i++) {
      for (int j = 0; j < numNodes; j++) {
        if (!edges[i][j]) continue;
        for (int k = 0; k < numNodes; k++) {
          if (edges[j][k] && !edges[i][k]) return false;
        }
      }
    }
    return true;
  }
}
