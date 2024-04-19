#include "pch.h"
#include "terminal.h"

Terminal::Terminal(const std::string& name, const Line& terminalLine) 
    : Object(name), standardElementLine_(terminalLine)
{}

Element Terminal::getStandardElement() const
{
    return Element(*this, standardElementLine_);
}
