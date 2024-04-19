#include "pch.h"
#include "inside_rule.h"

InsideRule::InsideRule(const Object& resultElement, const Object& firstArgument,
                       const Object& secondArgument)
    : Rule(resultElement, firstArgument, secondArgument)
{}

Element InsideRule::generateConnection(Element& first, Element& second)
{
    using uni_int_distr_param = std::uniform_int_distribution<int>::param_type;

    second.scaleTransform(first.getLength() / second.getLength() + 1.5,
                          first.getHeight() / second.getHeight() + 1.5);

    uni_int_distr_param distrRange(static_cast<int>(std::abs(first.getLength() - second.getLength()) * 0.5),
                                   static_cast<int>(std::abs(first.getLength() - second.getLength()) * 0.8));

    distribution_.param(distrRange);
    int xDelta = second.getStartPos().getX() + distribution_(random_) - first.getStartPos().getX();
    
    distrRange = uni_int_distr_param(static_cast<int>(std::abs(first.getHeight() - second.getHeight()) * 0.5),
                                     static_cast<int>(std::abs(first.getHeight() - second.getHeight()) * 0.8));
    distribution_.param(distrRange);
    int yDelta = (second.getEndPos().getY() - distribution_(random_) - first.getEndPos().getY()) * 0.3;

    first.shiftTransform(xDelta, yDelta);

    return connect(first, second);
}

Element InsideRule::connect(const Element& first, const Element& second) const
{
    std::vector<Line> resultLines(first.getLines());
    const std::vector<Line>& secondLines = second.getLines();
    resultLines.insert(resultLines.end(), secondLines.begin(), secondLines.end());

    return Element(resultElement_, std::move(resultLines), second.getStartPos(), second.getEndPos());
}

bool InsideRule::isFollowing(const Element& first, const Element& second) const
{
    if (first.getNonterminal().getName() != firstArgument_.getName() 
        || second.getNonterminal().getName() != secondArgument_.getName()
        || (first.getStartPos() == second.getStartPos() && first.getEndPos() == second.getEndPos())
        ) {
        return false;
    }

    return first.getStartPos().getX() > second.getStartPos().getX() - deltaVariation_
           && first.getStartPos().getY() + deltaVariation_ > second.getStartPos().getY()
           && first.getEndPos().getX() - deltaVariation_ < second.getEndPos().getX()
           && first.getEndPos().getY() < second.getEndPos().getY() + deltaVariation_;
}
