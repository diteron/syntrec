#pragma once

class Object {
public:
    Object();
    Object(const std::string& name);
    virtual ~Object() = default;
    const std::string& getName() const;

private:
    std::string name_;
};
