#include "pch.h"
#include "rule.h"

Rule::Rule(const Object& resultElement, const Object& firstArgument,
           const Object& secondArgument) 
    : resultElement_(resultElement), firstArgument_(firstArgument),
      secondArgument_(secondArgument), distribution_()
{}

Rule::~Rule()
{}

const Object& Rule::getResultElement() const
{
    return resultElement_;
}

const Object& Rule::getFirstArgument() const
{
    return firstArgument_;
}

const Object& Rule::getSecondArgument() const
{
    return secondArgument_;
}
