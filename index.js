var five = require("johnny-five");

var Shieldbot = require('./src/shieldbot');

var sequence = require('when/sequence');

var board = new five.Board();

board.on("ready", function() {

// #define finder1 A0      //define line finder S1
// #define finder2 A1      //define line finder S2
// #define finder3 A2      //define line finder S3
// #define finder4 A3      //define line finder S4
// #define finder5 4       //define line finder S5


  // pinMode(finder1, INPUT);
  // pinMode(finder2, INPUT);
  // pinMode(finder3, INPUT);
  // pinMode(finder4, INPUT);
  // pinMode(finder5, INPUT);


  var shieldbot = new Shieldbot();

  var circle = {
    left: function(){
      shieldbot.motor('left', 25);
      shieldbot.motor('right', 127);
    },
    right: function(){
      shieldbot.motor('left', 127);
      shieldbot.motor('right', 25);
    }
  };

  this.repl.inject({
    shieldbot: shieldbot
  });

  // shieldbot.forward(20);
  // var side = 'left';

  // circle[side]();

  // this.loop(4800, function(){
  //   side = side === 'left' ? 'right' : 'left';
  //   circle[side]();
  // });

  // var turn = shieldbot.turnRight;

  // this.loop(4800, function(){
  //   turn = turn == shieldbot.turnRight ? shieldbot.turnLeft : shieldbot.turnRight;

  //   turn.apply(shieldbot);
  // });

  // shieldbot.forward(127)
  //   .then(function(){
  //     return shieldbot.turnRight(127, 1000);
  //   })
  //   .then(function(){
  //     return shieldbot.forward(127, 4800);
  //   })
  //   .then(function(){
  //     return shieldbot.turnLeft(127, 1000);
  //   })
  //   .then(function(){
  //     return shieldbot.reverse(127, 4800);
  //   })
  //   .then(function(){
  //     return shieldbot.stop();
  //   })
  //   .then(function(){
  //     console.log('end!');
  //   });

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