#pragma once

#include<iostream>
#include<string>

// 所有 AST 的基类
class BaseAST {
public:
    virtual ~BaseAST() = default;

  virtual void Dump() const = 0;
};

class CompUnitAST : public BaseAST {
public:
    std::unique_ptr<BaseAST> func_def;

    void Dump() const override {
        func_def->Dump();
    }
};

class FuncDefAST : public BaseAST {
public:
    std::unique_ptr<BaseAST> func_type;
    std::string ident;
    std::unique_ptr<BaseAST> block;

    void Dump() const override {
        std::cout << "fun @";
        std::cout << ident << "(): ";
        func_type->Dump();
        std::cout << " {" << std::endl;
        block->Dump();
        std::cout << "}" << std::endl;
    }
};

class FuncTypeAST : public BaseAST {
public:
    std::string type;

    void Dump() const override {
        std::cout << type;
    }
};

class BlockAST : public BaseAST {
public:
    std::unique_ptr<BaseAST> stmt;

    void Dump() const override {
        std::cout << "%entry:" << std::endl;
        stmt->Dump();
    }
};

class StmtAST : public BaseAST {
public:
    int number;

    void Dump() const override {
        std::cout << "  ret ";
        std::cout << number << std::endl;
    }
};