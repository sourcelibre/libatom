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

namespace atom {

/**
 * Stores an integer.
 */
class IntValue: public Value
{
    public:
        typedef std::tr1::shared_ptr<IntValue> ptr;
        static const char TYPE_TAG = 'i';
        void setInt(long int value)
        {
            this->value_ = value;
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
    private:
        long int value_;
        IntValue(long int value) :
            value_(value)
        {}
        virtual char doGetTypeTag() const
        {
            return TYPE_TAG;
        }
};

} // end of namespace

#endif // include guard

