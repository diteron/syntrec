#pragma once

#include "line.h"
#include "object.h"
#include "element.h"

class Terminal : public Object {
public:
    Terminal(const std::string& name, const Line& terminalLine);
    Element getStandardElement() const;

private:
    Line standardElementLine_;
};
