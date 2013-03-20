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

/** @file
 * The DictValue class.
 */

#ifndef __ATOM_DICTVALUE_H__
#define __ATOM_DICTVALUE_H__

#include <map>
#include <string>
#include "atom/value.h"

namespace atom {

/**
 * Stores a map of strings to shared pointers to Value instances.
 */
class DictValue: public Value
{
    public:
        typedef std::tr1::shared_ptr<DictValue> ptr;
        static const char TYPE_TAG = 'D';
        DictValue(const std::map<std::string, Value::ptr> &value) :
            value_(value)
        {}
        void setMap(const std::map<std::string, Value::ptr> &value)
        {
            this->value_ = value;
        }
        std::map<std::string, Value::ptr> & getMap()
        {
            return value_;
        }
        static Value::ptr create(std::map<std::string, Value::ptr> &value)
        {
            DictValue::ptr ret(new DictValue(value));
            return std::tr1::static_pointer_cast<Value>(ret);
        }
        static DictValue::ptr convert(Value::ptr from)
        {
            return std::tr1::dynamic_pointer_cast<DictValue>(from);
        }
    private:
        std::map<std::string, Value::ptr> value_;
        virtual char doGetTypeTag() const
        {
            return TYPE_TAG;
        }
};

} // end of namespace

#endif // include guard

