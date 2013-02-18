#include <iostream>
#include <sstream>
#include "atom/message.h"

using namespace atom;
static const bool VERBOSE = true;

class Dummy : public AbstractObject
{
    public:
        typedef std::tr1::shared_ptr<Dummy> ptr;
        Dummy()
        {
            if (VERBOSE)
                std::cout << __FUNCTION__ << std::endl;
        }
        ~Dummy()
        {
            if (VERBOSE)
                std::cout << __FUNCTION__ << std::endl;
        }
};

bool check_messages()
{
    Byte blobstring[] = "this is a blob";
    Byte blobstring2[] = "this is a larger blob that contains a string.";

    std::vector<Value::ptr> message;
    message.push_back(BlobValue::create(blobstring, sizeof(blobstring)));
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

    std::map<std::string, Value::ptr> map;
    map["foo"] = IntValue::create(3);
    map["bar"] = FloatValue::create(1.618);
    map["egg"] = StringValue::create("hi");
    map["spam"] = BooleanValue::create(false);
    map["ham"] = NullValue::create();
    map["blob_empty_1"] = BlobValue::create();
    map["blob_empty_2"] = BlobValue::create();
    map["blob_with_text"] = BlobValue::create(blobstring, sizeof(blobstring));
    message.push_back(DictValue::create(map));

    message.push_back(PointerValue::create(std::tr1::dynamic_pointer_cast<AbstractObject>(Dummy::ptr(new Dummy()))));
    
    std::ostringstream os;
    os << __FILE__ << ": " << getTypeTags(message) << std::endl;
    os << __FILE__ << ": " <<  message << std::endl;

    if (VERBOSE)
    {
        std::cout << os.str();
    }
    return true;
}

bool check_range()
{
    std::vector<Value::ptr> message;
    message.push_back(IntValue::create(2));
    message.push_back(FloatValue::create(3.14159));
    
    IntValue::ptr i = IntValue::convert(message[0]);
    FloatValue::ptr f = FloatValue::convert(message[1]);

    if (VERBOSE)
    {
        std::cout << "Float range: [" << f->getMin() << ", " << f->getMax() << "]" << std::endl;
        std::cout << "Int   range: [" << i->getMin() << ", " << i->getMax() << "]" << std::endl;
    }

    i->setRange(1, 100);
    if (i->setInt(200))
    {
        std::cout << "Could setInt even though not within range." << std::endl;
        return false;
    }

    f->setRange(1.0, 100.0);
    if (f->setFloat(200.0))
    {
        std::cout << "Could setFloat even though not within range." << std::endl;
        return false;
    }
    
    f->setFloat(10.0);
    if (f->getFloat() != 10.0)
    {
        std::cout << "Float stored doesn't match expected." << std::endl;
        return false;
    }
    return true;
}

int main(int /* argc */, char ** /* argv */)
{
    if (! check_messages())
        return 1;
    if (! check_range())
        return 1;
    return 0;
}

