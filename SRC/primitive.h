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

void NotIt(void); //Complement Primary Register
void PopAnd(void); //AND Top of Stack with Primary
void PopOr(void); //OR Top of Stack with Primary
void PopXor(void); //XOR Top of Stack with Primary
void PopCompare(void); //Compare Top of Stack with Primary
void SetEqual(void); //Set D0 If Compare was =
void SetNEqual(void); //Set D0 If Compare was !=
void SetGreater(void); //Set D0 If Compare was >
void SetGreaterOrEqual(void); //Set D0 If Compare was >=
void SetLess(void); //Set D0 If Compare was <
void SetLessOrEqual(void); //Set D0 If Compare was <=

void SetTrue(void); //Set D0 to True
void SetFalse(void); //Set D0 to False
void Branch(char *L); //Branch Unconditional
void BranchFalse(char *L); //Branch False

#define Undefined(s) Abort("Undefined Identifier %s")
#define InTable(s) 1

#endif //PRIMATIVE_H_
