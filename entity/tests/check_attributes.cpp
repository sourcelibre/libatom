#include "atom/message.h"
#include "entity/entity.h"
#include "entity/logger.h"
#include <string>
#include <iostream>

using namespace entity;

static const bool VERBOSE = false;

class DummyEntity : public Entity
{
    public:
        DummyEntity() :
            Entity(),
            triggered_(false)
        {
            this->addAttribute(Attribute::ptr(new Attribute(
                "hello", 
                atom::createMessage("ifs", 1, 3.14159, "foo")
                )));
        }
        bool triggered_;
    private:
        virtual bool onAttributeChanged(const char *name, const atom::Message &value)
        {
            triggered_ = true;
            if (VERBOSE)
            {
                std::cout << "DummyEntity::" << __FUNCTION__ << " " << name << "=" << value << std::endl;
                std::cout << "DummyEntity::triggered_ = " << triggered_ << std::endl;
            }
            return true;
        }
};

static bool check_attributes()
{
    DummyEntity x;

    Message message_b;
    message_b.appendInt(2);
    message_b.appendFloat(6.819);
    message_b.appendString("bar");

    x.setAttributeValue("hello", message_b);
    if (! x.triggered_)
    {
        std::cout << "attribute not triggered" << std::endl;
        return false;
    }

    try
    {
        Message message_c;
        message_c.appendInt(9);
        x.setAttributeValue("hello", message_c);
        std::cout << "Should not be able to set a property with a different type.\n";
        return false;
    }
    catch (const BadAtomTypeException &e)
    {}

    try
    {
        x.setAttributeValue("invalid", message_b);
        std::cout << "Should not be able to set a property that does not exist.\n";
        return false;
    }
    catch (const BadIndexException &e)
    {}

    return true;
}

int main(int /* argc */, char ** /*argv */)
{
    if (VERBOSE)
        Logger::getInstance().setLevel(DEBUG);
    if (! check_attributes())
        return 1;

    return 0;
}

