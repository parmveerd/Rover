const express = require('express');
const http = require('http');
const PORT = 8088;
const socketio = require('socket.io');
const socket = require('./socket');
const Router = require('./routes');

const app = express();
const server = http.createServer(app);

socket.initialize(server);

app.use('/', Router);

server.listen(PORT, function () {
    console.log('Web app listening on port 8088!');
});
