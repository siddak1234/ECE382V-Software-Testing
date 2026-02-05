// HashCodeTester.java
// declare package and imports
package pset1;

import static org.junit.Assert.*;
import org.junit.Test;

//create class HashCodeTester
public class HashCodeTester {
  //P5 : If two objects are equal according to the equals(Object) method, then calling the hashCode method on each of the two objects must produce the same integer result.
  // test 0, x = y, hashcode must be same, not equal
  // object vs object
  @Test public void t0() {
    Object x = new Object();
    Object y = new Object();
    assertTrue(!x.equals(y) || x.hashCode() == y.hashCode());
  }
  // test 1, x!=y, not equal
  // object vs class C
  @Test public void t1() {
    Object x = new Object();
    C y = new C(1);
    assertTrue(!x.equals(y) || x.hashCode() == y.hashCode());
  }
  // test 2, x!=y, not equal
  // object vs class D
  @Test public void t2() {
    Object x = new Object();
    D y = new D(1, 2);
    assertTrue(!x.equals(y) || x.hashCode() == y.hashCode());
  }
  // test 3, x!=y, not equal
  // class C vs object
  @Test public void t3() {
    C x = new C(1);
    Object y = new Object();
    assertTrue(!x.equals(y) || x.hashCode() == y.hashCode());
  }
  // test 4, x!=y, not equal
  // class C vs class C
  @Test public void t4() {
    C x = new C(1);
    C y = new C(2);
    assertTrue(!x.equals(y) || x.hashCode() == y.hashCode());
  }
  // test 5, x!=y, not equal
  // class C vs class D
  @Test public void t5() {
    C x = new C(1);
    D y = new D(2, 3);
    assertTrue(!x.equals(y) || x.hashCode() == y.hashCode());
  }
  // test 6, x!=y, not equal
  // class D vs object
  @Test public void t6() {
    D x = new D(1, 2);
    Object y = new Object();
    assertTrue(!x.equals(y) || x.hashCode() == y.hashCode());
  }
  // test 7, x!=y, not equal
  // class D vs class C
  @Test public void t7() {
    D x = new D(1, 2);
    C y = new C(2);
    assertTrue(!x.equals(y) || x.hashCode() == y.hashCode());
  }
  // test 8, x!=y, not equal
  // class D vs class D
  @Test public void t8() {
    D x = new D(1, 2);
    D y = new D(3, 4);
    assertTrue(!x.equals(y) || x.hashCode() == y.hashCode());
  }

  // Extra test cases with equal pairs
  // test 9, x = y, equal
  // class C vs class C
  @Test public void t9() {
    C x = new C(5);
    C y = new C(5);
    assertTrue(!x.equals(y) || x.hashCode() == y.hashCode());
  }
  // test 10, x = y, equal
  // class D vs class D
  @Test public void t10() {
    D x = new D(7, 9);
    D y = new D(7, 9);
    assertTrue(!x.equals(y) || x.hashCode() == y.hashCode());
  }
}
