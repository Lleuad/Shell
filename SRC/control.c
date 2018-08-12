#include "cradle.h"
#include "control.h"
#include "bool.h"
#include "expr.h"
#include "scanner.h"

//Recognize and Translate an "Other"
void Other(){
    GetName();
    Emit("%s\n", Value);
}

//Recognize and Translate an IF Construct
//<IF-statement> ::= IF <condition> <block> ["ELSE" <block>] "ENDIF"
void DoIf(char *L){
    char* L1;
    char* L2;
    BoolExpression();
    L1 = NewLabel();
    L2 = NULL;
    BranchFalse(L);
    Block(L);
    if (Token == 'L') {
        L2 = NewLabel();
        Branch(L);
        PostLabel(L1);
        Block(L);
    }
    MatchString("ENDIF");
    PostLabel(L2 ? L2 : L1);
    free(L1);
    free(L2);
}

//Recognize and Translate a WHILE Construct
//<WHILE-statement> ::= "WHILE" <condition> <block> "ENDWHILE"
void DoWhile(){
    char *L1, *L2;
    L1 = NewLabel();
    L2 = NewLabel();
    PostLabel(L1);
    BoolExpression();
    BranchFalse(L2);
    Block(L2);
    MatchString("ENDWHILE");
    Branch(L1);
    PostLabel(L2);
    free(L1);
    free(L2);
}

//Recognize and Translate a LOOP Construct
//<LOOP-statement> ::= "LOOP" <block> "ENDLOOP"
void DoLoop(){
    char *L1, *L2;
    L1 = NewLabel();
    L2 = NewLabel();
    PostLabel(L1);
    Block(L2);
    MatchString("ENDLOOP");
    Branch(L1);
    PostLabel(L2);

    free(L1);
    free(L2);
}

//Recognize and Translate a REPEAT Construct
//<REPEAT-statement> ::= "REPEAT" <block> "UNTIL" <condition>
void DoRepeat(){
    char *L1, *L2;
    L1 = NewLabel();
    L2 = NewLabel();
    PostLabel(L1);
    Block(L2);
    MatchString("UNTIL");
    BoolExpression();
    Branch(L1);
    PostLabel(L2);

    free(L1);
    free(L2);
}

//Recognize and Translate a FOR Construct
//<FOR-statement> ::= "FOR" <name> "=" <expr1> <expr2> <block> "ENDFOR"
void DoFor(){
    char *L1, *L2, *Name;
    if (!(Name = malloc(ValueSize * sizeof (char)))) MemError();
    L1 = NewLabel();
    L2 = NewLabel();
    GetName();
    strcpy(Name, Value);

    Match('=');
    Expression();
    Emit("SUBQ #1, D0\n");
    Store(Name);
    Expression();
    Push();
    PostLabel(L1);
    LoadVar(Name);
    Emit("ADDQ #1, D0\n");
    Store(Name):
    Emit("CMP (SP), D0\n");
    Emit("BGT %s\n", L2);
    Block(L2);
    MatchString("ENDFOR");
    Branch(L1);
    PostLabel(L2);
    Emit("ADDQ #2, SP\n");

    free(L1);
    free(L2);
    free(Name);
}

//Recognize and Translate a DO Construct
//<DO-statement> ::= "DO" <expr> <block> "ENDDO"
void DoDo(){
    char *L1, *L2;
    L1 = NewLabel();
    L2 = NewLabel();
    Expression();
    Emit("SUBQ #1, D0\n");
    PostLabel(L1);
    Push();
    Block(L2);
    MatchString("ENDDO");
    Emit("MOVE (SP)+, D0\n");
    Emit("DBRA D0, %s\n", L1);
    Emit("SUBQ #2, SP\n");
    PostLabel(L2);
    Emit("ADDQ #2, SP\n");

    free(L1);
    free(L2);
}

//Recognize and Translate a BREAK Statement
//<BREAK-statement> ::= "BREAK"
void DoBreak(char *L){
    if (L) Branch(L);
    else Abort("Can't break from global scope");
}

//Recognize and Translate a Statement Block
//<block> ::= [ <statement> ]*
void Block(char *L){
    Scan();
    while ( !(Token == 'E' || Token == 'L' || Token == 'U') ){
        switch (Token) {
            case 'I':
                DoIf(L);
                break;
            case 'W':
                DoWhile();
                break;
            case 'P':
                DoLoop();
                break;
            case 'R':
                DoRepeat();
                break;
            case 'F':
                DoFor();
                break;
            case 'D':
                DoDo();
                break;
            case 'B':
                DoBreak(L);
                break;
            default:
                Assignment();
                break;
        }
        Scan();
    }
}

//Parse and Translate a Program
//<program> ::= <block> END
void DoProgram(){
    Block(NULL);
    MatchString("END");
    Emit("END\n");
}
