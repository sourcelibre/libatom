#include <string>
#include <vector>
#include <iostream>
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

typedef std::vector<Value::ptr> Message;

// static functions:
static void printValues(const std::vector<Value::ptr> &message);

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
        static IntValue::ptr convert(Value::ptr &from)
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
        const char * getString() const
        {
            return value_.c_str();
        }
        static Value::ptr create(const char * value)
        {
            StringValue::ptr ret(new StringValue(value));
            return std::tr1::static_pointer_cast<Value>(ret);
        }
        static StringValue::ptr convert(Value::ptr &from)
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

// class ListValue: public Value
// {
//     public:
//         ListValue(const std::vector<Value> &value) :
//             value_(value);
//         {}
//         void setList(const std::vector<Value> &value)
//         {
//             this->value_ = value;
//         }
//         const std::vector<Value> & getList() const
//         {
//             return value_;
//         }
//         Value::ptr create(std::vector<Value> &value)
//         {
//             return Value::ptr(new ListValue(value));
//         }
//         IntValue::ptr convert(Value::ptr from)
//         {
//             return std::tr1::dynamic_pointer_cast<ListValue>(from);
//         }
//     private:
//         std::vector<Value> value_;
//         virtual char doGetTypeTag() const
//         {
//             return 'l'
//         }
// };


static void printValues(std::vector<Value::ptr> &message)
{
    std::vector<Value::ptr>::iterator iter;
    for (iter = message.begin(); iter != message.end(); ++iter)
    {
        if ((*iter)->getTypeTag() == 'i')
        {
            std::cout << (IntValue::convert((*iter)))->getInt() << std::endl;
        }
        else if ((*iter)->getTypeTag() == 's')
        {
            StringValue::ptr tmp = std::tr1::dynamic_pointer_cast<StringValue>((*iter));
            std::cout << tmp->getString() << std::endl;
            //std::cout << (StringValue::convert((*iter)))->getString() << std::endl;
        }
        else
        {
            std::cerr << __FUNCTION__ << ": Unsupported type \"" << (*iter)->getTypeTag() << "\"." << std::endl;
        }
    }
}

int main(int /* argc */, char ** /* argv */)
{
    std::vector<Value::ptr> message;
    message.push_back(IntValue::create(2));
    message.push_back(StringValue::create("hello"));
    printValues(message);
    return 0;
}

