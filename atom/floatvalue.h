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

/** @file
 * The FloatValue class.
 */

#ifndef __ATOM_FLOATVALUE_H__
#define __ATOM_FLOATVALUE_H__

#include "atom/value.h"

namespace atom {

class FloatValue: public Value
{
    public:
        typedef std::tr1::shared_ptr<FloatValue> ptr;
        static const char TYPE_TAG = 'f';
        bool setFloat(double value)
        {
            if (value > this->max_)
                return false;
            if (value < this->min_)
                return false;
            this->value_ = value;
            return true;
        }
        double getFloat() const
        {
            return value_;
        }
        static Value::ptr create(double value)
        {
            FloatValue::ptr ret(new FloatValue(value));
            return std::tr1::static_pointer_cast<Value>(ret);
        }
        static FloatValue::ptr convert(const Value::ptr &from)
        {
            return std::tr1::dynamic_pointer_cast<FloatValue>(from);
        }
        bool setRange(double minimum, double maximum)
        {
            if (! this->setMin(minimum))
                return false;
            if (! this->setMax(maximum))
                return false;
            return true;
        }
        bool setMax(double maximum)
        {
            if (maximum > std::numeric_limits<double>::max())
                return false;
            this->max_ = maximum;
            return true;
        }
        bool setMin(double minimum)
        {
            if (minimum < std::numeric_limits<double>::min())
                return false;
            this->min_ = minimum;
            return true;
        }
        double getMax() const
        {
            return this->max_;
        }
        double getMin() const
        {
            return this->min_;
        }
    private:
        double value_;
        double max_;
        double min_;
        FloatValue(double value) :
            value_(value)
        {
            this->min_ = std::numeric_limits<double>::min();
            this->max_ = std::numeric_limits<double>::max();
        }
        virtual char doGetTypeTag() const
        {
            return TYPE_TAG;
        }
};

} // end of namespace

#endif // include guard

