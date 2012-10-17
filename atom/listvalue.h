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
 * The ListValue class.
 */

#ifndef __ATOM_LISTVALUE_H__
#define __ATOM_LISTVALUE_H__

#include <vector>
#include "atom/value.h"

namespace atom {

/**
 * Stores a list of shared pointers to Value instances.
 */
class ListValue: public Value
{
    public:
        typedef std::tr1::shared_ptr<ListValue> ptr;
        static const char TYPE_TAG = 'L';
        ListValue(const std::vector<Value::ptr> &value) :
            value_(value)
        {}
        void setList(const std::vector<Value::ptr> &value)
        {
            this->value_ = value;
        }
        std::vector<Value::ptr> & getList()
        {
            return value_;
        }
        static Value::ptr create(std::vector<Value::ptr> value)
        {
            return Value::ptr(new ListValue(value));
        }
        static ListValue::ptr convert(Value::ptr from)
        {
            return std::tr1::dynamic_pointer_cast<ListValue>(from);
        }
    private:
        std::vector<Value::ptr> value_;
        virtual char doGetTypeTag() const
        {
            return TYPE_TAG;
        }
};

} // end of namespace

#endif // include guard

