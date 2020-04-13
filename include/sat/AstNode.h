#pragma once

#include <iostream>
#include <vector>

class AstNode;
class AstAnd;
class AstOr;
class AstNot;
class AstVariable;

/**
 * Represents a generic node in the AST.
 */
class AstNode {
public:
    friend std::ostream& operator<<(std::ostream& os, const AstNode& node) {
        node.print(os);
        return os;
    }

    virtual AstNode* clone() const = 0;

protected:
    virtual void print(std::ostream& os) const = 0;
};

/**
 * Represents an "X & Y" in a logical formula.
 */
class AstAnd : public AstNode {
public:
    AstAnd(AstNode* left, AstNode* right) : left(left), right(right) {}

    AstNode* getLeft() const {
        return left;
    }

    AstNode* getRight() const {
        return right;
    }

    AstAnd* clone() const override {
        return new AstAnd(left->clone(), right->clone());
    }

protected:
    void print(std::ostream& os) const override;

private:
    AstNode* left;
    AstNode* right;
};

/**
 * Represents an "X | Y" in a logical formula.
 */
class AstOr : public AstNode {
public:
    AstOr(AstNode* left, AstNode* right) : left(left), right(right) {}

    AstNode* getLeft() const {
        return left;
    }

    AstNode* getRight() const {
        return right;
    }

    AstOr* clone() const override {
        return new AstOr(left->clone(), right->clone());
    }

protected:
    void print(std::ostream& os) const override;

private:
    AstNode* left;
    AstNode* right;
};

/**
 * Represents an "!X" in a logical formula.
 */
class AstNot : public AstNode {
public:
    AstNot(AstNode* operand) : operand(operand) {}

    AstNode* getOperand() const {
        return operand;
    }

    AstNot* clone() const override {
        return new AstNot(operand->clone());
    }

protected:
    void print(std::ostream& os) const override;

private:
    AstNode* operand;
};

/**
 * Represents a variable in a logical formula.
 */
class AstVariable : public AstNode {
public:
    AstVariable(std::string name) : name(name) {}

    std::string getName() const {
        return name;
    }

    AstVariable* clone() const override {
        return new AstVariable(name);
    }

protected:
    void print(std::ostream& os) const override;

private:
    std::string name;
};
