# shieldbot.js

Control [Shieldbot](http://www.seeedstudio.com/wiki/Shield_Bot_V1.0) with JavaScript

![Shieldbot](http://www.seeedstudio.com/wiki/images/thumb/0/05/Shield_Bot_5.jpg/800px-Shield_Bot_5.jpg)

## API

### `Shieldbot` - Constructor

Must be done inside board ready

```js
var five = require("johnny-five");
var Shieldbot = require('shieldbot');

var board = new five.Board();

board.on("ready", function(){

  var shieldbot = new Shieldbot();

});
```

### `wait` - Delay execution of next task

Returns a promise that is resolved after specified duration

```js
// delay for 1000 milliseconds
shieldbot.wait(1000).then(function(){
  // do something after delay
});
```

### `motor` - Turn a motor at a specified magnitude

Typically used internally

```js
// magnitude can be between -128 & 127
shieldbot.motor('leftPins', 127);
shieldbot.motor('rightPins', 127);
```

### `leftMotor` - Turn the left motor at specified magnitude

Typically used internally

```js
// magnitude can be between -128 & 127
shieldbot.leftMotor(127);
```

### `rightMotor` - Turn the right motor at specified magnitude

Typically used internally

```js
// magnitude can be between -128 & 127
shieldbot.rightMotor(127);
```

### `forward` - Drive forward

Given a speed and duration, drives the bot forward

Returns a promise that is resolved after specified duration

```js
shieldbot.forward(127, 4800);
```

### `reverse` - Drive in reverse

Given a speed and duration, drives the bot backward

Returns a promise that is resolved after specified duration

```js
shieldbot.reverse(127, 4800);
```

### `stop` - Stop

Stops the bot

Returns a resolved promised

```js
shieldbot.stop();
```

### `fastStopSide` - Disables motor on given side

Typically used internally

```js
shieldbot.fastStopSide('leftPins');
shieldbot.fastStopSide('rightPins');
```

### `fastStop` - Disables both motors

You should probably be using `stop`

```js
shieldbot.fastStop();
```

### `turnLeft` - Turn left

Given a speed and duration, turns the bot left

Returns a promise that is resolved after specified duration

```js
shieldbot.turnLeft(127, 1000);
```

### `turnRight` - Turn right

Given a speed and duration, turns the bot right

Returns a promise that is resolved after specified duration

```js
shieldbot.turnRight(127, 1000);
```

## Line Following

The Shieldbot also has finders on the front (good for line following)

We emit events when the finder values change

### `finder.on` & `finder.off` - Emitted when the finder changes state to on or off

Callbacks receive the pin number that changed

```js
shieldbot.on('finder.on', function(pin){
  console.log('on', pin);
});

shieldbot.on('finder.off', function(pin){
  console.log('off', pin);
});
```
