#include "cradle.h"
#include "bool.h"
#include "expr.h"

//Recognize and Translate a Relational "Equals"
void Equals(){
    Match('=');
    Expression();
    PopCompare();
    SetEqual();
}

//Recognize and Translate a Relational "Nat Equals"
void NotEquals(){
    Match('#');
    Expression();
    PopCompare();
    SetNEqual();
}

//Recognize and Translate a Relational "Less Than"
void Less(){
    Match('<');
    Expression();
    PopCompare();
    SetLess();
}

//Recognize and Translate a Relational "Greater Than"
void Greater(){
    Match('>');
    Expression();
    PopCompare();
    SetGreater();
}

//Parse and Translate a Relation
//<relation> ::= <expression> [<relop> <expression>]
//<relop> ::= "=" | "#" | "<" | ">"
void Relation(){
    Expression();
    if (IsRelop(Look)){
        Push();
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
        Emit("TST D0\n"); //FIXME (?)
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
        if (GetBoolean()) SetTrue();
        else SetFalse();
    }else{
        Relation();
    }

    if (neg) NotIt();
}

//Parse and Translate a Boolean Term
//<b-term> ::= <b-notfactor> ["&" <b-notfactor>]*
void BoolTerm(){
    BoolFactor();
    while (Look == '&'){
        Push();
        Match('&');
        BoolFactor();
        PopAnd();
    }
}

//Recognize and Translate a Boolean OR
void BoolOr(){
    Match('|');
    BoolTerm();
    PopOr();
}

//Recognize and Translate a Boolean XOR
void BoolXor(){
    Match('~');
    BoolTerm();
    PopXor();
}

//Parse and Translate a Boolean Expression
//<b-expression> ::= <b-term> [<orop> <b-term>]*
//<orop> ::= "OR" | "XOR"
void BoolExpression(){
    BoolTerm();
    while (IsOrop(Look)){
        Push();
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
