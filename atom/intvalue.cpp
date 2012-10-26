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

#include "atom/intvalue.h"
#include <limits>
#include <sstream>
#include <ostream>
#include <iostream>

namespace atom {

bool IntValue::setInt(long int value)
{
    if (value > this->max_)
        return false;
    if (value < this->min_)
        return false;
    this->value_ = value;
    return true;
}
long int IntValue::getInt() const
{
    return value_;
}
Value::ptr IntValue::create(long int value)
{
    IntValue::ptr ret(new IntValue(value));
    return std::tr1::static_pointer_cast<Value>(ret);
}
IntValue::ptr IntValue::convert(const Value::ptr &from)
{
    return std::tr1::dynamic_pointer_cast<IntValue>(from);
}
bool IntValue::setRange(long int minimum, long int maximum)
{
    if (! this->setMin(minimum))
        return false;
    if (! this->setMax(maximum))
        return false;
    return true;
}
bool IntValue::setMax(long int maximum)
{
    if (maximum > std::numeric_limits<long int>::max())
        return false;
    this->max_ = maximum;
    return true;
}
bool IntValue::setMin(long int minimum)
{
    if (minimum < std::numeric_limits<long int>::min())
        return false;
    this->min_ = minimum;
    return true;
}
long int IntValue::getMax() const
{
    return this->max_;
}
long int IntValue::getMin() const
{
    return this->min_;
}
IntValue::IntValue(long int value) :
    value_(value)
{
    this->min_ = std::numeric_limits<long int>::min();
    this->max_ = std::numeric_limits<long int>::max();
}
char IntValue::doGetTypeTag() const
{
    return TYPE_TAG;
}

long int toInt(const Value::ptr &value)
    throw(BadTypeTagError)
{
    if (value->getTypeTag() != IntValue::TYPE_TAG)
    {
        std::ostringstream os;
        os << __FUNCTION__ << ": Expect int but got " << value->getTypeTag();
        throw BadTypeTagError(os.str().c_str());
    }
    return IntValue::convert(value)->getInt();
}

} // end of namespace
