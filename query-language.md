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
  * Number - any number that fits in 64 bits

## Examples

* Get a node
    ```
    V['xxx'] -> { (id='xxx', prop=value) }
    ```
    Returns the set of nodes with id `xxx`, which is guaranteed to have cardinality 1 or 0. Or maybe we want
    ```
    node 'xxx' -> { (id='xxx', prop=value) }
    ```
    Or even just
    ```
    xxx -> (id='xxx', prop=value)
    ```

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
