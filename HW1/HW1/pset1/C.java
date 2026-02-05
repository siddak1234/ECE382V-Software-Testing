// C.java
// declare package
package pset1;

// create class c
public class C {
  // initialize variable and object constructor
  int f;
  public C(int f) {
    this.f = f;
  }
  @Override
  public boolean equals(Object o) {
    // if same return true
    if (this == o) {
      return true;
    }
    // if not same or null return false
    if (o == null || getClass() != o.getClass()) {
      return false;
    }
    // otherwise compare
    C c = (C) o;
    return f == c.f;
  }
  @Override
  public int hashCode() {
    // simple hash formula
    return 31 + f;
  }
}
