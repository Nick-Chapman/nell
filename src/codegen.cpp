
#include "misc.h"
#include "ast.h"
#include <map>
#include "misc.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

using namespace llvm;

// TODO: use own context instead of globals
static up<LLVMContext> TheContext;
static up<IRBuilder<>> Builder;
static std::map<std::string, Value *> NamedValues; // meh
static up<Module> TheModule;

Value* Var::codegen() {
  Value* res = NamedValues[VarName]; // meh
  if (!res) {
    printf("No such variable: %s\n",VarName.c_str());
    crash
  }
  return res;
}

Value* Num::codegen() {
  return ConstantInt::get(*TheContext, APInt(16,NumValue));
}

Value* Mul::codegen() {
  auto L = MulLeft->codegen();
  auto R = MulRight->codegen();
  auto res = Builder->CreateMul(L, R, "multmp");
  return res;
}

Value* Add::codegen() {
  crash
}

Value* Sub::codegen() {
  auto L = SubLeft->codegen();
  auto R = SubRight->codegen();
  auto res = Builder->CreateSub(L, R, "subtmp");
  return res;
}

Value* LessThan::codegen() {
  crash
}

Value* Ite::codegen() {
  crash
}

Value* Call::codegen() {
  crash
}

void Def::codegen() {

  Type* T = Type::getInt16Ty(*TheContext); // everything is an int!
  Type* retType = T;
  std::vector<Type*> ArgTypes;
  for (unsigned i=0; i < DefFormals.size(); i++) {
    ArgTypes.push_back(T);
  }

  FunctionType *FT = FunctionType::get(retType,ArgTypes,false);
  GlobalValue::LinkageTypes L = Function::ExternalLinkage;
  Function* F = Function::Create(FT,L,DefName,TheModule.get());
  BasicBlock *BB = BasicBlock::Create(*TheContext, "Entry", F);
  Builder->SetInsertPoint(BB);

  int i = 0;
  for (auto &Arg : F->args()) {
    Name name = DefFormals[i];
    i++;
    NamedValues[name] = &Arg; //meh
    Arg.setName(name);
  }

  llvm::Value* v = DefBody->codegen();
  Builder->CreateRet(v);
}

static void Init() {
  TheContext = mk<LLVMContext>();
  TheModule = mk<Module>("TheModule", *TheContext);
  Builder = mk<IRBuilder<>>(*TheContext);
}

// entry point...
void codegen(Prog& prog) {
  Init(); // TODO: Use context param
  for (auto &def : prog.ProgDefs) {
    //printf("gen for: %s\n",def->DefName.c_str());
    def->codegen();
  }
  // TODO: ProgMain
  if (!TheModule) {
    printf("DumpCode: no module!\n");
    crash
  }
  TheModule->print(errs(), nullptr);
}
