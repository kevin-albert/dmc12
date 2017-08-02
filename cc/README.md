## Dependencies:
### Ninja
The build system. Like a faster `make`. 
```
$ brew install ninja
```
### ASIO
Async IO / Networking Library  
Already checked in under `src/lib`


### ANTLR4
Parser generator. Sadly, this one is a bit clunky...
```
$ brew install java` (if you don't already have it)
$ cd /usr/local/lib
$ sudo curl -O http://www.antlr.org/download/antlr-4.7-complete.jar
$ export CLASSPATH=".:/usr/local/lib/antlr-4.7-complete.jar:$CLASSPATH"
$ alias antlr4='java -jar /usr/local/lib/antlr-4.7-complete.jar'
$ alias grun='java org.antlr.v4.gui.TestRig'
```

## Build:

```
$ ninja
```

## Test:

```
$ ninja -t test
```

## Clean:

```
$ ninja -t clean
```

## Recommended VSCode Settings
### Config
Add two directories to your includePath (`.vscode/c_cpp_properties.json`):
```
{
    "configurations": [{
            "name": "Mac",
            "includePath": [
                ...
                "${workspaceRoot}/cc/include",
                "${workspaceRoot}/cc/antlr4"
            ],
            ...
    }]
}
```

### Extensions
* C/C++
* ninja-build
* ANTLR4 grammar syntax
