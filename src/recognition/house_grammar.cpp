#include "pch.h"
#include <future>
#include <thread>
#include "house_grammar.h"
#include "terminal.h"

HouseGrammar::HouseGrammar()
    : mutex_()
{}

Element HouseGrammar::getHouse() const
{
    return getElement(&startObject_);
}

Element HouseGrammar::getElement(const Object* elementObj) const
{
    const auto* terminalObj = dynamic_cast<const Terminal*>(elementObj);
    
    if (terminalObj != nullptr) {
        return terminalObj->getStandardElement();
    }
    else {    
        auto isElementRuleResult = [&](std::shared_ptr<Rule> r) { 
            return elementObj->getName() == r->getResultElement().getName();
        };
        auto it = std::find_if(rules_.begin(), rules_.end(), isElementRuleResult);
        assert(("No such rule", it != rules_.end()));
        Element ruleFirstElem = getElement(&(it->get()->getFirstArgument()));
        Element ruleSecondElem = getElement(&(it->get()->getSecondArgument()));
        
        return it->get()->generateConnection(ruleFirstElem, ruleSecondElem);
    }
}

Element HouseGrammar::getTerminalElement(const Line& line) const
{
    std::string terminalName = getGetTerminalName(line);
    return Element(*houseObjects_[terminalName], line);
}

std::string HouseGrammar::isHouse(const std::vector<Element>& drawnElements)
{
    std::vector<Element> elements(drawnElements);
    for (const std::shared_ptr<Rule>& rule : rules_) {
        if (!isEachArgumentInElements(rule, elements)) {
            return std::string("Missed element: " + rule->getResultElement().getName());
        }
    }

    return "Drawing is a house";
}

std::string HouseGrammar::getGetTerminalName(const Line& line) const
{
    double deltaX = line.getStartPoint().getX() - line.getEndPoint().getX();
    double deltaY = line.getStartPoint().getY() - line.getEndPoint().getY();

    if (std::abs(deltaY) < 1) {
        return "a1";
    }
    if (std::abs(deltaX) < 1) {
        return "a2";
    }
    if (std::abs(deltaX / deltaY) < 0.2) {
        return "a2";
    }
    if (std::abs(deltaY / deltaX) < 0.2) {
        return "a1";
    }

    Point highPoint = line.getEndPoint().getY() < line.getStartPoint().getY() ? line.getEndPoint() : line.getStartPoint();
    Point lowPoint = line.getEndPoint().getY() > line.getStartPoint().getY() ? line.getEndPoint() : line.getStartPoint();
    if (highPoint.getX() < lowPoint.getX()) {
        return "a3";
    }

    return "a4";
}

std::unordered_map<std::string, std::shared_ptr<Object>> HouseGrammar::getHouseObjects()
{
    return std::unordered_map<std::string, std::shared_ptr<Object>>{
        {"a1", std::make_shared<Terminal>("a1", Line(Point(0, 0), Point(20, 0)))},
        {"a2", std::make_shared<Terminal>("a2", Line(Point(0, 0), Point(0, 20)))},
        {"a3", std::make_shared<Terminal>("a3", Line(Point(0, 0), Point(20, 20)))},
        {"a4", std::make_shared<Terminal>("a4", Line(Point(20, 0), Point(0, 20)))},
        {"parallel", std::make_shared<Object>("parallel")},
        {"square_bottom", std::make_shared<Object>("square_bottom")},
        {"square", std::make_shared<Object>("square")},
        {"windows", std::make_shared<Object>("windows")},
        {"facade", std::make_shared<Object>("facade")},
        {"roof", std::make_shared<Object>("roof")}
    };
}

std::vector<std::shared_ptr<Rule>> HouseGrammar::getHouseRules()
{
    return std::vector<std::shared_ptr<Rule>> {
        std::make_shared<LeftRule>(*houseObjects_["parallel"], *houseObjects_["a2"], *houseObjects_["a2"]),
        std::make_shared<UpRule>(*houseObjects_["square_bottom"], *houseObjects_["parallel"], *houseObjects_["a1"]),
        std::make_shared<UpRule>(*houseObjects_["square"], *houseObjects_["a1"], *houseObjects_["square_bottom"]),
        std::make_shared<LeftRule>(*houseObjects_["windows"], *houseObjects_["square"], *houseObjects_["square"]),
        std::make_shared<InsideRule>(*houseObjects_["facade"], *houseObjects_["windows"], *houseObjects_["square"]),
        std::make_shared<LeftRule>(*houseObjects_["roof"], *houseObjects_["a4"], *houseObjects_["a3"]),
        std::make_shared<UpRule>(startObject_, *houseObjects_["roof"], *houseObjects_["facade"])
    };
}

bool HouseGrammar::isEachArgumentInElements(const std::shared_ptr<Rule>& rule, std::vector<Element>& elements)
{
    bool result = false;
    for (size_t i = 0; i < elements.size(); ++i) {
        if (elements[i].getNonterminal().getName() == rule->getFirstArgument().getName()) {
            if (isAnySecondArgumentInElements(elements[i], rule, elements)) {
                result = true;
            }
        }
    }

    return result;
}

bool HouseGrammar::isAnySecondArgumentInElements(Element firstArg,
                                                 const std::shared_ptr<Rule>& rule, std::vector<Element>& elements)
{
    size_t elementsCnt = elements.size();
    unsigned int futuresCnt = std::thread::hardware_concurrency();
    unsigned int elementsPerFuture = std::round(elementsCnt / futuresCnt);
    std::vector<std::future<bool>> futures(futuresCnt);
    int currentFirstIdx = 0;
    int currentLastIdx = elementsPerFuture - 1;
    bool result = false;

    for (auto& future : futures) {
        if (currentLastIdx >= elementsCnt) {
            currentLastIdx = elementsCnt - 1;
        }
        future = std::async(&HouseGrammar::isAnyElementFollowsRule, this,
                            currentFirstIdx, currentLastIdx, 
                            firstArg, std::ref(rule), std::ref(elements));
        currentFirstIdx = currentLastIdx + 1;
        currentLastIdx += elementsPerFuture;
    }

    for (auto& future : futures) {
        if (future.get() == true) {
            result = true;
        }
    }

    return result;
}

bool HouseGrammar::isAnyElementFollowsRule(int firstElemIdx, int lastElemIdx, Element firstArg,
                                           const std::shared_ptr<Rule>& rule, std::vector<Element>& elements)
{
    bool result = false;
    for (size_t i = firstElemIdx; i <= lastElemIdx; ++i) {
        if (rule->isFollowing(firstArg, elements[i])) {
            threadSafePushback(rule->connect(firstArg, elements[i]), elements);
            result = true;
        }
    }

    return result;
}

void HouseGrammar::threadSafePushback(const Element& element, std::vector<Element>& vector)
{
    std::lock_guard<std::mutex> lock(mutex_);
    vector.push_back(element);
}
