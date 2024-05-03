const express = require('express');
const path = require('path');
const router = express.Router();

router.get('/', function(req, res, next) {  
    res.sendFile(path.join(__dirname + "/public/index.html"));
});

router.get('/style.css', function(req, res) {
	res.sendFile(path.join(__dirname + "/public/style.css"));
});

router.get('/server.js', function(req, res) {
	res.sendFile(path.join(__dirname + "/server.js"));
});

router.get('/script.js', function(req, res) {
	res.sendFile(path.join(__dirname + "/public/script.js"));
});
router.get('/socket.js', function(req, res) {
	res.sendFile(path.join(__dirname + "/socket.js"));
});

module.exports = router;
