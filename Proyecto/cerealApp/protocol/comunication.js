var SerialPort = require('serialport')
var ProtocolParser = require('./ProtocolParser')

class Comunication {

  constructor() {
    this.port = new SerialPort('COM5', {
      baudRate: 115200
    });

    this.comunicationOK=false;
    this.parser = this.port.pipe(new ProtocolParser());

    this.parser.on('data', function (data) {
      for (let i = 0; i < data.length; i++) {
        console.log('Datos:' + data[i]);
      }

      if(data.length==5)
      {
        this.comunicationOK=true;
      }
    });
  }

  sendData() {
    this.comunicationOK=false;

    setTimeout(function (port) {
      var frame = [0x7e, 0x01, 0x06, 0xB4, 0x139];
      var buff = Buffer.from(frame);
      port.write(buff)
    }, 2000, this.port);
  }
}

module.exports = Comunication
