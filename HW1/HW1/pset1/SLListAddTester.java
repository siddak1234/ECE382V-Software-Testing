// SLListAddTester.java
// Add package and imports
package pset1;

import static org.junit.Assert.*;
import org.junit.Test;

// Add tester for add in class
public class SLListAddTester {
  // test 0
  @Test public void test0() {
    SLList l = new SLList();
    // assert confirms acyclic
    assertTrue(l.repOk());
    l.add(true);
    // assert confirms structure after adding element
    assertTrue(l.header != null);
    assertTrue(l.header.elem == true);
    assertTrue(l.header.next == null);
  }
  // test 1
  @Test public void test1() {
    SLList l = new SLList();
    // check to see if list is valid/acyclic before any add, after first add, and after second add
    assertTrue(l.repOk());
    l.add(true);
    assertTrue(l.repOk());
    l.add(false);
    assertTrue(l.repOk());
    // Check node to make sure elements have valid elem, next, and header of list
    assertTrue(l.header != null);
    assertTrue(l.header.elem == false);
    assertTrue(l.header.next != null);
    assertTrue(l.header.next.elem == true);
    assertTrue(l.header.next.next == null);
  }
}
