#include "cradle.h"
#include "bool.h"
#include "expr.h"

//Recognize and Translate a Relational "Equals"
void Equals(){
    Match('=');
    Expression();
    Emit("CMP (SP)+, D0\n");
    Emit("SEQ D0\n");
}

//Recognize and Translate a Relational "Nat Equals"
void NotEquals(){
    Match('#');
    Expression();
    Emit("CMP (SP)+, D0\n");
    Emit("SNE D0\n");
}

//Recognize and Translate a Relational "Less Than"
void Less(){
    Match('<');
    Expression();
    Emit("CMP (SP)+, D0\n");
    Emit("SGE D0\n");
}

//Recognize and Translate a Relational "Greater Than"
void Greater(){
    Match('>');
    Expression();
    Emit("CMP (SP)+, D0\n");
    Emit("SLE D0\n");
}

//Parse and Translate a Relation
//<relation> ::= <expression> [<relop> <expression>]
//<relop> ::= "=" | "#" | "<" | ">"
void Relation(){
    Expression();
    if (IsRelop(Look)){
        Emit("MOVE D0, -(SP)\n");
        switch (Look){
            case '=':
                Equals();
                break;
            case '#':
                NotEquals();
                break;
            case '<':
                Less();
                break;
            case '>':
                Greater();
                break;
        }
        Emit("TST D0\n");
    }
}

//Parse and Translate a Boolean Factor
//<b-notfactor> :: ["!"] <b-factor>
//<b-factor> ::= <b-literal> | <relation>
void BoolFactor(){
    int neg = 0;
    if (Look == '!'){
        Match('!');
        neg = 1;
    }

    if (IsBoolean(Look)) {
        if (GetBoolean()) Emit("MOVE #-1, D0\n");
        else Emit("CLR D0\n");
    }else{
        Relation();
    }

    if (neg) Emit("EOR #-1, D0\n");
}

//Parse and Translate a Boolean Term
//<b-term> ::= <b-notfactor> ["&" <b-notfactor>]*
void BoolTerm(){
    BoolFactor();
    while (Look == '&'){
        Emit("MOVE D0, -(SP)\n");
        Match('&');
        BoolFactor();
        Emit("AND (SP)+, D0\n");
    }
}

//Recognize and Translate a Boolean OR
void BoolOr(){
    Match('|');
    BoolTerm();
    Emit("OR (SP)+, D0\n");
}

//Recognize and Translate a Boolean XOR
void BoolXor(){
    Match('~');
    BoolTerm();
    Emit("EOR (SP)+, D0\n");
}

//Parse and Translate a Boolean Expression
//<b-expression> ::= <b-term> [<orop> <b-term>]*
//<orop> ::= "OR" | "XOR"
void BoolExpression(){
    BoolTerm();
    while (IsOrop(Look)){
        Emit("MOVE D0, -(SP)\n");
        switch (Look){
            case '|':
                BoolOr();
                break;
            case '~':
                BoolXor();
                break;
        }
    }
}
