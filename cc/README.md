### Dependencies:
* Build System: Ninja
    * `brew install ninja`
* Async IO / Networking Library: ASIO
    * checked in under src/lib
* Lexer / Parser Generator: ??? Flex + Bison, probably
    * `brew install flex`
    * `brew install bison`
    * `echo 'export PATH="/usr/local/opt/bison/bin:$PATH"' >> ~/.bash_profile`

### Build:

```
$ brew install ninja (if needed)
$ ninja
```

### Clean:

```
$ ninja -t clean
```

