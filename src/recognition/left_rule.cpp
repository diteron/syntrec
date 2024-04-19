#include "pch.h"
#include "left_rule.h"

LeftRule::LeftRule(const Object& resultElement, const Object& firstArgument,
                   const Object& secondArgument)
    : Rule(resultElement, firstArgument, secondArgument)
{}

Element LeftRule::generateConnection(Element& first, Element& second)
{
    using uni_int_distr_param = std::uniform_int_distribution<int>::param_type;
    
    distribution_.param(uni_int_distr_param(2, 8));
    second.shiftTransform(first.getLength() + distribution_(random_), 0);

    return connect(first, second);
}

Element LeftRule::connect(const Element& first, const Element& second) const
{
    std::vector<Line> resultLines(first.getLines());
    const std::vector<Line>& secondLines = second.getLines();
    resultLines.insert(resultLines.end(), secondLines.begin(), secondLines.end());

    Point startPosition(first.getStartPos().getX(),
                        std::min(first.getStartPos().getY(), second.getStartPos().getY()));
    Point endPosition(second.getEndPos().getX(),
                      std::max(first.getEndPos().getY(), second.getEndPos().getY()));

    return Element(resultElement_, std::move(resultLines), startPosition, endPosition);
}

bool LeftRule::isFollowing(const Element& first, const Element& second) const
{
    if (first.getNonterminal().getName() != firstArgument_.getName() 
        || second.getNonterminal().getName() != secondArgument_.getName()
        || (first.getStartPos() == second.getStartPos() && first.getEndPos() == second.getEndPos())
        ) {
        return false;
    }

    return first.getEndPos().getX() - deltaVariation_ < second.getStartPos().getX()
        && first.getStartPos().getY() + first.getHeight() / 2.0 > second.getStartPos().getY()
        && first.getStartPos().getY() + first.getHeight() / 2.0 < second.getEndPos().getY();;
}
