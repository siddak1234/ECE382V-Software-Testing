package ee360t.pset4;

import static org.junit.Assert.*;
import java.util.TreeSet;
import java.util.Set;
import org.junit.Test;

public class GraphTester {
  // tests for method "addEdge" in class "Graph"
  @Test public void testAddEdge0() {
    Graph g = new Graph(2);
    g.addEdge(0, 1);
    System.out.println(g);
    assertEquals(g.toString(), "numNodes: 2\nedges: [[false, true], [false, false]]");
  }

  // your tests for method "addEdge" in class "Graph" go here

  // provide at least 4 test methods such that together they provide full statement
  // coverage of your implementation of addEdge and any helper methods;
  // each test method has at least 1 invocation of addEdge;
  // each test method creates exactly 1 graph
  // each test method creates a unique graph w.r.t. "equals" method
  // each test method has at least 1 test assertion;
  // each test assertion correctly characterizes expected behavior with respect to the spec;

  // ...

  // tests for a self loop in single node graph
  @Test public void testAddEdge1() {
    Graph g = new Graph(1);
    g.addEdge(0, 0);
    assertEquals(g.toString(), "numNodes: 1\nedges: [[true]]");
  }
  
  // tests for multiple edges from one source node
  @Test public void testAddEdge2() {
    Graph g = new Graph(3);
    g.addEdge(2, 0);
    g.addEdge(2, 1);
    assertEquals(g.toString(),
        "numNodes: 3\nedges: [[false, false, false], [false, false, false], [true, true, false]]");
  }
  
  // tests for invalid edge gives exception
  @Test public void testAddEdge3() {
    Graph g = new Graph(2);
    boolean threw = false;
    try {
      g.addEdge(-1, 0);
    } catch (IllegalArgumentException e) {
      threw = true;
    }
    assertTrue(threw);
  }

  // tests for one edge from source to target
  @Test public void testAddEdge4() {
    Graph g = new Graph(3);
    g.addEdge(0, 2);
    assertEquals(g.toString(),
        "numNodes: 3\nedges: [[false, false, true], [false, false, false], [false, false, false]]");
  }

  // tests for method "reachable" in class "Graph"
  @Test public void testReachable0() {
    Graph g = new Graph(1);
    Set<Integer> nodes = new TreeSet<Integer>();
    nodes.add(0);
    assertTrue(g.reachable(nodes, nodes));
  }

  // your tests for method "reachable" in class "Graph" go here
  // provide at least 6 test methods such that together they provide full statement
  // coverage of your implementation of reachable and any helper methods;
  // each test method has at least 1 invocation of reachable;
  // each test method has at least 1 test assertion;
  // at least 2 test methods have at least 1 invocation of addEdge;
  // ...

  // tests for no edges in graph
  @Test public void testReachable1() {
    Graph g = new Graph(3);
    Set<Integer> sources = new TreeSet<Integer>();
    Set<Integer> targets = new TreeSet<Integer>();
    sources.add(0);
    targets.add(2);
    assertFalse(g.reachable(sources, targets));
  }

  // multple edges from source to target
  @Test public void testReachable2() {
    Graph g = new Graph(3);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    Set<Integer> sources = new TreeSet<Integer>();
    Set<Integer> targets = new TreeSet<Integer>();
    sources.add(0);
    targets.add(2);
    assertTrue(g.reachable(sources, targets));
  }

  // tests with source disconnected from target
  @Test public void testReachable3() {
    Graph g = new Graph(3);
    g.addEdge(0, 1);
    Set<Integer> sources = new TreeSet<Integer>();
    Set<Integer> targets = new TreeSet<Integer>();
    sources.add(2);
    targets.add(1);
    assertFalse(g.reachable(sources, targets));
  }

  // tests with many sources but only one reaches target
  @Test public void testReachable4() {
    Graph g = new Graph(4);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    Set<Integer> sources = new TreeSet<Integer>();
    Set<Integer> targets = new TreeSet<Integer>();
    sources.add(0);
    sources.add(3);
    targets.add(2);
    assertTrue(g.reachable(sources, targets));
  }

  // tests with target out of bounds
  @Test public void testReachable5() {
    Graph g = new Graph(2);
    Set<Integer> sources = new TreeSet<Integer>();
    Set<Integer> targets = new TreeSet<Integer>();
    sources.add(0);
    targets.add(2);
    assertFalse(g.reachable(sources, targets));
  }

  // tests with no edges but target and source are valid
  @Test public void testReachable6() {
    Graph g = new Graph(2);
    Set<Integer> sources = new TreeSet<Integer>();
    Set<Integer> targets = new TreeSet<Integer>();
    sources.add(0);
    targets.add(1);
    assertFalse(g.reachable(sources, targets));
  }
}

