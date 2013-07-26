var Board = require('johnny-five/lib/board');

var when = require('when');

var _ = require('lodash');

var events = require('events');
var util = require('util');

function Shieldbot(opts){

  var leftPins = this.leftPins = [
    8, // I3 interface
    10 // I4 interface
  ];

  var rightPins = this.rightPins = [
    5, // I1 interface
    7 // I2 interface
  ];

  var speedPins = this.speedPins = [
    9, // Motor B (Left)
    6 // Motor A (Right)
  ];

  var speed = this.speed = [
    255, // speed of motorB (Left)
    255 // speed of motorA (Right)
  ];

  var finders = this.finders = [
    14, // A0
    15, // A1
    16, // A2
    17, // A3
    4
  ];

  Board.Device.call(this, opts = Board.Options({
    pins: leftPins.concat(rightPins, speedPins, finders)
  }));

  var INPUT = this.firmata.MODES.INPUT;
  var OUTPUT = this.firmata.MODES.OUTPUT;
  var PWM = this.firmata.MODES.PWM;

  var pinMode = _.bind(this.firmata.pinMode, this.firmata);
  var board = this.board;

  var self = this;

  _.forEach(leftPins, function(pin){
    pinMode(pin, OUTPUT);
  });

  _.forEach(rightPins, function(pin){
    pinMode(pin, OUTPUT);
  });

  _.forEach(speedPins, function(pin){
    pinMode(pin, PWM);
  });

  _.forEach(finders, function(finder){
    pinMode(finder, INPUT);
    board.digitalRead(finder, function(data){
      if(data === 0){
        self.emit('finder.on', finder);
      } else {
        self.emit('finder.off', finder);
      }
    });
  });
}

util.inherits(Shieldbot, events.EventEmitter);

Shieldbot.prototype.wait = function(length){
  var deferred = when.defer();
  this.board.wait(length, deferred.resolve);
  return deferred.promise;
};

Shieldbot.prototype.motor = function(pin, magnitude){
  var actualSpeed = 0;
  var ratio;

  var side;
  if(pin === 'leftPins'){
    side = 0;
  }

  if(pin === 'rightPins'){
    side = 1;
  }

  /* jshint eqnull: true */
  if(side == null){
    return;
  }

  if(magnitude !== 0){
    ratio = Math.abs(magnitude) / 128;
    actualSpeed = parseInt(ratio * this.speed[side], 10); //define your speed based on global speed

    this.firmata.analogWrite(this.speedPins[side], actualSpeed);

    if(magnitude > 0){
      this.firmata.digitalWrite(this[pin][0], this.firmata.HIGH);
      this.firmata.digitalWrite(this[pin][1], this.firmata.LOW);//turn right motor clockwise
    } else {
      this.firmata.digitalWrite(this[pin][0], this.firmata.LOW);
      this.firmata.digitalWrite(this[pin][1], this.firmata.HIGH);
    }
  } else {
    this.firmata.analogWrite(this.speedPins[side], magnitude);
  }
};

Shieldbot.prototype.leftMotor = function(magnitude){
  this.motor('leftPins', magnitude);
};

Shieldbot.prototype.rightMotor = function(magnitude){
  this.motor('rightPins', magnitude);
};

Shieldbot.prototype.forward = function(speed, length){
  var deferred = when.defer();
  if(speed >= 0){
    this.leftMotor(speed);
    this.rightMotor(speed);
    this.board.wait(length, deferred.resolve);
  } else {
    deferred.reject();
  }
  return deferred.promise;
};

Shieldbot.prototype.reverse = function(speed, length){
  var deferred = when.defer();
  if(speed >= 0){
    this.leftMotor(-(speed));
    this.rightMotor(-(speed));
    this.board.wait(length, deferred.resolve);
  } else {
    deferred.reject();
  }
  return deferred.promise;
};

Shieldbot.prototype.stop = function(){
  var deferred = when.defer();
  this.leftMotor(0);
  this.rightMotor(0);
  return deferred.resolve();
};

Shieldbot.prototype.fastStopSide = function(pin){
  this.firmata.digitalWrite(this[pin][0], this.firmata.LOW);
  this.firmata.digitalWrite(this[pin][0], this.firmata.LOW);
};

Shieldbot.prototype.fastStop = function(){
  this.fastStopSide('leftPins');
  this.fastStopSide('rightPins');
};

Shieldbot.prototype.turnLeft = function(speed, length){
  var deferred = when.defer();
  this.leftMotor(speed);
  this.rightMotor(0);
  this.board.wait(length, deferred.resolve);
  return deferred.promise;
};

Shieldbot.prototype.turnRight = function(speed, length){
  var deferred = when.defer();
  this.leftMotor(0);
  this.rightMotor(speed);
  this.board.wait(length, deferred.resolve);
  return deferred.promise;
};

module.exports = Shieldbot;