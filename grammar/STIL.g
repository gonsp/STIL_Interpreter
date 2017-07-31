grammar STIL;

stil_test: ;

// White spaces ignored
WS: [ \t\r\n]+ -> channel(99);