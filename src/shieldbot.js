var Board = require("johnny-five/lib/board");

var when = require('when');

function Shieldbot(){

  var opts = Board.options([5,6,7,8,9,10]);

  this.board = Board.mount(opts);
  this.firmata = this.board.firmata;

  this.speed = {
    left: 255, //define the speed of motorB
    right: 255 //define the speed of motorA
  };

  this.right = {
    pin1: 5, //define I1 interface
    pin2: 7 //define I2 interface
  };

  this.left = {
    pin1: 8, //define I3 interface
    pin2: 10 //define I4 interface
  };

  this.speedPin = {
    left: 9, //enable motor B
    right: 6 //enable right motor (bridge A)
  };

  this.firmata.pinMode(this.right.pin1, this.firmata.MODES.OUTPUT);
  this.firmata.pinMode(this.right.pin2, this.firmata.MODES.OUTPUT);
  this.firmata.pinMode(this.speedPin.right, this.firmata.MODES.PWM);

  this.firmata.pinMode(this.left.pin1, this.firmata.MODES.OUTPUT);
  this.firmata.pinMode(this.left.pin2, this.firmata.MODES.OUTPUT);
  this.firmata.pinMode(this.speedPin.left, this.firmata.MODES.PWM);
}

Shieldbot.prototype.wait = function(length){
  var deferred = when.defer();
  this.board.wait(length, deferred.resolve);
  return deferred.promise;
};

Shieldbot.prototype.motor = function(side, magnitude){
  var actualSpeed = 0;
  var ratio;

  if(magnitude !== 0){
    ratio = Math.abs(magnitude) / 128;
    actualSpeed = parseInt(ratio * this.speed[side], 10); //define your speed based on global speed

    this.firmata.analogWrite(this.speedPin[side], actualSpeed);

    if(magnitude > 0){
      this.firmata.digitalWrite(this[side].pin1, this.firmata.HIGH);
      this.firmata.digitalWrite(this[side].pin2, this.firmata.LOW);//turn right motor clockwise
    } else {
      this.firmata.digitalWrite(this[side].pin1, this.firmata.LOW);
      this.firmata.digitalWrite(this[side].pin2, this.firmata.HIGH);
    }
  } else {
    this.firmata.analogWrite(this.speedPin[side], magnitude);
  }
};

Shieldbot.prototype.leftMotor = function(magnitude){
  this.motor('left', magnitude);
};

Shieldbot.prototype.rightMotor = function(magnitude){
  this.motor('right', magnitude);
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

Shieldbot.prototype.fastStopSide = function(side){
  this.firmata.digitalWrite(this[side].pin1, this.firmata.LOW);
  this.firmata.digitalWrite(this[side].pin2, this.firmata.LOW);
};

Shieldbot.prototype.fastStop = function(){
  this.fastStopSide('left');
  this.fastStopSide('right');
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