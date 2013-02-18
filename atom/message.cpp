/*
 * Copyright (C) 2011 Alexandre Quessy
 *
 * This file is part of libatom.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "atom/message.h"
#include <ostream>
#include <iostream>
#include <sstream>
#include <cstdarg> // va_list
#include <cstring> // strlen
#include <cstdio>

namespace atom {

std::ostream & operator<<(std::ostream &os, const Value::ptr& value)
{
    if (value->getTypeTag() == IntValue::TYPE_TAG)
    {
        os << IntValue::convert(value)->getInt();
    }
    else if (value->getTypeTag() == StringValue::TYPE_TAG)
    {
        os << "\"";
        os << StringValue::convert(value)->getString();
        os << "\"";
    }
    else if (value->getTypeTag() == ListValue::TYPE_TAG)
    {
        std::vector<Value::ptr> list = (ListValue::convert(value))->getList();
        os << list;
    }
    else if (value->getTypeTag() == FloatValue::TYPE_TAG)
    {
        os << FloatValue::convert(value)->getFloat();
    }
    else if (value->getTypeTag() == BooleanValue::TYPE_TAG)
    {
        os << (BooleanValue::convert(value)->getBoolean() ? "true" : "false");
    }
    else if (value->getTypeTag() == NullValue::TYPE_TAG)
    {
        os << "null";
    }
    else if (value->getTypeTag() == PointerValue::TYPE_TAG)
    {
        os << "*" << PointerValue::convert(value)->getPointer().get();
    }
    else if (value->getTypeTag() == DictValue::TYPE_TAG)
    {
        std::map<std::string, Value::ptr> map = (DictValue::convert(value))->getMap();
        os << map;
    }
    else if (value->getTypeTag() == BlobValue::TYPE_TAG)
    {
        os << "0x" << BlobValue::convert(value)->getHex();
    }
    else
    {
        std::cerr << __FUNCTION__ << ": Unsupported type \"" << value->getTypeTag() << "\"." << std::endl;
    }
    return os;
}

std::ostream & operator<<(std::ostream &os, const std::vector<Value::ptr>& message)
{
    os << "[";
    for (unsigned int i = 0; i < message.size(); ++i)
    {
        Value::ptr value = message[i];
        os << value;
        if (message.size() != 0 && i < message.size() - 1)
        {
            os << ", ";
        }
    }
    os << "]";
    return os;
}

std::ostream & operator<<(std::ostream &os, const std::map<std::string, Value::ptr>& map)
{
    os << "{";
    std::map<std::string, Value::ptr>::const_iterator iter;
    unsigned int position = 0;
    unsigned int size = map.size();
    for (iter = map.begin(); iter != map.end(); ++iter)
    {
        std::string key = (*iter).first;
        Value::ptr value = (*iter).second;

        os << "\"" <<  key << "\":";
        os << value;
        if (size != 0 && position < size - 1)
        {
            os << ", ";
        }
        position++;
    }
    os << "}";
    return os;
}

std::string getTypeTags(const Message &message)
{
    std::ostringstream os;
    for (unsigned int i = 0; i < message.size(); ++i)
    {
        Value::ptr value = message[i];
        os << value->getTypeTag();
    }
    return os.str();
}

Message createMessage(const char *types, ...)
    throw(BadTypeTagError)
{
    Message result;

    va_list arguments;
    va_start(arguments, types);

    for (int i = 0; types[i] != '\0'; ++i)
    {
        switch (types[i])
        {
            case FloatValue::TYPE_TAG:
            {
                double value = va_arg(arguments, double);
                result.push_back(FloatValue::create(value));
                break;
            }
            case IntValue::TYPE_TAG:
            {
                long int value = va_arg(arguments, long int);
                result.push_back(IntValue::create(value));
                break;
            }
            case BooleanValue::TYPE_TAG:
            {
                bool value = (bool) va_arg(arguments, int);
                result.push_back(BooleanValue::create(value));
                break;
            }
            case StringValue::TYPE_TAG:
            {
                const char *value = va_arg(arguments, const char*);
                result.push_back(StringValue::create(value));
                break;
            }
            case ListValue::TYPE_TAG:
            case DictValue::TYPE_TAG:
            case PointerValue::TYPE_TAG:
            default:
                {
                    std::ostringstream os;
                    os << __FUNCTION__ << ": Unsupported type tag: " << types[i] << " (types=\"" << types << "\") (length=" << std::strlen(types) << ")";
                    throw BadTypeTagError(os.str().c_str());
                }
                break;
        }
    }

    va_end(arguments);
    return result;
}

} // end of namespace

