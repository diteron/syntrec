#pragma once

#include "rule.h"

class LeftRule : public Rule {
public:
    LeftRule(const Object& resultElement, const Object& firstArgument,
             const Object& secondArgument);

    Element generateConnection(Element& first, Element& second) override;
    Element connect(const Element& first, const Element& second) const override;
    bool isFollowing(const Element& first, const Element& second) const override;
};

