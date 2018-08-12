# Shell

### Syntax ###
```
<program> ::= <block> "END"
<block> ::= [ [ <CR> ]* <statement> [ <CR> ]* ]*
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
<relop> ::= "=" | "<" | ">" | "<>" | "<=" | ">="

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
<alnum> ::= <alpha> | <digit>
<digit> ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
<alpha> ::= "A" | "B" | "C" | "D" | "E" | "F" | "G" | "H" | "I" |
            "J" | "K" | "L" | "M" | "N" | "O" | "P" | "Q" | "R" |
            "S" | "T" | "U" | "V" | "W" | "X" | "Y" | "Z"
<CR> ::= "\n" | "\r"
```
Even though it is good practice to use whitespace to increase readability it is techically only required to separate a `<name>` sequence from another or from a `<number>`. For instance; `IF0=0` is an assignment of `0` to a variable named `IF0` whereas `IF 0=0` is the start of an if-statement testing the equallity of `0` to itself. On the otherhand `IF!a=0a=0ENDIF` is perfectly valid code that assigns `0` to a variable `a` if it isn't `0` already.

### Credits ###

terminal.js is a modified version [terminaljs](https://github.com/eosterberg/terminaljs) by [Erik Österberg](https://github.com/eosterberg)

### License ###

This project is licensed under the [BSD 3-Clause License](./LICENSE)
