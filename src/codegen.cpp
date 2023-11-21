
#include "misc.h"
#include "ast.h"
#include <map>
#include "misc.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"

using namespace llvm;

struct TopCon {
  LLVMContext& context;
  IRBuilder<>& builder;
  Module& module;
};

struct DefCon {
  TopCon& top;
  Function* function;
  std::map<std::string, Value *> args;
};

Value* Var::codegen(DefCon& con) {
  Value* res = con.args[VarName];
  if (!res) {
    printf("No such variable: %s\n",VarName.c_str());
    crash
  }
  return res;
}

Value* Num::codegen(DefCon& con) {
  return ConstantInt::get(con.top.context, APInt(16,NumValue));
}

Value* Mul::codegen(DefCon& con) {
  auto L = MulLeft->codegen(con);
  auto R = MulRight->codegen(con);
  return con.top.builder.CreateMul(L, R, "mul-tmp");
}

Value* Add::codegen(DefCon& con) {
  auto L = AddLeft->codegen(con);
  auto R = AddRight->codegen(con);
  return con.top.builder.CreateAdd(L, R, "add-tmp");
}

Value* Sub::codegen(DefCon& con) {
  auto L = SubLeft->codegen(con);
  auto R = SubRight->codegen(con);
  return con.top.builder.CreateSub(L, R, "sub-tmp");
}

Value* LessThan::codegen(DefCon& con) {
  auto L = LessThanLeft->codegen(con);
  auto R = LessThanRight->codegen(con);
  return con.top.builder.CreateICmpULT(L, R, "lt-tmp");
}

Value* Ite::codegen(DefCon& con) {
  auto& context = con.top.context;
  auto& builder = con.top.builder;

  BasicBlock* ThenBB = BasicBlock::Create(context, "bthen", con.function);
  BasicBlock* ElseBB = BasicBlock::Create(context, "belse", con.function);
  BasicBlock* MergeBB = BasicBlock::Create(context, "bmerge", con.function);

  auto Cond = IteCond->codegen(con);
  builder.CreateCondBr(Cond,ThenBB,ElseBB);

  builder.SetInsertPoint(ThenBB);
  auto Then = IteThen->codegen(con);
  builder.CreateBr(MergeBB);

  builder.SetInsertPoint(ElseBB);
  auto Else = IteElse->codegen(con);
  builder.CreateBr(MergeBB);

  builder.SetInsertPoint(MergeBB);
  Type* Ty = Type::getInt16Ty(context);
  PHINode* Phi = builder.CreatePHI(Ty, 2, "merged");
  Phi->addIncoming(Then, ThenBB);
  Phi->addIncoming(Else, ElseBB);
  return Phi;
}

Value* Call::codegen(DefCon& con) {
  auto& builder = con.top.builder;
  Function* callee = con.top.module.getFunction(CallFunc);
  if (!callee) {
    printf("No such function: %s\n",CallFunc.c_str());
    crash
  }
  if (callee->arg_size() != CallArgs.size()) {
    printf("call-to(%s) #formals=%zu, #actuals=%zu\n",
           CallFunc.c_str(), callee->arg_size(), CallArgs.size());
    crash
  }
  std::vector<Value*> actuals;
  for (auto &arg : CallArgs) {
    actuals.push_back(arg->codegen(con));
  }
  return builder.CreateCall(callee, actuals, "call-tmp");
}

void Def::declare(TopCon& top) {
  Type* T = Type::getInt16Ty(top.context); // everything is an int!
  Type* retType = T;
  std::vector<Type*> ArgTypes;
  for (unsigned i=0; i < DefFormals.size(); i++) {
    ArgTypes.push_back(T);
  }
  FunctionType *FT = FunctionType::get(retType,ArgTypes,false);
  GlobalValue::LinkageTypes L = Function::ExternalLinkage;
  Function::Create(FT,L,DefName,top.module);
}

void Def::codegen(TopCon& top) {
  Function* function = top.module.getFunction(DefName);
  BasicBlock *BB = BasicBlock::Create(top.context, "Entry", function);
  top.builder.SetInsertPoint(BB);
  std::map<std::string, Value*> args;
  DefCon con { top, function, args };
  int i = 0;
  for (auto &Arg : function->args()) {
    Name name = DefFormals[i];
    i++;
    con.args[name] = &Arg;
    Arg.setName(name);
  }
  llvm::Value* v = DefBody->codegen(con);
  con.top.builder.CreateRet(v);
  verifyFunction(*function);
}

// entry point...
void codegen(Prog& prog) {
  LLVMContext context;
  IRBuilder<> builder(context);
  Module module("TheModule", context);
  TopCon top = { context, builder, module };
  for (auto &def : prog.ProgDefs) {
    def->declare(top);
  }
  for (auto &def : prog.ProgDefs) {
    def->codegen(top);
  }
  // dump...
  module.print(errs(), nullptr);
}
