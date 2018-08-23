var SerialPort = require('serialport')
var RawParser = require('./raw_parser')
var readline = require('readline');

var writeCallback = function writeBuffer(error, result) {
  if (error) {
    console.log('Error while sending message : ' + error);
  }
  if (result) {
    console.log('Response received after sending message : ' + result);
  }
}

var openCallback = function openPort(error) {
  if (error) {
    console.log('Error while opening the port ' + error);
  } else {
    console.log('Port open');

    // Switches the port into "flowing mode"

    port.on('data', function (data) {
      console.log('Data:', data);
    });

    //construir el buffer
    //enviamos el buffer
    //uint8_t inpBuffer[5] = {0x7e, 0, trig, 0, 0};

    var buffer = new Buffer(5);
    buffer.writeUInt8(0x7e,0);
    buffer.writeUInt8(0,1);
    buffer.writeUInt8(8,2);
    buffer.writeUInt8(8,3);
    var checksum= 0x7e+8;
    buffer.writeUInt8(checksum,4);

    console.log('before write');

    port.write(buffer, function (err, result) {
      if (err) {
        console.log('Error while sending message : ' + err);
      }

      console.log('Response received after sending message : ' + result);
    });
  }
}

var port = new SerialPort(
  'COM5',
  {
    baudRate: 115200,
    autoOpen: false,
  }
);

Readline = SerialPort.parsers.Readline;
parser = new Readline();
port.pipe(parser);

// Creating the parser and piping can be shortened to
// const parser = port.pipe(new Readline());
port.open(openCallback);

readline.emitKeypressEvents(process.stdin);
process.stdin.setRawMode(true);

process.stdin.on('keypress', (str, key) => {
  if (key.ctrl && key.name === 'c') {
    process.exit();
  } else {
  }
});



//console.log('Press any key...');
//console.log('Waiting for Serial Data...');