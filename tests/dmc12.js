const expect = require('expect');
const DMC12 = require('../src/dmc12');

describe('DMC12', () => {
    
    beforeEach(function() {
        this.dmc12 = new DMC12();
    });
    
    it('should exist', function() {
        expect(this.dmc12).toExist();
    });

    it('should return empty for missing node', function(done) {
        this.dmc12.getNode('x')
            .isEmpty()
            .subscribe(empty => {
                expect(empty).toBe(true);
                done();
            }, done);
    });

    it('should create a node', function(done) {
        let data = { name: 'X' };
        this.dmc12.putNode('x', data).defaultIfEmpty(null)
            .flatMap(() => this.dmc12.getNode('x'))
            .subscribe(node => {
                expect(node).toExist();
                expect(node.key).toEqual('x');
                expect(node.data).toEqual(data);
                done();
            }, done);
    });

    it('should store node history', function(done) {
        this.dmc12.putNode('x', { value: 1 }).defaultIfEmpty(null)
            .map(() => Date.now())
            .delay(1)
            .flatMap(now => this.dmc12.putNode('x', { value: 2 }).defaultIfEmpty(now))
            .flatMap(now => this.dmc12.getNode('x', now))
            .subscribe(node => {
                expect(node).toExist();
                expect(node.key).toEqual('x');
                expect(node.data).toEqual({ value: 1 });
                done();
            }, done);
    });
});