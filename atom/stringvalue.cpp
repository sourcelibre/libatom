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
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "atom/stringvalue.h"
#include <limits>
#include <sstream>
#include <ostream>
#include <iostream>

namespace atom {

void StringValue::setString(const char * value)
{
    this->value_ = value;
}

const std::string & StringValue::getString() const
{
    return value_;
}

Value::ptr StringValue::create(const char * value)
{
    StringValue::ptr ret(new StringValue(value));
    return std::tr1::static_pointer_cast<Value>(ret);
}

StringValue::ptr StringValue::convert(const Value::ptr &from)
{
    return std::tr1::dynamic_pointer_cast<StringValue>(from);
}

StringValue::StringValue(const char *value) :
    value_(value)
{
}

char StringValue::doGetTypeTag() const
{
    return TYPE_TAG;
}

std::string toString(const Value::ptr &value)
    throw(BadTypeTagError)
{
    if (value->getTypeTag() != StringValue::TYPE_TAG)
    {
        std::ostringstream os;
        os << __FUNCTION__ << ": Expect string but got " << value->getTypeTag();
        throw BadTypeTagError(os.str().c_str());
    }
    return StringValue::convert(value)->getString();
}

} // end of namespace

