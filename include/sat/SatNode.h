#pragma once

#include <iostream>
#include <string>
#include <vector>

class SatNode;
class SatConjunction;
class SatDisjunction;
class SatAtom;

class SatNode {
public:
    friend std::ostream& operator<<(std::ostream& os, const SatNode& node) {
        node.print(os);
        return os;
    }

    virtual SatNode* clone() const = 0;

protected:
    virtual void print(std::ostream& os) const = 0;
};

/**
 * Represents a conjunction of nested disjunctions.
 */
class SatConjunction : public SatNode {
public:
    SatConjunction() = default;

    /**
     * Add a disjunction to the conjunction.
     * @param disjunction disjunction to add
     */
    void addDisjunction(SatDisjunction* disjunction) {
        disjunctions.push_back(disjunction);
    }

    const std::vector<SatDisjunction*>& getDisjunctions() const {
        return disjunctions;
    }

    size_t size() const {
        return disjunctions.size();
    }

    SatConjunction* clone() const override;

protected:
    void print(std::ostream& os) const override;

private:
    std::vector<SatDisjunction*> disjunctions{};
};

/**
 * Represents a disjunction of nested atoms.
 */
class SatDisjunction : public SatNode {
public:
    SatDisjunction() = default;

    /**
     * Add an atom to the disjunction.
     * @param atom atom to add
     */
    void addAtom(SatAtom* atom) {
        atoms.push_back(atom);
    }

    const std::vector<SatAtom*>& getAtoms() const {
        return atoms;
    }

    size_t size() const {
        return atoms.size();
    }

    SatDisjunction* clone() const override;

protected:
    void print(std::ostream& os) const override;

private:
    std::vector<SatAtom*> atoms{};
};

/**
 * Represents a possibly negated atom.
 */
class SatAtom : public SatNode {
public:
    SatAtom(std::string name, bool negated) : name(name), negated(negated) {}

    std::string getName() const {
        return name;
    }

    bool isNegated() const {
        return negated;
    }

    SatAtom* clone() const override;

protected:
    void print(std::ostream& os) const override;

private:
    std::string name;
    bool negated;
};
