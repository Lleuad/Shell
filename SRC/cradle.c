#include "cradle.h"

//Report Error and Halt
void Abort(const char* s){
    Error(s);
    exit(1);
}

//Report What Was Expected
void Expected_s(const char* s){
    fprintf(stderr, "Error: Got '%c', Expected %s.\n", Token, s);
    exit(1);
}

void Expected_c(char c){
    fprintf(stderr, "Error: Got '%c', '%c' Expected.\n", Token, c);
    exit(1);
}

//Skip Over a Comma
void SkipComma(){
    SkipWhite();
    if ( Look == ',' ){
        GetChar();
        SkipWhite();
    }
}

void Match(char x){
    if ( !(Token == x) ) Expected(x);
    Next();
}

void MatchString(const char* s){
    if (strcmp(Value, s)) Expected(s);
    Next();
}

void Next(){
    SkipWhite();
    if ( IsAlpha(Look) ) GetName();
    else if ( IsDigit(Look) ) GetNum();
    else if ( IsOp(Look) ) GetOp();
    else {
        Value[0] = Look;
        Value[1] = 0;
        Token = Look;
        GetChar();
    }
}

void GetName(){
    size_t i;
    for (i = 0; IsAlNum(Look); i++, GetChar()){
        Value[i] = (char)toupper(Look);
        if (i == ValueSize){
            ValueSize <<= 1;
            if (!(Value = realloc(Value, ValueSize * sizeof (char)))) MemError();
       }
    }
    Value[i] = 0;
    Token = 'x';
}

void GetNum(){
    size_t i;
    for (i = 0; IsDigit(Look); i++, GetChar()){
        Value[i] = Look;
        if (i == ValueSize){
            ValueSize <<= 1;
            if (!(Value = realloc(Value, ValueSize * sizeof (char)))) MemError();
       }
    }
    Value[i] = 0;
    Token = '#';
}

void GetOp(){
#if 0
    size_t i;
    for (i = 0; IsOp(Look); i++, GetChar()){
        Value[i] = Look;
        if (i == ValueSize){
            ValueSize <<= 1;
            if (!(Value = realloc(Value, ValueSize * sizeof (char)))) MemError();
       }
    }
    Value[i] = 0;
    Token = Value[0];
#endif //0
    Token = Look;
    Value[0] = Look;
    Value[1] = 0;
    GetChar();
}

//Get a Boolean Literal
int GetBoolean(){
    int bool;
    if (!IsBoolean(Look)) Expected("Boolean Literal");
    bool = (toupper(Look) == 'T');
    GetChar();
    SkipWhite();
    return bool;
}

//Generate a Unique Label
char* NewLabel(){
    char* Label;
    if ( !(Label = malloc(2 + 2*sizeof Lcount)) ) MemError();
    sprintf(Label, "L%X", Lcount++);
    if (!Lcount) Abort("Lcount overflow");
    return Label;
}

//Output a String with Tab
void Emit(const char* fmt, ...){
    va_list vlist;
    va_start(vlist, fmt);

    fprintf(stdout, "%c", TAB);
    vfprintf(stdout, fmt, vlist);

    va_end(vlist);
}

//Initialize
void Init(){
    #ifdef DEBUGGING
    DEBUGCOUNT = 0;
    #endif //DEBUGGING
    Lcount = 0;
    Value = malloc(TOKENSIZE * sizeof (char));
    ValueSize = TOKENSIZE;
    GetChar();
}

