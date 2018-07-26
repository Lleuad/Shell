# Shell

### Syntax ###
```
<program> ::= <block> "E"
<block> ::= [ <statement> ]*
<statement> ::= <IF> | <WHILE> | <LOOP> | <REPEAT> | <FOR> | <DO> | <BREAK> | <assignment>
<IF> ::= "I" <b-expression> <block> [ "L" <block> ] "E"
<WHILE> ::= "W" <b-expression> <block> "E"
<LOOP> ::= "L" <block> "E"
<REPEAT> ::= "R" <block> "U" <b-expression>
<FOR> ::= "F" <name> "=" <expression> <expression> <block> "E"
<DO> ::= "D" <expression> <block> "E"
<BREAK> ::= "B"

<b-expression> ::= <b-term> [ <orop> <b-term> ]*
<orop> ::= "|" | "~"
<b-term> ::= <not-factor> [ "&" <not-factor> ]*
<not-factor> ::= [ "!" ] <b-factor>
<b-factor> ::= <b-literal> | <relation>
<b-literal> ::= "T" | "F"
<relation> ::= <expression> [ <relop> <expression> ]
<relop> ::= "=" | "#" | "<" | ">"

<assignment> ::= <name> "=" <expression>
<expression> ::= <term> [ <addop> <term> ]*
<addop> ::= "+" | "-"
<term> ::= <signed-factor> [ <mulop> <signed-factor> ]*
<mulop> ::= "*" | "/"
<signed-factor> ::= [ <addop> ] <factor>
<factor> ::= "(" <expression> ")" | <ident> | <number>
<ident> ::= <name> [ "()" ]

<name> ::= <alpha> [ <alnum> ]*
```

### Credits ###

terminal.js is a modified version [terminaljs](https://github.com/eosterberg/terminaljs) by [Erik Österberg](https://github.com/eosterberg)

### License ###

This project is licensed under the [BSD 3-Clause License](./LICENSE)
