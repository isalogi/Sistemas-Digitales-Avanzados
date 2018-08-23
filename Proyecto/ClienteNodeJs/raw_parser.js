const Buffer = require('safe-buffer').Buffer
const Transform = require('stream').Transform

class RawParser extends Transform {
  constructor (options) {
    options = options || {}
    super(options)
    this.buffer = Buffer.alloc(0)
  }
  _transform (chunk, encoding, cb) {
    let data = Buffer.concat([this.buffer, chunk])
    let parser = {
      pos: null,
      len: null,
      payload : null
    }

    if ((parser.pos = data.indexOf(0x7E)) !== -1) {

      parser.len = data[parser.pos + 3];
      parser.payload = data.slice(parser.pos + 1,  (parser.pos + 5 + parser.len))

      if(parser.payload.length == parser.len + 4){
        var buff = new Buffer(parser.len)
        parser.payload.slice(3, parser.payload.length-1).copy(buff);
        var sum = 0;
        for(var i = 0; i< buff.length; i++){
            sum += buff[i];
        }
        sum &= 0b0000000011111111;
        sum = 0xFF - sum;

        if(sum == parser.payload[parser.payload.length-1]){
          this.push(parser.payload);
        }
      }
    }
    this.buffer = data
    cb()
  }
  _flush (cb) {
    this.push(this.buffer)
    this.buffer = Buffer.alloc(0)
    cb()
  }
}

module.exports = RawParser