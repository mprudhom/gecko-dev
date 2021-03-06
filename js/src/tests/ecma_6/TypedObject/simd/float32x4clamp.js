// |reftest| skip-if(!this.hasOwnProperty("TypedObject"))
var BUGNUMBER = 946042;
var float32x4 = SIMD.float32x4;
var int32x4 = SIMD.int32x4;

var summary = 'float32x4 add';

function test() {
  print(BUGNUMBER + ": " + summary);

  // FIXME -- Bug 948379: Amend to check for correctness of border cases.

  var a = float32x4(1, 2, 3, 4);
  var b = float32x4(10, 20, 30, 40);
  var c = SIMD.float32x4.add(a, b);
  assertEq(c.x, 11);
  assertEq(c.y, 22);
  assertEq(c.z, 33);
  assertEq(c.w, 44);

  if (typeof reportCompare === "function")
    reportCompare(true, true);
}

test();

