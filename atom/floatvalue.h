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

#include <limits>
#include <sstream>
#include "atom/value.h"
#include "atom/exceptions.h"

namespace atom {

typedef double Float;

class FloatValue: public Value
{
    public:
        typedef std::tr1::shared_ptr<FloatValue> ptr;
        static const char TYPE_TAG = 'f';
        bool setFloat(Float value);
        Float getFloat() const;
        static Value::ptr create(Float value);
        static FloatValue::ptr convert(const Value::ptr &from);
        bool setRange(Float minimum, Float maximum);
        bool setMax(Float maximum);
        bool setMin(Float minimum);
        Float getMax() const;
        Float getMin() const;
    private:
        Float value_;
        Float max_;
        Float min_;
        FloatValue(Float value);
        virtual char doGetTypeTag() const;
};

Float toFloat(const Value::ptr &value)
    throw(BadTypeTagError);

} // end of namespace

#endif // include guard

