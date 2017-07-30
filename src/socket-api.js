const { Observable } = require('rxjs');
const sockets = require('./socket-server');

module.exports.start = function(dmc12, config) {

    function requestHandler(verb, path, body) {
        return Observable.of({});
    }

    sockets.createServer(config.port, requestHandler, () => {
        console.log(`TCP server listening on port ${config.port}`);
    });
}