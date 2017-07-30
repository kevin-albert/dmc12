const net = require('net');
const MAX_REQUEST_SIZE = 1 << 20     // 1 MB
const REGEX = /(\w+)\s+(\S+)(\s+(.*))?/

module.exports.createServer = function(port, handler, cb) {
    net.createServer(socket => {

        let buffers = [];
        let size = 0;
        socket.on('data', buffer => {
            if (typeof buffer !== 'string') buffer = buffer.toString('utf8');
            for (let idx = 0; idx < buffer.length;) {
                // split on '\r'
                let next = buffer.indexOf('\r', idx);
                let chunk = buffer.slice(idx, Math.max(next, buffer.length));
                size += chunk.length;
                if (size > MAX_REQUEST_SIZE) {
                    console.error(`request exceeded ${MAX_REQUEST_SIZE} bytes`);
                    socket.destroy();
                }
                buffers.push(chunk);

                // found a '\r'. handle the current request
                if (next !== -1) {
                    handleRequest();
                } else {
                    next = buffer.length;
                }
                idx = next + 1;
            }
        });

        function handleRequest() {
            let data = buffers.join('');
            size = 0;
            buffers = [];
            let match = REGEX.exec(data);
            if (match) {
                let verb = match[1];
                let resource = match[2].split('/');
                let body = match[4];
                if (body && body !== '') {
                    try {
                        body = JSON.parse(body);
                    } catch (e) {
                        console.error('invalid request json');
                        socket.end('ERROR { "error": "JSON not readable" }\r\n');
                        return;
                    }
                } else {
                    body = undefined;
                }
                let response = handler(verb, resource, body);
                if (!response) {
                    throw new Error('Callback did not return an Observable');
                }
                response.subscribe(
                    next => {
                        socket.write('OK');
                        if (next) {
                            socket.write(' ');
                            socket.write(JSON.stringify(next));
                        }
                        socket.write('\r\n');
                    },
                    error => {
                        socket.write('ERROR ');
                        socket.write(JSON.stringify({ error: error.name, message: error.message }));
                        socket.write('\r\n');
                    }
                );
            } else {
                socket.end('ERROR { "error": "Malformed request" }');
            }
        }

    }).listen(port, cb)
}