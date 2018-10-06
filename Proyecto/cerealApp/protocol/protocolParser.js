const Buffer = require('safe-buffer').Buffer
const Transform = require('stream').Transform

class ProtocolParser extends Transform {

    constructor(options) {
        options = options || {}
        super(options)
        this.buffer = Buffer.alloc(0)
    }

    calculateChecksum(tempBuffer) {
        var checksum = tempBuffer[0] + tempBuffer[1] + tempBuffer[2] + tempBuffer[3];
        return checksum;
    }

    _transform(chunk, encoding, callback) {

        var tempBuffer = Buffer.concat([this.buffer, chunk]);
        var headerIndex = tempBuffer.lastIndexOf(0x7E);
        //se calcula el pedazo del buffer que se puede obtener a patir de la posición del header
        //chekiar si la posicipin index + 5 existe, si existe ya puedo saber si esta lleno
        if (headerIndex != -1 && tempBuffer[headerIndex + 4] != undefined) {

            let sliceBuffer = tempBuffer.slice(headerIndex, headerIndex + 5);

            //el if es para validar si el buffer esta completo y debe ser enviado
            if (sliceBuffer.length == 5) {

                let checksum = this.calculateChecksum(sliceBuffer);

                if (checksum == sliceBuffer[4]) {
                    this.push(sliceBuffer);
                }
            }
        }
        callback();
        this.buffer = tempBuffer;
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
