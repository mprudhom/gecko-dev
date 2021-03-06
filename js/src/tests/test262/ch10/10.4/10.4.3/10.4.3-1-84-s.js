/// Copyright (c) 2012 Ecma International.  All rights reserved. 
/// Ecma International makes this code available under the terms and conditions set
/// forth on http://hg.ecmascript.org/tests/test262/raw-file/tip/LICENSE (the 
/// "Use Terms").   Any redistribution of this code must retain the above 
/// copyright and this notice and otherwise comply with the Use Terms.
/**
 * @path ch10/10.4/10.4.3/10.4.3-1-84-s.js
 * @description Strict Mode - checking 'this' (non-strict function declaration called by strict new'ed Function constructor)
 * @noStrict
 */
    
function testcase() {
fnGlobalObject().f = function()  { return this!==undefined;};
return (function () {return new Function("\"use strict\";return f();")();})();
}
runTestCase(testcase);