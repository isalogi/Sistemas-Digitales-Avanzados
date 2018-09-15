var express = require('express');
var router = express.Router();
//var arduino = require('../driver/arduino')

/* GET home page. */
router.get('/', function(req, res) {
	res.render('../views/index');
});

module.exports = router;
