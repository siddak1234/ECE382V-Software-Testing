package ee360t.pset7;

import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class GraphGenTester {
  @Test public void theoe0() {
    assertEquals(1, GraphGenerator.generateAllGraphs(1, "hasExactlyOneEdge").size());
  }

  @Test public void theoe1() {
    assertEquals(4, GraphGenerator.generateAllGraphs(2, "hasExactlyOneEdge").size());
  }

  @Test public void theoe2() {
    assertEquals(9, GraphGenerator.generateAllGraphs(3, "hasExactlyOneEdge").size());
  }

  @Test public void tir0() {
    assertEquals(1, GraphGenerator.generateAllGraphs(1, "isReflexive").size());
  }

  @Test public void tir1() {
    assertEquals(4, GraphGenerator.generateAllGraphs(2, "isReflexive").size());
  }

  @Test public void tir2() {
    assertEquals(64, GraphGenerator.generateAllGraphs(3, "isReflexive").size());
  }

  @Test public void tis0() {
    assertEquals(2, GraphGenerator.generateAllGraphs(1, "isSymmetric").size());
  }

  @Test public void tis1() {
    assertEquals(8, GraphGenerator.generateAllGraphs(2, "isSymmetric").size());
  }

  @Test public void tis2() {
    assertEquals(64, GraphGenerator.generateAllGraphs(3, "isSymmetric").size());
  }

  @Test public void titr0() {
    assertEquals(2, GraphGenerator.generateAllGraphs(1, "isTransitive").size());
  }

  @Test public void titr1() {
    assertEquals(13, GraphGenerator.generateAllGraphs(2, "isTransitive").size());
  }

  @Test public void titr2() {
    assertEquals(171, GraphGenerator.generateAllGraphs(3, "isTransitive").size());
  }

  @Test public void theoeir() {
    assertEquals(0, GraphGenerator.generateAllGraphs(3,
        new String[] {"hasExactlyOneEdge", "isReflexive"}).size());
  }

  @Test public void theoeis() {
    assertEquals(3, GraphGenerator.generateAllGraphs(3,
        new String[] {"hasExactlyOneEdge", "isSymmetric"}).size());
  }

  @Test public void theoeitr() {
    assertEquals(9, GraphGenerator.generateAllGraphs(3,
        new String[] {"hasExactlyOneEdge", "isTransitive"}).size());
  }

  @Test public void teq0() {
    assertEquals(1, GraphGenerator.generateAllGraphs(1,
        new String[] {"isReflexive", "isSymmetric", "isTransitive"}).size());
  }

  @Test public void teq1() {
    assertEquals(2, GraphGenerator.generateAllGraphs(2,
        new String[] {"isReflexive", "isSymmetric", "isTransitive"}).size());
  }

  @Test public void teq2() {
    assertEquals(5, GraphGenerator.generateAllGraphs(3,
        new String[] {"isReflexive", "isSymmetric", "isTransitive"}).size());
  }
}
