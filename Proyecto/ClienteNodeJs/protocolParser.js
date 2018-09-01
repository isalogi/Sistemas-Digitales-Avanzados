const Buffer = require('safe-buffer').Buffer
const Transform = require('stream').Transform

class ProtocolParser extends Transform {

    constructor(options) {
        options = options || {}
        super(options)
        this.buffer = Buffer.alloc(0)
    }

    _transform(chunk, encoding, callback) {
        console.log('byte :' + chunk.length);
        var tempBuffer= Buffer.concat([this.buffer, chunk]);
        var headerIndex = tempBuffer.indexOf(0x7E);
        //se calcula el pedazo del buffer que se puede obtener a patir de la posición del header 
        tempBuffer.slice(headerIndex + 1, headerIndex + (tempBuffer.length-headerIndex.length));

        if (this.buffer.length >= 5) {
            
            if ( tempIndex !== -1) {
                console.log('header:' + tempIndex);
            }
            this.push(this.buffer);
        }
        callback();
        this.buffer=tempBuffer;
    }
    
    _flush(callback) {
        this.push(this.buffer);
        this.buffer = Buffer.alloc(0);
        callback();
    }

    readData(emitter, buffer) {
    }

}
//para poder usar la clase desde afuera

module.exports = ProtocolParser
