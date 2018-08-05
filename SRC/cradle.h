#ifndef CRADLE_H_
#define CRADLE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

//Constant Declaration
#define TAB '\t'
#define EXP " Expected"
#define TOKENSIZE 8
#define CR '\n'

//Variable Declarations
char Look;           //Lookahead Character
char Token;          //Encoded Token
char* Value;         //Unencoded Token
size_t ValueSize;    //Buffersize of Value
unsigned int Lcount; //Label Counter

//Read New Character From Input Stream
#define GetChar() ( Look = (char)getc(stdin) )

//Report an Error
#define Error(s) fprintf(stderr, "Error: %s.\n", s)
#define MemError() Abort("Insufficient Memory")
#define FileError(s) Abort("%s, no such file")

void Abort(const char* s); //Report Error and Halt

//Report What Was Expected
void Expected_s(const char* s);
void Expected_c(char c);
#define Expected(s) _Generic((s), const char*: Expected_s, char: Expected_c)(s)

//Recognize a Character Set
#define IsAlpha isalpha
#define IsDigit isdigit
#define IsAlNum isalnum
#define IsAddop(c) (c == '+' || c == '-')
#define IsMulop(c) (c == '*' || c == '/')
#define IsWhite(c) (c == ' ' || c == TAB)
#define IsCR(c) (c == CR || c == '\r')
#define IsBoolean(c) (c == 'F' || c == 'T')
#define IsOrop(c) (c == '|' || c == '~')
#define IsRelop(c) (c == '=' || c == '#' || c == '<' || c == '>')
#define IsOp(c) (IsAddop(c) || IsMulop(c) || IsRelop(c))

//Skip White Space
#define SkipWhite() while IsWhite(Look) GetChar()
#define Fin() while IsCR(Look) GetChar()

void SkipComma(void);            //Skip Over a Comma
void Match(char);                //Match a Specific Input Character
void MatchString(const char *);  //Match a Specific Input String
void GetName(void);              //Get an Identifier
void GetNum(void);               //Get a Number
void GetOp(void);                //Get an Operator
int GetBoolean(void);            //Get a Boolean Literal
char* NewLabel(void);            //Generate a Unique Label

//Post a Label To Outpun
#define PostLabel(L) fprintf(stdout, "%s:\n", L)

void Emit(const char* fmt, ...); //Output a String with Tab
void Init(void);                 //Initialize

#endif//CRADLE_H_
