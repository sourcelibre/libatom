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

#include "atom/floatvalue.h"
#include "atom/intvalue.h"
#include <limits>
#include <sstream>
#include <ostream>
#include <iostream>

namespace atom {

bool FloatValue::setFloat(Float value)
{
    if (value > this->max_)
        return false;
    if (value < this->min_)
        return false;
    this->value_ = value;
    return true;
}
Float FloatValue::getFloat() const
{
    return value_;
}
Value::ptr FloatValue::create(Float value)
{
    FloatValue::ptr ret(new FloatValue(value));
    return std::tr1::static_pointer_cast<Value>(ret);
}
FloatValue::ptr FloatValue::convert(const Value::ptr &from)
{
    return std::tr1::dynamic_pointer_cast<FloatValue>(from);
}
bool FloatValue::setRange(Float minimum, Float maximum)
{
    if (! this->setMin(minimum))
        return false;
    if (! this->setMax(maximum))
        return false;
    return true;
}
bool FloatValue::setMax(Float maximum)
{
    if (maximum > std::numeric_limits<Float>::max())
        return false;
    this->max_ = maximum;
    return true;
}
bool FloatValue::setMin(Float minimum)
{
    if (minimum < std::numeric_limits<Float>::min())
        return false;
    this->min_ = minimum;
    return true;
}
Float FloatValue::getMax() const
{
    return this->max_;
}
Float FloatValue::getMin() const
{
    return this->min_;
}

FloatValue::FloatValue(Float value) :
    value_(value)
{
    this->min_ = std::numeric_limits<Float>::min();
    this->max_ = std::numeric_limits<Float>::max();
}
char FloatValue::doGetTypeTag() const
{
    return TYPE_TAG;
}

Float toFloat(const Value::ptr &value)
    throw(BadTypeTagError)
{
    Float v;
    if (value->getTypeTag() == FloatValue::TYPE_TAG)
    {
        v = FloatValue::convert(value)->getFloat();
    }
    else if (value->getTypeTag() == IntValue::TYPE_TAG)
    {
        v = (Float)(IntValue::convert(value)->getInt());
    }
    else
    {
        std::ostringstream os;
        os << __FUNCTION__ << ": Expect float but got " << value->getTypeTag();
        throw BadTypeTagError(os.str().c_str());
    }
    return v;
}

} // end of namespace
