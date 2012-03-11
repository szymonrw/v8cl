'use strict';

var cl = require('cl');
var testgc = cl.testgc;

// var value;
// for (var i = 0; i < 10; ++i) {
//   value = testgc(value);
//   gc();
// }

(function () {
  var cl = require('cl');
  var platforms = cl.getPlatformIDs();
  var devices = cl.getDeviceIDs(platforms[0], cl.DEVICE_TYPE_ALL);
  cl.createContext(null, devices);
  // console.log(platforms, devices);
})();

for (var i = 0; i < 100; ++i) {
  gc();
}
