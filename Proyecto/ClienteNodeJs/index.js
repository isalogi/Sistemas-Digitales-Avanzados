var SerialPort = require('serialport')
var readline = require('readline');
var ByteLength = require('@serialport/parser-readline')
var ProtocolParser = require('./ProtocolParser')

var port = new SerialPort('COM5', {
  baudRate: 115200
}
);

parser=port.pipe(new ProtocolParser());

setTimeout(function () {
  var frame = [0x7e, 0x00, 0x08, 0x00, 0x86];
  var buff = Buffer.from(frame);
  port.write(buff)
  //console.log(buff)
}, 4000)


parser.on('data', function (data) {
  console.log('Datos: ' + data[1].toString(16));
})


