const DMC12 = require('./dmc12');

let dmc12 = new DMC12();

require('./rest-api').start(dmc12, { port: 8000 });
require('./socket-api').start(dmc12, { port: 8001 });