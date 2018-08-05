# Shell

### Syntax ###
```
<program> ::= <block> "END"
<block> ::= [ <statement> ]*
<statement> ::= <IF> | <WHILE> | <LOOP> | <REPEAT> | <FOR> | <DO> | <BREAK> | <assignment>
<IF> ::= "IF" <b-expression> <block> [ "ELSE" <block> ] "ENDIF"
<WHILE> ::= "WHILE" <b-expression> <block> "ENDWHILE"
<LOOP> ::= "LOOP" <block> "ENDLOOP"
<REPEAT> ::= "REPEAT" <block> "UNTIL" <b-expression>
<FOR> ::= "FOR" <name> "=" <expression> <expression> <block> "ENDFOR"
<DO> ::= "DO" <expression> <block> "ENDDO"
<BREAK> ::= "BREAK"

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
<number> ::= <digit> [ <digit> ]*
```

### Credits ###

terminal.js is a modified version [terminaljs](https://github.com/eosterberg/terminaljs) by [Erik Österberg](https://github.com/eosterberg)

### License ###

This project is licensed under the [BSD 3-Clause License](./LICENSE)
