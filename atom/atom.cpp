#include "atom/atom.h"

namespace atom {

Atom::Atom(double value)
{
    double_value_ = value;
    type_ = ATOM_DOUBLE;
}

Atom::Atom(bool value)
{
    bool_value_ = value;
    type_ = ATOM_BOOL;
}

Atom::Atom(float value)
{
    float_value_ = value;
    type_ = ATOM_FLOAT;
}

Atom::Atom(const char *value)
{
    string_value_ = value;
    type_ = ATOM_STRING;
}

Atom::Atom(int value)
{
    int_value_ = value;
    type_ = ATOM_INT;
}

bool Atom::isDouble() const
{
    return type_ == ATOM_DOUBLE;
}

bool Atom::isBool() const
{
    return type_ == ATOM_BOOL;
}

bool Atom::isFloat() const
{
    return type_ == ATOM_FLOAT;
}

bool Atom::isString() const
{
    return type_ == ATOM_STRING;
}

bool Atom::isInt() const
{
    return type_ == ATOM_INT;
}

std::string Atom::getString() const
{
    return string_value_;
}

void Atom::getString(std::string &result) const
{
    result = string_value_;
}

double Atom::getDouble() const
{
    return double_value_;
}

bool Atom::getBool() const
{
    return bool_value_;
}

double Atom::getFloat() const
{
    return float_value_;
}

int Atom::getInt() const
{
    return int_value_;
}

char Atom::getType() const
{
    return type_;
}

std::string message_get_types(const Message &message)
{
    std::string ret;
    Message::const_iterator iter;
    for (iter = message.begin(); iter != message.end(); iter++)
    {
        ret += (*iter).getType();
    }
    return ret;
}

std::ostream & operator<< (std::ostream &out, const Atom &atom)
{
    if (atom.isString())
        out << "\"" <<  atom.getString() << "\"";
    else if (atom.isInt())
        out << atom.getInt();
    else if (atom.isDouble())
        out << atom.getDouble();
    else if (atom.isFloat())
        out << atom.getFloat();
    else if (atom.isBool())
        out << (atom.getBool() ? "true" : "false");
    return out;
}

std::ostream & operator<< (std::ostream &out, const Message &message)
{
    Message::const_iterator iter;
    out << "(";
    unsigned int index = 0;
    unsigned int size = message.size();
    for (iter = message.begin(); iter != message.end(); iter++)
    {
        out << (*iter).getType() << ":" << (*iter);
        if (index < size - 1)
            out << ", ";
        index++;
    }
    out << ")";
    return out;
}

bool message_build_from_lo_args(Message &result, const char * types, lo_arg ** argv, int argc)
{
    bool ok = true;
    for (int i = 0; i < argc; i++)
    {
        switch (types[i])
        {
            case 'i':
                result.push_back(Atom(argv[i]->i));
                break;
            case 'f':
                result.push_back(Atom(argv[i]->f));
                break;
            case 'd':
                result.push_back(Atom(argv[i]->d));
                break;
            case 's':
                result.push_back(Atom(static_cast<const char *>(&argv[i]->s)));
                break;
            case 'T':
                result.push_back(Atom(true));
                break;
            case 'F':
                result.push_back(Atom(false));
                break;
            default:
                ok = false;
        }
    }
    return ok;
}

} // end of namespace

