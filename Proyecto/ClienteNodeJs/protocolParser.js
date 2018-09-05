const Buffer = require('safe-buffer').Buffer
const Transform = require('stream').Transform

class ProtocolParser extends Transform {

    constructor(options) {
        options = options || {}
        super(options)
        this.buffer = Buffer.alloc(0)
    }

    calculateChecksum(tempBuffer) {

        return parseInt(tempBuffer[0], 16) + parseInt(tempBuffer[1], 16) + parseInt(tempBuffer[2], 16) + parseInt(tempBuffer[3], 16) + parseInt(tempBuffer[4], 16);
    }

    _transform(chunk, encoding, callback) {

        var tempBuffer = Buffer.concat([this.buffer, chunk]);
        var headerIndex = tempBuffer.lastIndexOf(0x7E);
        //se calcula el pedazo del buffer que se puede obtener a patir de la posición del header
        if (headerIndex != -1 && tempBuffer.length >= 5) {
            for (let index = 0; index < tempBuffer.length; index++) {

                console.log('temp ' + index + ' ' + tempBuffer[index].toString(16));
            }

            console.log('headerIndex' + headerIndex);
            let sliceBuffer = tempBuffer.slice(headerIndex, headerIndex + 5);

            //el if es para validar si el buffer esta completo y debe ser enviado
            if (sliceBuffer.length == 5) {

                let checksum = this.calculateChecksum(sliceBuffer);
              //  console.log(sliceBuffer[0].toString(16));
              //  console.log(sliceBuffer[1].toString(16));
              //  console.log(sliceBuffer[2].toString(16));
              //  console.log(sliceBuffer[3].toString(16));
              //  console.log(sliceBuffer[4].toString(16));
            
               console.log('Nuevo Buffer');
                if (checksum == sliceBuffer[4]) {

                    console.log('DATOS OK');
                    this.push(this.buffer);
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
