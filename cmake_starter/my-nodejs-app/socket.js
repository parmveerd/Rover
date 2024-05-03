const { Server } = require('socket.io');
const dgram = require('dgram');

var io;

// used online resources and lectures to understand and used their work in initialize
function initialize(server) {
    io = new Server(server);

    // on connection to node server
    io.on('connection', (socket) => {
        console.log('connected');

        // on request received from another server
        socket.on('REQUEST', (data) => {
            console.log(data);

            const PORT = 12345;
            const HOST = '192.168.7.2';
            const buffer = Buffer.from(data);

            const client = dgram.createSocket('udp4');
            client.send(buffer, 0, buffer.length, PORT, HOST, function(err, bytes) {
                if (err) 
                    throw err;
                console.log('UDP message sent to ' + HOST + ':' + PORT);
            });

            client.on('listening', function () {
                const address = client.address();
            });

            client.on('message', function (message, remote) {
                const reply = message.toString('utf8')
                socket.emit('Reply', reply);
                client.close();
            });
            client.on('error', function (err) {
                console.error("UDP server error:", err);
                socket.emit("UDPServerError", err);
                client.close();
              });
        });
    });
    
}

module.exports = {
    initialize
};
