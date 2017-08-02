grammar DMCQL;

start: expr ;

expr: vscan ;

vscan: 'V[' STRING ']' { std::cout << "find vertex " << $STRING.text << "\n"; };

STRING
    : '"' DOUBLECHAR* '"' 
    | '\'' SINGLECHAR* '\''
    ;

fragment DOUBLECHAR: ~["\r\n] | '\\"' | '\\\r' | '\\\n';
fragment SINGLECHAR: ~['\r\n] | '\\\'' | '\\\r' | '\\\n';

