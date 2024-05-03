// Variables to track keyboard input
let keyPressed = {
    "ArrowLeft": false,
    "ArrowRight": false,
    "ArrowUp": false,
    "ArrowDown": false,
    "w": false,
    "s": false,
    "a": false,
    "d": false,
    "Escape": false
};
let lastKey = "";

socket = io.connect();
// Function to emit request based on pressed keys
function emitRequest() {
    if (keyPressed["ArrowLeft"]) {
        // console.log('left');
        socket.emit('REQUEST', "left");
    }
    else if (keyPressed["ArrowRight"]) {
        socket.emit('REQUEST', "right");
    }
    else if (keyPressed["ArrowUp"]) {
        socket.emit('REQUEST', "forward");
    }
    else if (keyPressed["ArrowDown"]) {
        socket.emit('REQUEST', "backward");
    }  

    else if (keyPressed["ArrowDown"]) {
        socket.emit('REQUEST', "backward");
    } 
    else if (lastKey && isMovementKey(lastKey)) {
        socket.emit('REQUEST', "stop");
    }

    ///////////////////////////////////////////////////////
    if (keyPressed["w"]) {
        socket.emit('REQUEST', "rotation_up");
    } 
    else if (keyPressed["s"]) {
        socket.emit('REQUEST', "rotation_down");
    } 
    else if (keyPressed["a"]) {
        socket.emit('REQUEST', "rotation_left");
    } 
    else if (keyPressed["d"]) {
        socket.emit('REQUEST', "rotation_right");
    } 
    ////////////////////////////////////////////////

    if (keyPressed["Escape"]) {
        socket.emit('REQUEST', "terminate_program");
    }
    
}

function isMovementKey(key) {
    return (key === 'ArrowLeft' || key === 'ArrowRight' || key === 'ArrowUp' || key === 'ArrowDown');
}


// Event listeners for keyboard input
document.addEventListener("keydown", function(event) {
    lastKey = event.key;
    if (keyPressed.hasOwnProperty(event.key)) {
        keyPressed[event.key] = true; // Set keyPressed to true when a key is pressed
        emitRequest();
    }
});

document.addEventListener("keyup", function(event) {
    if (keyPressed.hasOwnProperty(event.key)) {
        keyPressed[event.key] = false; // Set keyPressed to false when a key is released
        emitRequest();
    }
});