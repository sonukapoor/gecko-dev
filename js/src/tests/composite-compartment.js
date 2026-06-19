// Test: Composite objects are re-interned across compartment boundaries
// rather than wrapped in a CrossCompartmentWrapper.

// Create two separate compartments.
const g1 = newGlobal({newCompartment: true});
const g2 = newGlobal({newCompartment: true});

// Create a Composite in the shell's compartment.
const key = "a=1,b=2";
const c1 = makeComposite(key);
assertEq(isComposite(c1), true, "c1 should be a Composite");

// Pass c1 to g2. Instead of a CrossCompartmentWrapper, g2 should
// receive a re-interned Composite with the same key.
const checkInG2 = g2.evaluate(
  `(function(c) {
    if (!isComposite(c)) {
      throw new Error("Expected Composite, got: " + Object.prototype.toString.call(c));
    }
    return true;
  })`
);
assertEq(checkInG2(c1), true, "c1 should appear as a Composite in g2");

// A second pass should return the same interned pointer in g2.
const getInG2 = g2.evaluate(`(function(c) { return c; })`);
const c2a = getInG2(c1);
const c2b = getInG2(c1);
assertEq(c2a === c2b, true, "same key should yield same object in g2");

print("PASS: Composite re-interning across compartments works");
