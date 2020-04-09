#pragma once

#include <iostream>
#include <vector>

class AstNode;
class AstAnd;
class AstOr;
class AstNot;
class AstVar;

/**
 * Represents a generic node in the AST.
 */
class AstNode {
public:
    friend std::ostream& operator<<(std::ostream& os, const AstNode& node) {
        node.print(os);
        return os;
    }

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

protected:
    void print(std::ostream& os) const override;

private:
    AstNode* operand;
};

/**
 * Represents a variable in a logical formula.
 */
class AstVar : public AstNode {
public:
    AstVar(std::string id) : id(id) {}

    std::string getName() const {
        return id;
    }

protected:
    void print(std::ostream& os) const override;

private:
    std::string id;
};
