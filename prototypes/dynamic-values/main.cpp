#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <tr1/memory>

// base class:
class Value
{
    public:
        typedef std::tr1::shared_ptr<Value> ptr;
        char getTypeTag() const
        {
            return this->doGetTypeTag();
        }
    private:
        virtual char doGetTypeTag() const = 0;
};

// static functions:
static void printValues(std::ostringstream &os, const std::vector<Value::ptr> &message);

// Children of Value:
class IntValue: public Value
{
    public:
        typedef std::tr1::shared_ptr<IntValue> ptr;
        IntValue(long int value) :
            value_(value)
        {}
        void setInt(long int value)
        {
            this->value_ = value;
        }
        long int getInt() const
        {
            return value_;
        }
        static Value::ptr create(long int value)
        {
            IntValue::ptr ret(new IntValue(value));
            return std::tr1::static_pointer_cast<Value>(ret);
        }
        static IntValue::ptr convert(const Value::ptr &from)
        {
            return std::tr1::dynamic_pointer_cast<IntValue>(from);
        }
    private:
        long int value_;
        virtual char doGetTypeTag() const
        {
            return 'i';
        }
};

class StringValue: public Value
{
    public:
        typedef std::tr1::shared_ptr<StringValue> ptr;
        StringValue(const char *value) :
            value_(value)
        {}
        void setString(const char * value)
        {
            this->value_ = value;
        }
        const std::string & getString() const
        {
            return value_;
        }
        static Value::ptr create(const char * value)
        {
            StringValue::ptr ret(new StringValue(value));
            return std::tr1::static_pointer_cast<Value>(ret);
        }
        static StringValue::ptr convert(const Value::ptr &from)
        {
            return std::tr1::dynamic_pointer_cast<StringValue>(from);
        }
    private:
        std::string value_;
        virtual char doGetTypeTag() const
        {
            return 's';
        }
};

class ListValue: public Value
{
    public:
        typedef std::tr1::shared_ptr<ListValue> ptr;
        ListValue(const std::vector<Value::ptr> &value) :
            value_(value)
        {}
        void setList(const std::vector<Value::ptr> &value)
        {
            this->value_ = value;
        }
        std::vector<Value::ptr> & getList()
        {
            return value_;
        }
        static Value::ptr create(std::vector<Value::ptr> value)
        {
            return Value::ptr(new ListValue(value));
        }
        static ListValue::ptr convert(Value::ptr from)
        {
            return std::tr1::dynamic_pointer_cast<ListValue>(from);
        }
    private:
        std::vector<Value::ptr> value_;
        virtual char doGetTypeTag() const
        {
            return 'l';
        }
};

static void printValues(std::ostringstream &os, const std::vector<Value::ptr> &message)
{
    os << "[";
    for (unsigned int i = 0; i < message.size(); ++i)
    {
        Value::ptr value = message[i];
        if (value->getTypeTag() == 'i')
        {
            os << IntValue::convert(value)->getInt();
        }
        else if (value->getTypeTag() == 's')
        {
            os << "\"";
            os << StringValue::convert(value)->getString();
            os << "\"";
        }
        else if (value->getTypeTag() == 'l')
        {
            std::vector<Value::ptr> list = (ListValue::convert(value))->getList();
            printValues(os, list);
        }
        else
        {
            std::cerr << __FUNCTION__ << ": Unsupported type \"" << value->getTypeTag() << "\"." << std::endl;
        }
        if (message.size() != 0 && i < message.size() - 1)
        {
            os << ", ";
        }
    }
    os << "]";
}

int main(int /* argc */, char ** /* argv */)
{
    std::vector<Value::ptr> message;
    message.push_back(IntValue::create(2));
    message.push_back(StringValue::create("hello"));

    std::vector<Value::ptr> list;
    list.push_back(IntValue::create(2));
    list.push_back(StringValue::create("hello"));
    message.push_back(ListValue::create(list));
    
    std::ostringstream os;
    printValues(os, message);
    std::cout << os.str() << std::endl;
    return 0;
}

