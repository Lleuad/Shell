#include "cradle.h"
#include "expr.h"
#include "bool.h"

//Parse and Translate an Identifier
//<ident> ::= <function> "()" | <variable>
void Ident(){
    DEBUG;
    char *Name;
    if (!(Name = malloc(ValueSize * sizeof (char)))) MemError();
    strcpy(Name, Value);

    Next();
    if (Token == '('){
        Match('(');
        Match(')');
        FuncCall(Name);
    }else{
        LoadVar(Name);
    }
    DEBUGRET;
}

//Parse and Translate a Math Factor
//<factor> ::= [<addop>] <unsigned-factor>
//<unsigned-factor> :: = "(" <expression> ")" | <ident> | <number>
void Factor(){
    DEBUG;
    int neg = 0;

    switch (Token){
        case '+':
            Next();
            break;
        case '-':
            Next();
            neg = 1;
            break;
    }

    if (Token == '('){
        Next();
        Expression();
        Match(')');
    } else if ( (Token = 'x') ) {
        Ident();
    } else if ( (Token = '#') ) {
        LoadConst(Value);
        Next();
    } else {
        Expected("Math Factor");
    }

    if (neg) Negate();
    DEBUGRET;
}

//Recognize and Translate a Multiply
void Multiply(){
    DEBUG;
    Next();
    Factor();
    PopMul();
    DEBUGRET;
}

//Recognize and Translate a Divide
void Divide(){
    DEBUG;
    Next();
    Factor();
    PopDiv();
    DEBUGRET;
}

//Parse and Translate a Math Term
//<term> ::= <factor> [ <mulop> <factor> ]*
//<mulop> ::= "*" | "/"
void Term(){
    DEBUG;
    Factor();

    while ( IsMulop(Token) ){
        Push();
        switch (Token){
            case '*':
                Multiply();
                break;
            case '/':
                Divide();
                break;
        }
    }
    DEBUGRET;
}

//Recognize and Translate an Add
void Add(){
    DEBUG;
    Next();
    Term();
    PopAdd();
    DEBUGRET;
}

//Recognize and Translate a Subtract
void Subtract(){
    DEBUG;
    Next();
    Term();
    PopSub();
    DEBUGRET;
}

//Parse and Translate an Expression
//<expression> ::= <term> [ <addop> <term> ]*
//<addop> ::= "+" | "-"
void Expression(){
    DEBUG;
    Term();

    while ( IsAddop(Token) ){
        Push();
        switch (Token){
            case '+':
                Add();
                break;
            case '-':
                Subtract();
                break;
        }
    }
    DEBUGRET;
}

//Parse and Translate an Assignment Statement
//<assignment> ::= <ident> "=" <expression>
void Assignment(){
    DEBUG;
    char *Name;
    if (!(Name = malloc(ValueSize * sizeof (char)))) MemError();
    strcpy(Name, Value);

    Next();
    Match('=');
    BoolExpression();
    Store(Name);
    free(Name);
    DEBUGRET;
}
