#pragma once

#include <iostream>
#include <vector>

class AstNode {
public:
    friend std::ostream& operator<<(std::ostream& os, const AstNode& node) {
        node.print(os);
        return os;
    }

protected:
    virtual void print(std::ostream& os) const = 0;
};

class AstAnd : public AstNode {
public:
    AstAnd() = default;

    void addOperand(AstNode* operand) {
        operands.push_back(operand);
    }

protected:
    void print(std::ostream& os) const override;

private:
    std::vector<AstNode*> operands;
};

class AstOr : public AstNode {
public:
    AstOr() = default;

    void addOperand(AstNode* operand) {
        operands.push_back(operand);
    }

protected:
    void print(std::ostream& os) const override;

private:
    std::vector<AstNode*> operands;
};

class AstNot : public AstNode {
public:
    AstNot(AstNode* operand) : operand(operand) {}

protected:
    void print(std::ostream& os) const override;

private:
    AstNode* operand;
};

class AstVar : public AstNode {
public:
    AstVar(std::string id) : id(id) {}

protected:
    void print(std::ostream& os) const override;

private:
    std::string id;
};
