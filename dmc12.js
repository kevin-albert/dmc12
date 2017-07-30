const { Observable } = require('rxjs');
const History = require('./history');

module.exports = DMC12;

function DMC12() {
    this.nodes = {};
    this.edges = {};
}

DMC12.prototype.getNode = function(key, when) {
    return Observable.create(subscriber => {
        if (!when) when = Date.now();
        let history = this.nodes[key];
        if (history) {
            let record = history.get(when);
            if (record.state) {
                subscriber.next({
                    key: key,
                    data: record.state
                });
            }
        }
        subscriber.complete();
    });
}

DMC12.prototype.putNode = function(key, data) {
    if (!data) data = {};
    let history = this.nodes[key];
    if (!history) 
        this.nodes[key] = History.begin(Date.now(), data);
    else history.put(Date.now(), data);
    return Observable.empty();
}

DMC12.prototype.deleteNode = function(key) {
    let history = this.nodes[key];
    if (history) {
        let now = Date.now();
        if (history.get(now)) {
            history.delete(now);
        }
    }
    return Observable.empty();
}

DMC12.prototype.getEdge = function(from, to, when) {
    return new Observable(subscriber => {
        if (!when) when = Date.now();
        let histories = this.edges[from];
        if (histories) {
            let history = histories[to];
            if (history) {
                let edge = history.get(when);
                if (edge) {
                    let res = {
                        from: from,
                        to: to,
                        data: edge
                    }
                }
                subscriber.next(history.get(when))
            }
        }
        subscriber.complete();
    });
}

DMC12.prototype.putEdge = function(from, to, data) {
    if (!data) data = {};
    let histories = this.edges[from];
    if (!histories) histories = this.edges[from] = {};
    let history = histories[to];
    if (!history) history = History.begin(Date.now(), data);
    else history.put(Date.now(), data);
    return Observable.empty();
}

DMC12.prototype.deleteEdge = function(from, to, data) {
    let histories = this.edges[from];
    if (histories) {
        let history = histories[to];
        if (history) {
            history.delete(Date.now(), data);
        }
    }
    return Observable.empty();
}