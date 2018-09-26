var SerialPort = require('serialport')
var ProtocolParser = require('./ProtocolParser')

var port = new SerialPort('COM10', {
  baudRate: 115200
});

parser = port.pipe(new ProtocolParser());

setTimeout(function () {
  var frame = [0x7e, 0x01, 0x06, 0xB4, 0x139];
  var buff = Buffer.from(frame);
  port.write(buff)
}, 2000);

parser.on('data', function (data) {
  for (let i = 0; i < data.length; i++) {
    console.log('Datos:' + data[i]);
  }
});
