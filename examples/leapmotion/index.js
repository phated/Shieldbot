var five = require("johnny-five");

var Shieldbot = require('../../src/shieldbot');

var sequence = require('when/sequence');

var leap = require('leapjs');

var board = new five.Board();

board.on("ready", function() {

  var shieldbot = new Shieldbot();

  this.repl.inject({
    shieldbot: shieldbot
  });

  var prevZ;

  leap.loop(function(frame){
    if(frame.hands.length){
      var z = frame.hands[0].palmPosition[2];
      var velZ = frame.hands[0].palmVelocity[2];
      if(prevZ == null){
        prevZ = z;
      }
      var direction;
      if(z < prevZ && Math.abs(velZ) > 50){
        direction = 'forward';
        shieldbot.forward(127, 0.1);
      } else if(z > prevZ && Math.abs(velZ) > 50){
        direction = 'backward';
        shieldbot.reverse(127, 0.1);
      } else {
        direction = 'still';
        shieldbot.stop();
      }
      console.log(direction, z, velZ);

      prevZ = z;
    } else {
      shieldbot.stop();
    }
  });

});