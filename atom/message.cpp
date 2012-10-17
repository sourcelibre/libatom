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

namespace atom {

std::ostream & operator<<(std::ostream &os, const Value::ptr& value)
{
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
        os << list;
    }
    else if (value->getTypeTag() == 'f')
    {
        os << FloatValue::convert(value)->getFloat();
    }
    else if (value->getTypeTag() == 'b')
    {
        os << (BooleanValue::convert(value)->getBoolean() ? "true" : "false");
    }
    else if (value->getTypeTag() == '-')
    {
        os << "null";
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

} // end of namespace

