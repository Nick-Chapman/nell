
#include "ast.h"
#include <map>
#include "misc.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

using namespace llvm;

// TODO: move to own context type instead of top level statics
static std::unique_ptr<LLVMContext> TheContext;
static std::unique_ptr<IRBuilder<>> Builder;
static std::unique_ptr<Module> TheModule;
static std::map<std::string, Value *> NamedValues;

void InitializeModule() {
  TheContext = std::make_unique<LLVMContext>();
  TheModule = std::make_unique<Module>("TheModule", *TheContext);
  Builder = std::make_unique<IRBuilder<>>(*TheContext);

  // TODO: drive function codegen from AST
  Type* D = Type::getInt16Ty(*TheContext);
  std::vector<Type*> ArgTypes;

  // setup 2 function inputs
  ArgTypes.push_back(D);
  ArgTypes.push_back(D);

  FunctionType *FT = FunctionType::get(D,ArgTypes,false);
  GlobalValue::LinkageTypes L = Function::ExternalLinkage;
  Function* F = Function::Create(FT,L,"TheFunction",TheModule.get());
  BasicBlock *BB = BasicBlock::Create(*TheContext, "Entry", F);
  Builder->SetInsertPoint(BB);

  int i = 0;
  for (auto &Arg : F->args()) {
    i++;
    std::string name = "xx" + std::to_string(i);
    //printf("making input: %d, %s\n",i,name.c_str());
    NamedValues[name] = &Arg;
    Arg.setName(name);
  }
}

void MakeTopLevel(llvm::Value* v) {
  Builder->CreateRet(v);
}

void DumpCode() {
  TheModule->print(errs(), nullptr);
}


Value* Var::codegen() {
  Value* res = NamedValues[name];
  if (!res) {
    printf("No such variable: %s\n",name.c_str());
    crash
  }
  return res;
}

Value* Num::codegen() {
  return ConstantInt::get(*TheContext, APInt(16,num));
}

Value* Sub::codegen() {
  auto L = left->codegen();
  auto R = right->codegen();
  auto res = Builder->CreateSub(L, R, "subtmp");
  return res;
}
