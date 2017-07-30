
module.exports = History;

History.begin = (when, initialState) => new History(when, initialState);

function History(when, initialState) {
    this.log = [{ timestamp: when, action: 'put', state: initialState }];
    Object.defineProperty(this, 'latest', {
        get: () => this.log.slice(-1)[0],
        set: (e) => this.log.push(e)
    });
}

History.prototype.put = function(when, state) {
    if (when >= this.latest.timestamp) 
        this.latest = { timestamp: when, action: 'put', state: state };
    else throw new Error("You can't do that");
}

History.prototype.delete = function(when) {
    if (when >= this.latest.timestamp)
        this.latest = { timestamp: when, action: 'delete', state: null };
    else throw new Error("You can't do that");
}

History.prototype.get = function(when) {
    if (!when) return this.latest[2];
    else {
        // XXX this could be a binary search
        for (let i = this.log.length - 1; i >= 0; --i) {
            if (this.log[i].timestamp <= when) {
                return this.log[i];
            }
        }
    }
}