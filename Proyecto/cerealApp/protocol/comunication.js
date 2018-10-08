var SerialPort = require('serialport')
var ProtocolParser = require('./ProtocolParser')
var Events = require('events');

class Comunication extends Events.EventEmitter {

  constructor(arg) {
    super(arg);

    this.port = new SerialPort(arg.port, {
      baudRate: arg.baudRate
    });

    this.parser = this.port.pipe(new ProtocolParser());
    this._init();
  }

  _init() {
    var actualObject = this;
    this.parser.on('data', function (data) {
      actualObject.emit('dataRecived', data); //asociamos el evento a ser ejecutado cuando se reciban los datos
    })
  }

  sendData(inputbuffer) {
    setTimeout(function (port) {
      port.write(inputbuffer)
    }, 2000, this.port);
  }
}

module.exports = Comunication
