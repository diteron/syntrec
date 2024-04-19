#pragma once

#include <random>

#include "object.h"
#include "element.h"

class Rule {
protected:
    Rule(const Object& resultElement, const Object& firstArgument,
         const Object& secondArgument);

    const Object& resultElement_;
    const Object& firstArgument_;
    const Object& secondArgument_;
    const double deltaVariation_ = 10.0;

    static inline std::random_device rdseed;
    static inline std::mt19937 random_ = std::mt19937(rdseed());
    std::uniform_int_distribution<> distribution_;

public:
    virtual ~Rule();

    const Object& getResultElement() const;
    const Object& getFirstArgument() const;
    const Object& getSecondArgument() const;

    virtual Element generateConnection(Element& first, Element& second) = 0;
    virtual Element connect(const Element& first, const Element& second) const = 0;
    virtual bool isFollowing(const Element& first, const Element& second) const = 0;
};

