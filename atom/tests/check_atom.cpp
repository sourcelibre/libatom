#include "atom/atom.h"
#include <iostream>

static const bool VERBOSE = true;

static bool check_message()
{
    using namespace atom;
    Message message;
    message.push_back(Atom("hello"));
    message.push_back(Atom(2));
    message.push_back(Atom(3.14159));
    message.push_back(Atom(3.14159f));
    message.push_back(Atom(true));

    if (VERBOSE)
    {
        Message::const_iterator iter;
        for (iter = message.begin(); iter != message.end(); iter++)
        {
            Atom atom = (*iter);
            std::cout << atom.getType() << ": ";
            if (atom.isString())
                std::cout << atom.getString();
            else if (atom.isInt())
                std::cout << atom.getInt();
            else if (atom.isDouble())
                std::cout << atom.getDouble();
            else if (atom.isFloat())
                std::cout << atom.getFloat();
            else if (atom.isBool())
                std::cout << atom.getBool();
            std::cout << std::endl;
        }
        std::cout << "types: " << message_get_types(message) << std::endl;
        std::cout << message << std::endl;
    }
    return true;
}

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;
    if (! check_message())
        return 1;
    return 0;
}

