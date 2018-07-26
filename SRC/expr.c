#include "cradle.h"
#include "expr.h"
#include "bool.h"

//Parse and Translate an Identifier
//<ident> ::= <function> "()" | <variable>
void Ident(){
    char* Name = GetName();
    if (Look == '('){
        Match('(');
        Match(')');
        Emit("BSR %s\n", Name);
    }else{
        Emit("MOVE %s(PC), D0\n", Name);
    }
    free(Name);
}

//Parse and Translate a Math Factor
//<factor> ::= [<addop>] <unsigned-factor>
//<unsigned-factor> :: = "(" <expression> ")" | <ident> | <number>
void Factor(){
    char *Num = NULL;
    int neg = 0;

    switch (Look){
        case '+':
            Match('+');
            break;
        case '-':
            Match('-');
            neg = 1;
            break;
    }

    if (Look == '('){
        Match('(');
        Expression();
        Match(')');
    }else if ( IsAlpha(Look) ){
        Ident();
    }else{
        Num = GetNum();
        Emit("MOVE #%s, D0\n", Num);
    }
    if (neg) Emit("NEG D0\n");
    free(Num);
}

//Recognize and Translate a Multiply
void Multiply(){
    Match('*');
    Factor();
    Emit("MULS (SP)+, D0\n");
}

//Recognize and Translate a Divide
void Divide(){
    Match('/');
    Factor();
    Emit("MOVE (SP)+, D1\n");
    Emit("DIVS D1, D0\n");
}

//Parse and Translate a Math Term
//<term> ::= <factor> [ <mulop> <factor> ]*
//<mulop> ::= "*" | "/"
void Term(){
    Factor();

    while (Look == '*' || Look == '/'){
        Emit("MOVE D0, -(SP)\n");
        switch (Look){
            case '*':
                Multiply();
                break;
            case '/':
                Divide();
                break;
        }
    }
}

//Recognize and Translate an Add
void Add(){
    Match('+');
    Term();
    Emit("ADD (SP)+, D0\n");
}

//Recognize and Translate a Subtract
void Subtract(){
    Match('-');
    Term();
    Emit("SUB (SP)+, D0\n");
    Emit("NEG D0\n");
}

//Parse and Translate an Expression
//<expression> ::= <term> [ <addop> <term> ]*
//<addop> ::= "+" | "-"
void Expression(){
    Term();

    Emit("MOVE D0, -(SP)\n");
    while ( IsAddop(Look) ){
        switch (Look){
            case '+':
                Add();
                break;
            case '-':
                Subtract();
                break;
        }
    }
}

//Parse and Translate an Assignment Statement
//<assignment> ::= <ident> "=" <expression>
void Assignment(){
    char* Name = GetName();
    Match('=');
    BoolExpression();
    Emit("LEA %s(PC), A0\n", Name);
    Emit("MOVE D0, (A0)\n");
    free(Name);
}
