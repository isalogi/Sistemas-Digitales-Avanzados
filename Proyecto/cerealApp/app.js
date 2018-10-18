// load things
var express = require('express');
var path = require('path');
var logger = require('morgan');
var bodyParser = require('body-parser');
var app = express();
var flash = require('connect-flash');
var session = require('express-session');


// set the view engine to ejs

app.use(express.static(path.join(__dirname, 'public')));
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'ejs');

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: false }));
app.use(logger('common'));
app.use(flash());
app.use(session({
    cookie: { maxAge: 60000 },
    secret: 'woot',
    resave: false,
    saveUninitialized: false
}));

var index = require('./routes/index')

app.use('/', index)

app.listen(8080);
console.log('8080 is the magic port');