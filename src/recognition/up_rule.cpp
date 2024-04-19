#include "pch.h"
#include "up_rule.h"

UpRule::UpRule(const Object& resultElement, const Object& firstArgument,
               const Object& secondArgument)
    : Rule(resultElement, firstArgument, secondArgument)
{}

Element UpRule::generateConnection(Element& first, Element& second)
{
    using uni_int_distr_param = std::uniform_int_distribution<int>::param_type;

    makeSameLength(first, second);
    distribution_.param(uni_int_distr_param(0, 1));
    first.shiftTransform(0, second.getStartPos().getY() - first.getEndPos().getY() - distribution_(random_));

    return connect(first, second);
}

Element UpRule::connect(const Element& first, const Element& second) const
{
    std::vector<Line> resultLines(first.getLines());
    const std::vector<Line>& secondLines = second.getLines();
    resultLines.insert(resultLines.end(), secondLines.begin(), secondLines.end());

    return Element(resultElement_, std::move(resultLines), first.getStartPos(), second.getEndPos());
}

bool UpRule::isFollowing(const Element& first, const Element& second) const
{
    if (first.getNonterminal().getName() != firstArgument_.getName() 
        || second.getNonterminal().getName() != secondArgument_.getName()
        || (first.getStartPos() == second.getStartPos() && first.getEndPos() == second.getEndPos())
        ) {
        return false;
    }
    // Screen coordinates
    return second.getStartPos().getY() + deltaVariation_ > first.getEndPos().getY()
        && first.getStartPos().getX() + first.getLength() / 2.0 > second.getStartPos().getX()
        && first.getStartPos().getX() + first.getLength() / 2.0 < second.getEndPos().getX();
}

void UpRule::makeSameLength(Element& first, Element& second)
{
    Element& longestElement = getLongestElement(first, second);
    Element& shortestElement = getShortestElement(first, second);
    if (shortestElement.getLength() == 0) {
        return;
    }

    shortestElement.scaleTransform(longestElement.getLength() / shortestElement.getLength(), 1.0);
}

Element& UpRule::getLongestElement(Element& first, Element& second)
{
    return first.getLength() > second.getLength() ? first : second;
}

Element& UpRule::getShortestElement(Element& first, Element& second)
{
    return first.getLength() < second.getLength() ? first : second;
}
