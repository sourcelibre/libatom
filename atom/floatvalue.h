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

class FloatValue: public Value
{
    public:
        typedef std::tr1::shared_ptr<FloatValue> ptr;
        static const char TYPE_TAG = 'f';
        bool setFloat(double value);
        double getFloat() const;
        static Value::ptr create(double value);
        static FloatValue::ptr convert(const Value::ptr &from);
        bool setRange(double minimum, double maximum);
        bool setMax(double maximum);
        bool setMin(double minimum);
        double getMax() const;
        double getMin() const;
    private:
        double value_;
        double max_;
        double min_;
        FloatValue(double value);
        virtual char doGetTypeTag() const;
};

double toFloat(const Value::ptr &value)
    throw(BadTypeTagError);

} // end of namespace

#endif // include guard

