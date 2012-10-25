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
#include "atom/exceptions.h"
#include <limits>
#include <sstream>

namespace atom {

/**
 * Stores an integer.
 */
class IntValue: public Value
{
    public:
        typedef std::tr1::shared_ptr<IntValue> ptr;
        static const char TYPE_TAG = 'i';
        bool setInt(long int value);
        long int getInt() const;
        static Value::ptr create(long int value);
        static IntValue::ptr convert(const Value::ptr &from);
        bool setRange(long int minimum, long int maximum);
        bool setMax(long int maximum);
        bool setMin(long int minimum);
        long int getMax() const;
        long int getMin() const;
    private:
        long int value_;
        long int max_;
        long int min_;
        IntValue(long int value);
        virtual char doGetTypeTag() const;
};

long int toInt(const Value::ptr &value)
    throw(BadTypeTagError);

} // end of namespace

#endif // include guard

