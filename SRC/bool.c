#include "cradle.h"
#include "bool.h"
#include "expr.h"

void Equals(){
    DEBUG;
    Next();
    Expression();
    PopCompare();
    SetEqual();
    DEBUGRET;
}

void Less(){
    DEBUG;
    Next();
    if (Token == '=') {
        Next();
        Expression();
        PopCompare();
        SetLessOrEqual();
    } else if (Token == '>') {
        Next();
        Expression();
        PopCompare();
        SetNEqual();
    } else {
        Expression();
        PopCompare();
        SetLess();
    }
    DEBUGRET;
}

void Greater(){
    DEBUG;
    Next();
    if (Token == '=') {
        Next();
        Expression();
        PopCompare();
        SetGreaterOrEqual();
    } else {
        Expression();
        PopCompare();
        SetGreater();
    }
    DEBUGRET;
}

//<relation> ::= <expression> [<relop> <expression>]
//<relop> ::= "=" | "<" | ">" | "<>" | "<=" | ">="
void Relation(){
    DEBUG;
    Expression();
    if (IsRelop(Token)){
        Push();
        switch (Token){
            case '=':
                Equals();
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
    DEBUGRET;
}

//Parse and Translate a Boolean Factor
//<b-notfactor> :: ["!"] <b-factor>
//<b-factor> ::= <b-literal> | <relation>
void BoolFactor(){
    DEBUG;
    int neg = 0;
    if (Token == '!'){
        Next();
        neg = 1;
    }

    if (IsBoolean(Token)) {
        if (GetBoolean()) SetTrue();
        else SetFalse();
    }else{
        Relation();
    }

    if (neg) NotIt();
    DEBUGRET;
}

//Parse and Translate a Boolean Term
//<b-term> ::= <b-notfactor> ["&" <b-notfactor>]*
void BoolTerm(){
    DEBUG;
    BoolFactor();
    while (Token == '&'){
        Push();
        Next();
        BoolFactor();
        PopAnd();
    }
    DEBUGRET;
}

//Recognize and Translate a Boolean OR
void BoolOr(){
    DEBUG;
    Next();
    BoolTerm();
    PopOr();
    DEBUGRET;
}

//Recognize and Translate a Boolean XOR
void BoolXor(){
    DEBUG;
    Next();
    BoolTerm();
    PopXor();
    DEBUGRET;
}

//Parse and Translate a Boolean Expression
//<b-expression> ::= <b-term> [<orop> <b-term>]*
//<orop> ::= "OR" | "XOR"
void BoolExpression(){
    DEBUG;
    BoolTerm();
    while (IsOrop(Token)){
        Push();
        switch (Token){
            case '|':
                BoolOr();
                break;
            case '~':
                BoolXor();
                break;
        }
    }
    DEBUGRET;
}
