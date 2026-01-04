#pragma once

#include<iostream>
#include<string>
#include<sstream>
#include <memory>

// 所有 AST 的基类
class BaseAST {
public:
    virtual ~BaseAST() = default;
    
    virtual void Dump(std::ostringstream &ost) const = 0;
};

class CompUnitAST : public BaseAST {
public:
    std::unique_ptr<BaseAST> func_def;

    void Dump(std::ostringstream &ost) const override {
        func_def->Dump(ost);
    }
};

class FuncDefAST : public BaseAST {
public:
    std::unique_ptr<BaseAST> func_type;
    std::string ident;
    std::unique_ptr<BaseAST> block;

    void Dump(std::ostringstream &ost) const override {
        ost << "fun @";
        ost << ident << "(): ";
        func_type->Dump(ost);
        ost << " {" << std::endl;
        block->Dump(ost);
        ost << "}" << std::endl;
    }
};

class FuncTypeAST : public BaseAST {
public:
    std::string type;

    void Dump(std::ostringstream &ost) const override {
        ost << type;
    }
};

class BlockAST : public BaseAST {
public:
    std::unique_ptr<BaseAST> stmt;

    void Dump(std::ostringstream &ost) const override {
        ost << "%entry:" << std::endl;
        stmt->Dump(ost);
    }
};

class StmtAST : public BaseAST {
public:
    int number;

    void Dump(std::ostringstream &ost) const override {
        ost << "  ret ";
        ost << number << std::endl;
    }
};