// SLListRepOkTester.java
// declare package and imports

package pset1;

import static org.junit.Assert.*;
import org.junit.Test;
import pset1.SLList.Node;

// Create test class for t0 to t5
public class SLListRepOkTester {
  // test 0
  // empty list
  @Test public void t0() {
    SLList l = new SLList();
    assertTrue(l.repOk());
  }

  // test 1
  // one node, acyclic
  @Test public void t1() {
    SLList l = new SLList();
    Node n = new Node();
    l.header = n;
    n.next = null;
    assertTrue(l.repOk());
  }
  // test 2
  // one node, cyclic
  @Test public void t2() {
    SLList l = new SLList();
    Node n = new Node();
    l.header = n;
    // create cycle
    n.next = n;
    assertFalse(l.repOk());
  }
  // test 3
  // two nodes, acyclic
  @Test public void t3() {
    SLList l = new SLList();
    Node n1 = new Node();
    Node n2 = new Node();
    l.header = n1;
    n1.next = n2;
    //acyclic
    n2.next = null;
    assertTrue(l.repOk());
  }
  // test 4
  // two nodes, cyclic, second node points to first
  @Test public void t4() {
    SLList l = new SLList();
    Node n1 = new Node();
    Node n2 = new Node();
    l.header = n1;
    n1.next = n2;
    // create cycle
    n2.next = n1;
    assertFalse(l.repOk());
  }
  // test 5
  // two nodes, cyclic, second node points to itself
  @Test public void t5() {
    SLList l = new SLList();
    Node n1 = new Node();
    Node n2 = new Node();
    l.header = n1;
    n1.next = n2;
    // create cycle to itself
    n2.next = n2;
    assertFalse(l.repOk());
  }
}
