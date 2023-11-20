
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
static std::unique_ptr<IRBuilder<>> Builder;
static std::unique_ptr<Module> TheModule;
//static std::map<std::string, Value *> NamedValues;

void InitializeModule() {
  TheContext = std::make_unique<LLVMContext>();
  TheModule = std::make_unique<Module>("TheModule", *TheContext);
  Builder = std::make_unique<IRBuilder<>>(*TheContext);

  Type* D = Type::getDoubleTy(*TheContext);
  std::vector<Type*> Nil;
  FunctionType *FT = FunctionType::get(D,Nil,false);
  GlobalValue::LinkageTypes L = Function::ExternalLinkage;
  Function* F = Function::Create(FT,L,"TheFunction",TheModule.get());
  BasicBlock *BB = BasicBlock::Create(*TheContext, "Entry", F);
  Builder->SetInsertPoint(BB);
}

void MakeTopLevel(llvm::Value* v) {
  Builder->CreateRet(v);
}

void DumpCode() {
  TheModule->print(errs(), nullptr);
}

Value* Num::codegen() {
  float f = num;
  return ConstantFP::get(*TheContext, APFloat(f)); // TODO: int!
}

Value* Sub::codegen() {
  auto L = left->codegen();
  auto R = right->codegen();
  auto res = Builder->CreateFSub(L, R, "subtmp");
  return res;
}
