var express = require('express');
var router = express.Router();
var Comunication = require('../protocol/comunication');
var Repository = require('../dataBase/repository');
var rep = new Repository();

var conn = new Comunication({
	port: 'COM5',
	baudRate: 115200
});


conn.on('dataRecived', function (data) {
	for (let i = 0; i < data.length; i++) {
		console.log('Datos:' + data[i]);
	}

	if (data.length == 5) {
		if (data[1] == 0x00) {
			if (data[3] < 15) {
				var frame = [0x7e, 0x01, 0x06, 0xB4, 0x139];
				var bufferActuator = Buffer.from(frame);
				conn.sendData(bufferActuator);
			}

			else if (data[3] >= 15 && data[3] < 17) {
				var frame = [0x7e, 0x01, 0x06, 0xB4, 0x139];
				var bufferActuator = Buffer.from(frame);
				conn.sendData(bufferActuator);
				console.log("Se estan acabando los granos");
				rep.insertAlert({
					Date: new Date().toDateString,
					Message: "Se estan acabando los granos"
				},function(){});
			}

			else {
				console.log("No hay granos");
				rep.insertAlert({
					Date: new Date().toDateString(),
					Message:"No hay granos"
				},function(){});
			}
		}
		else if (data[1] == 0x01) {
			if (data[3] == 0x01) {
				console.log('¡Mi labor aquí ha terminado!');
			}
		}
	}
});

/* GET home page. */
router.get('/', function (req, res) {
	res.render('../views/index');
});

router.get('/viewData',function(req,res){
	res.render('../views/viewData');
})

router.get('/getData', function (req, res) {

	rep.findAlert(function (docs) {
		res.send(docs);
	});

});

router.post('/dispence', function (req, res) {
	var frame = [0x7e, 0x00, 0x08, 0x00, 0x86];
	var bufferSensor = Buffer.from(frame);

	conn.sendData(bufferSensor);
	res.end();
});

module.exports = router;

