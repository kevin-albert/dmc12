# DMCQL (or something)

This is an informal langauge specification comprised mostly of examples, for the sake of collaboratively designing a graph query language.

## Features
* Graph-oriented
  * The language operates primarily on sets of nodes and edges. 
  * Queries can be specified using set arithmetic. 
  * The syntax is familiar to mathematians.
* Declarative
* Brevity
  * "Bind" syntax, e.g. `let S = {...}, R = {...} in S - R`
* Data types
  * Set - the primary data type
  * Map - a key-value dictionary. 
    * A graph is a map: `(V=set of nodes, E=set of egdes)`
    * An edge is a map: `(from=u, to=v, ... )`
    * A node is a map: `(id='x', ...)` 
  * String - a character sequence. Can be sorted and compared for equality
  * Number - a Decimal number fitting into 64 bits
  * UUID/GUID - A 128 bit number used to uniquely identify a node.

## Examples Querying

* Get a node
    ```
    V['xxx'] -> { (id='xxx', prop=value) }
    ```
    Returns a unique node with ```id``` `xxx`, which is guaranteed to have cardinality 1 or 0. Or maybe we want

    Question: A cardinality of 1 or 0 implies that the node is unique but we have 'Returns the set of nodes'? Changes to 'returns a unique node'

    Question: is ```id``` a reserved work representing a globally unique id for a node?

    ```
    node 'xxx' -> { (id='xxx', prop=value) }
    ```
    Question: Is the following true:

    ```V[id='xxx'] === V['xxx']```

* Find nodes
    ```
    V[name='Kevin'] -> { (id='xxx', name='Kevin', ...), ... }
    ```
    Returns the set of nodes with name 'Kevin'. Alternative:
    ```
    node (name='Kevin')
    ```
    or
    ```
    { v | v in V, v.name='Kevin' }
    ```

## Examples Writing

```
let G1 = {
  V: [
    u: { ... },
    v: { ... }
    q: { ... }
  ],
  E: [
     u: { to:v, meta: { ... } ],
     v: u,
     q: u
  ]
}
```

where u, v and q are unique node UUIDs?

Question: What if we want the database to generate a UUID and return the value? What then?

Example execution:

```
let gPrimary = openGraph (....);
gPrimary.merge(G1);
```

OR

we can assume that we are always in the context of "THE" primary graph...


```
merge(G1);
```


