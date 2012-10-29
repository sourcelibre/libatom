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

#include "atom/floatvalue.h"
#include <limits>
#include <sstream>
#include <ostream>
#include <iostream>

namespace atom {

bool FloatValue::setFloat(double value)
{
    if (value > this->max_)
        return false;
    if (value < this->min_)
        return false;
    this->value_ = value;
    return true;
}
double FloatValue::getFloat() const
{
    return value_;
}
Value::ptr FloatValue::create(double value)
{
    FloatValue::ptr ret(new FloatValue(value));
    return std::tr1::static_pointer_cast<Value>(ret);
}
FloatValue::ptr FloatValue::convert(const Value::ptr &from)
{
    return std::tr1::dynamic_pointer_cast<FloatValue>(from);
}
bool FloatValue::setRange(double minimum, double maximum)
{
    if (! this->setMin(minimum))
        return false;
    if (! this->setMax(maximum))
        return false;
    return true;
}
bool FloatValue::setMax(double maximum)
{
    if (maximum > std::numeric_limits<double>::max())
        return false;
    this->max_ = maximum;
    return true;
}
bool FloatValue::setMin(double minimum)
{
    if (minimum < std::numeric_limits<double>::min())
        return false;
    this->min_ = minimum;
    return true;
}
double FloatValue::getMax() const
{
    return this->max_;
}
double FloatValue::getMin() const
{
    return this->min_;
}

FloatValue::FloatValue(double value) :
    value_(value)
{
    this->min_ = std::numeric_limits<double>::min();
    this->max_ = std::numeric_limits<double>::max();
}
char FloatValue::doGetTypeTag() const
{
    return TYPE_TAG;
}

double toFloat(const Value::ptr &value)
    throw(BadTypeTagError)
{
    if (value->getTypeTag() != FloatValue::TYPE_TAG)
    {
        std::ostringstream os;
        os << __FUNCTION__ << ": Expect float but got " << value->getTypeTag();
        throw BadTypeTagError(os.str().c_str());
    }
    return FloatValue::convert(value)->getFloat();
}

} // end of namespace
