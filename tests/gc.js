'use strict';

var cl = require('cl');
var testgc = cl.testgc;

(function () {
  var cl = require('cl');
  var platforms = cl.getPlatformIDs();
  var devices = cl.getDeviceIDs(platforms[0], cl.DEVICE_TYPE_ALL);
  cl.createContext(null, devices);
})();

for (var i = 0; i < 100; ++i) {
  gc();
}
