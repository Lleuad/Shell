#ifndef PRIMATIVE_H_
#define PRIMATIVE_H_

void Clear(void); //Clear Primary Register
void Negate(void); //Negate Primary Register
void LoadConst(char *); //Load Constant to Primary Register
void LoadVar(char *); //Load Variable to Primary Register
void Push(void); //Push Primary onto Stack
void PopAdd(void); //Add Top of Stack to Primary
void PopSub(void); //Subtract Top of Stack from Primary
void PopMul(void); //Multiply Top of Stack by Primary
void PopDiv(void); //Divide Top of Stack by Primary
void Store(char *); //Stare Primary to Variable
void FuncCall(char *); //Call Function

void NotIt() //Complement Primary Register
void PopAnd() //AND Top of Stack with Primary
void PopOr() //OR Top of Stack with Primary
void PopXor() //XOR Top of Stack with Primary
void PopCompare() //Compare Top of Stack with Primary
void SetEqual() //Set D0 If Compare was =
void SetNEqual() //Set D0 If Compare was !=
void SetGreater() //Set D0 If Compare was >
void SetLess() //Set D0 If Compare was <

void SetTrue(); //Set D0 to True
void SetFalse(); //Set D0 to False
void Branch(char *L); //Branch Unconditional
void BranchFalse(char *L); //Branch False

#define Undefined(s) Abort("Undefined Identifier %s")
#define InTable(s) 1

#endif //PRIMATIVE_H_
