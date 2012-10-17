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
 * The BooleanValue class.
 */

#ifndef __ATOM_BOOLEANVALUE_H__
#define __ATOM_BOOLEANVALUE_H__

#include "atom/value.h"

/**
 * Stores a boolean.
 */
class BooleanValue: public Value
{
    public:
        typedef std::tr1::shared_ptr<BooleanValue> ptr;
        void setBoolean(bool value)
        {
            this->value_ = value;
        }
        bool getBoolean() const
        {
            return value_;
        }
        static Value::ptr create(bool value)
        {
            BooleanValue::ptr ret(new BooleanValue(value));
            return std::tr1::static_pointer_cast<Value>(ret);
        }
        static BooleanValue::ptr convert(const Value::ptr &from)
        {
            return std::tr1::dynamic_pointer_cast<BooleanValue>(from);
        }
    private:
        bool value_;
        BooleanValue(bool value) :
            value_(value)
        {}
        virtual char doGetTypeTag() const
        {
            return 'b';
        }
};

} // end of namespace

#endif // include guard

