const dgram = require('dgram');
const client = dgram.createSocket('udp4');

// Define the message to be sent
const message = Buffer.from('Hello from Node.js!');

// Set the server address and port
const serverPort = 12345; 
const serverAddress = '192.168.7.2'; 

// Send the message to the server
client.send(message, serverPort, serverAddress, (err) => {
  if (err) {
    console.error('Error sending message:', err);
    client.close();
  } else {
    console.log('Message sent successfully!');
    // Close the client socket after sending the message
    client.close();
  }
});

// Handle any errors
client.on('error', (err) => {
  console.error('Client error:', err);
  client.close();
});