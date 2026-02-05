// EqualsTester.java
// declare package and imports
package pset1;

import static org.junit.Assert.*;
import org.junit.Test;

// define class
public class EqualsTester {
  //P1: For any non-null reference value x, x.equals(null) should return false
  // test 0, returns false
  @Test public void t0() {
    assertFalse(new Object().equals(null));
  }
  // test 1, returns false
  @Test public void t1() {
    assertFalse(new C(1).equals(null));
  }
  // test 2, returns false
  @Test public void t2() {
    assertFalse(new D(1, 2).equals(null));
  }

  //P2: It is reflexive: for any non-null reference value x, x.equals(x) should return true
  // test 3, returns true
  @Test public void t3() {
    Object x = new Object();
    assertTrue(x.equals(x));
  }
  // test 4, returns true
  @Test public void t4() {
    C x = new C(1);
    assertTrue(x.equals(x));
  }
  // test 5, returns true
  @Test public void t5() {
    D x = new D(1, 2);
    assertTrue(x.equals(x));
  }

  //P3: It is symmetric: for any non-null reference values x and y, x.equals(y) should return true if
  //and only if y.equals(x) returns true
  // test 6, symmetric, object v object
  @Test public void t6() {
    Object x = new Object();
    Object y = new Object();
    assertTrue(x.equals(y) == y.equals(x));
  }
  // test 7, symmetric, object v C
  @Test public void t7() {
    Object x = new Object();
    C y = new C(1);
    assertTrue(x.equals(y) == y.equals(x));
  }
  // test 8, symmetric,  object v D
  @Test public void t8() {
    Object x = new Object();
    D y = new D(1, 2);
    assertTrue(x.equals(y) == y.equals(x));
  }
  // test 9, symmetric, C v object
  @Test public void t9() {
    C x = new C(1);
    Object y = new Object();
    assertTrue(x.equals(y) == y.equals(x));
  }
  // test 10, symmetric, C v C
  @Test public void t10() {
    C x = new C(1);
    C y = new C(2);
    assertTrue(x.equals(y) == y.equals(x));
  }
  // test 11, symmetric, C v D
  @Test public void t11() {
    C x = new C(1);
    D y = new D(2, 3);
    assertTrue(x.equals(y) == y.equals(x));
  }
  // test 12, symmetric, D v object
  @Test public void t12() {
    D x = new D(1, 2);
    Object y = new Object();
    assertTrue(x.equals(y) == y.equals(x));
  }
  // test 13, symmetric, D v C
  @Test public void t13() {
    D x = new D(1, 2);
    C y = new C(2);
    assertTrue(x.equals(y) == y.equals(x));
  }
  // test 14, symmetric, D v D
  @Test public void t14() {
    D x = new D(1, 2);
    D y = new D(3, 4);
    assertTrue(x.equals(y) == y.equals(x));
  }

}
