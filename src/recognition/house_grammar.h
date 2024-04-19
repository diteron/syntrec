#pragma once

#include "object.h"
#include "left_rule.h"
#include "inside_rule.h"
#include "up_rule.h"

class HouseGrammar {
public:
    HouseGrammar();
    Element getHouse() const;
    Element getElement(const Object* elementObj) const;
    Element getTerminalElement(const Line& line) const;
    std::string isHouse(const std::vector<Element>& drawnElements);

private:
    std::string getGetTerminalName(const Line& line) const;

    static std::unordered_map<std::string, std::shared_ptr<Object>> getHouseObjects();
    static std::vector<std::shared_ptr<Rule>> getHouseRules();

    bool isEachArgumentInElements(const std::shared_ptr<Rule>& rule, std::vector<Element>& elements);
    bool isAnySecondArgumentInElements(Element firstArg,
                                       const std::shared_ptr<Rule>& rule, std::vector<Element>& elements);
    bool isAnyElementFollowsRule(int firstElemIdx, int lastElemIdx,
                                 Element firstArg, const std::shared_ptr<Rule>& rule, std::vector<Element>& elements);
    void threadSafePushback(const Element& element, std::vector<Element>& vector);

    mutable std::mutex mutex_;
    static inline Object startObject_ = Object("house");
    static inline std::unordered_map<std::string,
                                     std::shared_ptr<Object>> houseObjects_ = getHouseObjects();
    static inline std::vector<std::shared_ptr<Rule>> rules_ = getHouseRules();
};

