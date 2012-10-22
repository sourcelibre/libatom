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
 * The IntValue class.
 */

#ifndef __ATOM_INTVALUE_H__
#define __ATOM_INTVALUE_H__

#include "atom/value.h"
#include <limits>

namespace atom {

/**
 * Stores an integer.
 */
class IntValue: public Value
{
    public:
        typedef std::tr1::shared_ptr<IntValue> ptr;
        static const char TYPE_TAG = 'i';
        bool setInt(long int value)
        {
            if (value > this->max_)
                return false;
            if (value < this->min_)
                return false;
            this->value_ = value;
            return true;
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
        bool setRange(long int minimum, long int maximum)
        {
            if (! this->setMin(minimum))
                return false;
            if (! this->setMax(maximum))
                return false;
            return true;
        }
        bool setMax(long int maximum)
        {
            if (maximum > std::numeric_limits<long int>::max())
                return false;
            this->max_ = maximum;
            return true;
        }
        bool setMin(long int minimum)
        {
            if (minimum < std::numeric_limits<long int>::min())
                return false;
            this->min_ = minimum;
            return true;
        }
        long int getMax() const
        {
            return this->max_;
        }
        long int getMin() const
        {
            return this->min_;
        }
    private:
        long int value_;
        long int max_;
        long int min_;
        IntValue(long int value) :
            value_(value)
        {
            this->min_ = std::numeric_limits<long int>::min();
            this->max_ = std::numeric_limits<long int>::max();
        }
        virtual char doGetTypeTag() const
        {
            return TYPE_TAG;
        }
};

} // end of namespace

#endif // include guard

