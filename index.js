var five = require("johnny-five");

var Shieldbot = require('./src/shieldbot');

var sequence = require('when/sequence');

var board = new five.Board();

board.on("ready", function() {

  var shieldbot = new Shieldbot();

  this.repl.inject({
    shieldbot: shieldbot
  });

  shieldbot.on('finder.on', function(pin){
    console.log('on', pin);
  });

  shieldbot.on('finder.off', function(pin){
    console.log('off', pin);
  });

  var forward = function(){
    return shieldbot.forward(127, 4800);
  };

  var right = function(){
    return shieldbot.turnRight(127, 1000);
  };

  var left = function(){
    return shieldbot.turnLeft(127, 1000);
  };

  var reverse = function(){
    return shieldbot.reverse(127, 4800);
  };

  var stop = function(){
    return shieldbot.stop();
  };

  sequence([
    forward,
    right,
    forward,
    left,
    reverse,
    stop
  ]);

});