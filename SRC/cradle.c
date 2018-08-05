#include "cradle.h"

//Report Error and Halt
void Abort(const char* s){
    Error(s);
    exit(1);
}

//Report What Was Expected
void Expected_s(const char* s){
    fprintf(stderr, "Error: Got '%c', Expected %s.\n", Look, s);
    exit(1);
}

void Expected_c(char c){
    fprintf(stderr, "Error: Got '%c', '%c' Expected.\n", Look, c);
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

//Match a Specific Input Character
void Match(char x){
    if(Look == x){
        GetChar();
        SkipWhite();
    }else{
        Expected(x);
    }
}

void MatchString(const char* s){
    if (strcmp(Value, s)) Expected(s);
}

//Get an Identifier
void GetName(){
    size_t i;
    Fin();
    if ( !IsAlpha(Look) ) Expected("Name");
    for (i = 0; IsAlNum(Look); i++, GetChar()){
        Value[i] = (char)toupper(Look);
        if (i == ValueSize){
            ValueSize <<= 1;
            if (!(Value = realloc(Value, ValueSize * sizeof (char)))) MemError();
       }
    }
    Value[i] = 0;
    SkipWhite();
}

//Get a Number
void GetNum(){
    size_t i;
    if ( !IsDigit(Look) ) Expected("Integer");
    for (i = 0; IsDigit(Look); i++, GetChar()){
        Value[i] = Look;
        if (i == ValueSize){
            ValueSize <<= 1;
            if (!(Value = realloc(Value, ValueSize * sizeof (char)))) MemError();
       }
    }
    Value[i] = 0;
    Token = '#';
    SkipWhite();
}

void GetOp(){
    size_t i;
    if ( !IsOp(Look) ) Expected("Relation");
    for (i = 0; IsOp(Look); i++, GetChar()){
        Value[i] = Look;
        if (i == ValueSize){
            ValueSize <<= 1;
            if (!(Value = realloc(Value, ValueSize * sizeof (char)))) MemError();
       }
    }
    Value[i] = 0;
    SkipWhite();
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
    char* Label = malloc(2 + 2*sizeof Lcount);
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
    Lcount = 0;
    Value = malloc(TOKENSIZE * sizeof (char));
    ValueSize = TOKENSIZE;
    GetChar();
    SkipWhite();
}

