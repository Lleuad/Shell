#ifndef CONTROLE_H_
#define CONTROLE_H_

void Other(void);      //Recognize and Translate an "Other"
void DoIf(char *);     //Recognize and Translate an IF Construct
void DoWhile(void);    //Recognize and Translate an WHILE Construct
void DoLoop(void);     //Recognize and Translate an LOOP Construct
void DoRepeat(void);   //Recognize and Translate an REPEAT Construct
void DoFor(void);      //Recognize and Translate an REPEAT Construct
void DoDo(void);       //Recognize and Translate a DO Construct
void DoBreak(char *);  //Recognize and Translate a BREAK Statement
void Block(char *);    //Recognize and Translate a Statement Block
void DoProgram(void);  //Parse and Translate a Program

#endif//CONTROLE_H_
