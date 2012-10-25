/**
 * This file is in the public domain.
 * Author: Alexandre Quessy
 */
#include <iostream>
#include <atom/message.h>

static const bool VERBOSE = true;

static void example_1()
{
    atom::Message message;
    message.push_back(atom::StringValue::create("hello"));
    message.push_back(atom::IntValue::create(2));
    message.push_back(atom::FloatValue::create(3.14159));
    message.push_back(atom::BooleanValue::create(true));

    if (VERBOSE)
    {
        atom::Message::const_iterator iter;
        for (iter = message.begin(); iter != message.end(); iter++)
        {
            char typeTag = (*iter)->getTypeTag();
            switch (typeTag)
            {
                case atom::StringValue::TYPE_TAG:
                    std::cout << atom::StringValue::convert(*iter)->getString();
                    break;
                case atom::IntValue::TYPE_TAG:
                    std::cout << atom::IntValue::convert(*iter)->getInt();
                    break;
                case atom::FloatValue::TYPE_TAG:
                    std::cout << atom::FloatValue::convert(*iter)->getFloat();
                    break;
                case atom::BooleanValue::TYPE_TAG:
                    std::cout << atom::BooleanValue::convert(*iter)->getBoolean();
                    break;
                default:
                    break;
            }
            std::cout << std::endl;
        }
        std::cout << "types: " << atom::getTypeTags(message) << std::endl;
        std::cout << message << std::endl;
    }
}

static void example_2()
{
    atom::Message message = atom::createMessage("sifb", "Hello", 2, 3.14159, true);
    std::cout << message << std::endl;
}

int main(int /* argc */, char ** /*argv*/)
{
    example_1();
    example_2();
    return 0;
}

