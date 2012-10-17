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
 * The StringValue class.
 */

#ifndef __ATOM_STRINGVALUE_H__
#define __ATOM_STRINGVALUE_H__

#include <string>
#include "atom/value.h"

/**
 * Stores a text string.
 */
class StringValue: public Value
{
    public:
        typedef std::tr1::shared_ptr<StringValue> ptr;
        void setString(const char * value)
        {
            this->value_ = value;
        }
        const std::string & getString() const
        {
            return value_;
        }
        static Value::ptr create(const char * value)
        {
            StringValue::ptr ret(new StringValue(value));
            return std::tr1::static_pointer_cast<Value>(ret);
        }
        static StringValue::ptr convert(const Value::ptr &from)
        {
            return std::tr1::dynamic_pointer_cast<StringValue>(from);
        }
    private:
        std::string value_;
        StringValue(const char *value) :
            value_(value)
        {}
        virtual char doGetTypeTag() const
        {
            return 's';
        }
};

} // end of namespace

#endif // include guard

