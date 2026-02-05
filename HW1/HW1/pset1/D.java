// D.java
// declare package
package pset1;
// create class d from c
public class D extends C {
  // initialize new variable and object constructor
  int g;
  public D(int f, int g) {
    super(f);
    this.g = g;
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
    D d = (D) o;
    return f == d.f && g == d.g;
  }
  // both f and g used in hashcode, both must be equal for same hash
  @Override
  public int hashCode() {
    int result = 31 + f;
    result = 31 * result + g;
    return result;
  }
}
