
#include "ast.h"
#include "misc.h"

// #include "llvm/ADT/APFloat.h"
// #include "llvm/ADT/STLExtras.h"
// #include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
// #include "llvm/IR/DerivedTypes.h"
// #include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
// #include "llvm/IR/Type.h"
// #include "llvm/IR/Verifier.h"

using namespace llvm;

//typedef IRBuilder<> BuilderT; //TODO: helpful?

static std::unique_ptr<LLVMContext> TheContext;
static std::unique_ptr<IRBuilder<>> Builder; //(TheContext); // TODO!
static std::unique_ptr<Module> TheModule;
//static std::map<std::string, Value *> NamedValues;

void InitializeModule() {
  TheContext = std::make_unique<LLVMContext>();
  TheModule = std::make_unique<Module>("my-module", *TheContext);
  Builder = std::make_unique<IRBuilder<>>(*TheContext);
}

void DumpCode() {
  printf("**DumpCode...\n");
  TheModule->print(errs(), nullptr);
  printf("**DumpCode...DONE\n");
}

Value* Num::codegen() {
  float f = num;
  return ConstantFP::get(*TheContext, APFloat(f)); // TODO: int!
}

Value* Sub::codegen() {
  //crash
  auto L = left->codegen();
  auto R = right->codegen();
  auto res = Builder->CreateFSub(L, R, "subtmp");
  return res;
}
