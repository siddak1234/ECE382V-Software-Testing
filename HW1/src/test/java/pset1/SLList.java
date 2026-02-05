 // SLList.java 
 // Add package and imports
package pset1;

import java.util.HashSet;
import java.util.Set;

// Points to head node, first node in list
public class SLList {
  Node header;
// value in node, and pointer to next node
  static class Node {
    boolean elem;
    Node next;
  }
// true if acyclic, false otherwise
  boolean repOk() {
    Set<Node> visited = new HashSet<Node>();
    Node n = header;
    while (n != null) {
      if (!visited.add(n)) {
        return false;
      }
      n = n.next;
    }
    return true;
  }
// new node gets put in front of list
  void add(boolean e) {
    Node n = new Node();
    n.elem = e;
    n.next = header;
    header = n;
  }
}
