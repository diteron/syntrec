#include "pch.h"
#include "object.h"

Object::Object()
    : name_("blank_object")
{}

Object::Object(const std::string& name)
    : name_(name)
{}

const std::string& Object::getName() const
{
    return name_;
}
