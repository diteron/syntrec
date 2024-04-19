#pragma once

#include "rule.h"

class InsideRule : public Rule {
public:
    InsideRule(const Object& resultElement, const Object& firstArgument,
               const Object& secondArgument);

    Element generateConnection(Element& first, Element& second) override;
    Element connect(const Element& first, const Element& second) const override;
    bool isFollowing(const Element& first, const Element& second) const override;
};

