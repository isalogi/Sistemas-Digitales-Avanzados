var SerialPort = require('serialport')
var readline = require('readline');

var port = new SerialPort('COM5', {
    baudRate: 115200}
);

Readline = SerialPort.parsers.Readline;
parser = new Readline();
port.pipe(parser);

parser.on('data', function(data){
    console.log(data.toString('utf8'));
})

var test = setInterval(function(){
    var frame = [0x7e, 0x14, 0xAB];
    var buff = Buffer.from(frame);
    port.write(buff)
    console.log(buff)
}, 5000)