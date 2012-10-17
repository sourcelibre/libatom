#include <iostream>
#include "atom/message.h"

using namespace atom;

static const bool VERBOSE = true;

bool check_messages()
{
    std::vector<Value::ptr> message;
    message.push_back(IntValue::create(2));
    message.push_back(FloatValue::create(3.14159));
    message.push_back(StringValue::create("hello"));
    message.push_back(BooleanValue::create(true));
    message.push_back(NullValue::create());

    std::vector<Value::ptr> list;
    list.push_back(IntValue::create(3));
    list.push_back(FloatValue::create(1.618));
    list.push_back(StringValue::create("hi"));
    list.push_back(BooleanValue::create(false));
    list.push_back(NullValue::create());
    message.push_back(ListValue::create(list));
    
    if (VERBOSE)
    {
        std::cout << __FILE__ << ": " << getTypeTags(message) << std::endl;
        std::cout << __FILE__ << ": " <<  message << std::endl;
    }
    return true;
}

int main(int /* argc */, char ** /* argv */)
{
    if (! check_messages())
        return 1;
    return 0;
}

