#pragma once

#include <iostream>
#include <memory>
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
    virtual ~AstNode() = default;
    virtual AstNode* clone() const = 0;

protected:
    virtual void print(std::ostream& os) const = 0;
};

/**
 * Represents an "X & Y" in a logical formula.
 */
class AstAnd : public AstNode {
public:
    AstAnd(std::unique_ptr<AstNode> left, std::unique_ptr<AstNode> right)
        : left(std::move(left)), right(std::move(right)) {}

    AstNode* getLeft() const { return left.get(); }

    AstNode* getRight() const { return right.get(); }

    AstAnd* clone() const override {
        return new AstAnd(std::unique_ptr<AstNode>(left->clone()),
                          std::unique_ptr<AstNode>(right->clone()));
    }

protected:
    void print(std::ostream& os) const override {
        os << "(" << *left << " & " << *right << ")";
    }

private:
    std::unique_ptr<AstNode> left;
    std::unique_ptr<AstNode> right;
};

/**
 * Represents an "X | Y" in a logical formula.
 */
class AstOr : public AstNode {
public:
    AstOr(std::unique_ptr<AstNode> left, std::unique_ptr<AstNode> right)
        : left(std::move(left)), right(std::move(right)) {}

    AstNode* getLeft() const { return left.get(); }

    AstNode* getRight() const { return right.get(); }

    AstOr* clone() const override {
        return new AstOr(std::unique_ptr<AstNode>(left->clone()),
                         std::unique_ptr<AstNode>(right->clone()));
    }

protected:
    void print(std::ostream& os) const override {
        os << "(" << *left << " | " << *right << ")";
    }

private:
    std::unique_ptr<AstNode> left;
    std::unique_ptr<AstNode> right;
};

/**
 * Represents an "X -> Y" in a logical formula.
 */
class AstImplies : public AstNode {
public:
    AstImplies(std::unique_ptr<AstNode> left, std::unique_ptr<AstNode> right)
        : left(std::move(left)), right(std::move(right)) {}

    AstNode* getLeft() const { return left.get(); }

    AstNode* getRight() const { return right.get(); }

    AstImplies* clone() const override {
        return new AstImplies(std::unique_ptr<AstNode>(left->clone()),
                              std::unique_ptr<AstNode>(right->clone()));
    }

protected:
    void print(std::ostream& os) const override {
        os << "((" << *left << ") -> (" << *right << "))";
    }

private:
    std::unique_ptr<AstNode> left;
    std::unique_ptr<AstNode> right;
};

/**
 * Represents an "!X" in a logical formula.
 */
class AstNot : public AstNode {
public:
    AstNot(std::unique_ptr<AstNode> operand) : operand(std::move(operand)) {}

    AstNode* getOperand() const { return operand.get(); }

    AstNot* clone() const override {
        return new AstNot(std::unique_ptr<AstNode>(operand->clone()));
    }

protected:
    void print(std::ostream& os) const override { os << "!" << *operand; }

private:
    std::unique_ptr<AstNode> operand;
};

/**
 * Represents a variable in a logical formula.
 */
class AstVariable : public AstNode {
public:
    AstVariable(std::string name) : name(name) {}

    std::string getName() const { return name; }

    AstVariable* clone() const override { return new AstVariable(name); }

protected:
    void print(std::ostream& os) const override { os << name; }

private:
    std::string name;
};
