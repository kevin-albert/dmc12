const express = require('express');
const bodyParser = require('body-parser');
const swaggerUi = require('swagger-ui-dist');

module.exports.start = function(dmc12, config) {
    let app = express();

    app.get(/^\/?$/, (req, res) => res.redirect('/docs'));
    app.use('/docs', express.static(__dirname + '/swagger'));
    app.use('/docs', express.static(swaggerUi.getAbsoluteFSPath()));
    app.use(bodyParser.json());

    let onError = res => e => {
        console.error(e);
        res.status(500).json({ error: e.name, message: e.message });
    };

    let notFound = res => res.status(404).end();

    app.get('/node/:key', (req, res) => {
        dmc12.getNode(req.params.key, req.query.t)
            .defaultIfEmpty(null)
            .subscribe(node => {
                if (node) res.json(node);
                else notFound(res)
            }, onError(res));
    });

    app.put('/node/:key', (req, res) => {
        dmc12.putNode(req.params.key, req.body)
            .subscribe({
                error: onError(res),
                complete: () => res.status(201).end('ok')
            });
    });

    app.delete('/node/:key', (req, res) => {
        dmc12.deleteNode(req.params.key)
            .subscribe({
                error: onError(res),
                complete: () => res.status(204).end('ok')
            });
    });

    app.get('/edge/:from/:to', (req, res) => {
        dmc12.getEdge(req.params.from, req.params.to, req.query.t)
            .defaultIfEmpty(null)
            .subscribe({
                next: edge => {
                    if (edge) res.json(edge);
                    else notFound(res);
                },
                error: onError(res)
            })
    });

    app.put('/edge/:from/:to', (req, res) => {
        dmc12.addEdge(req.params.from, req.params.to, req.body)
            .subscribe({
                error: onError(res),
                complete: () => res.status(201).end('ok')
            });
    });

    app.delete('/edge/:from/:to', (req, res) => {
        dmc12.deleteEdge(req.params.from, req.params.to)
            .subscribe({
                error: onError(res),
                complete: () => res.status(204).end('ok')
            });
    });

    app.use((req, res, next) => {
        res.status(404).end();
    });

    app.listen(config.port, () => {
        console.log(`HTTP server listening on port ${config.port}`);
    });
}