var express = require('express');
var router = express.Router();
var Comunication = require('../protocol/comunication');
//var arduino = require('../driver/arduino')

var conn = new Comunication();

/* GET home page. */
router.get('/', function (req, res) {
	res.render('../views/index');
});

router.post('/SendData', function (req, res) {
	conn.sendData();
});

module.exports = router;
