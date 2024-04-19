#pragma once
#include "rule.h"

class UpRule : public Rule {
public:
    UpRule(const Object& resultElement, const Object& firstArgument,
           const Object& secondArgument);

    Element generateConnection(Element& first, Element& second) override;
    Element connect(const Element& first, const Element& second) const override;
    bool isFollowing(const Element& first, const Element& second) const override;

private:
    void makeSameLength(Element& first, Element& second);
    Element& getLongestElement(Element& first, Element& second);
    Element& getShortestElement(Element& first, Element& second);
};

