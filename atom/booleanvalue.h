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
 * The BooleanValue class.
 */

#ifndef __ATOM_BOOLEANVALUE_H__
#define __ATOM_BOOLEANVALUE_H__

#include "atom/value.h"

namespace atom {

/**
 * Stores a boolean.
 */
class BooleanValue: public Value
{
    public:
        typedef std::tr1::shared_ptr<BooleanValue> ptr;
        static const char TYPE_TAG = 'b';
        void setBoolean(bool value);
        bool getBoolean() const;
        static Value::ptr create(bool value);
        static BooleanValue::ptr convert(const Value::ptr &from);
    private:
        bool value_;
        BooleanValue(bool value);
        virtual char doGetTypeTag() const;
};

std::ostream & operator<<(std::ostream &os, const BooleanValue& value);

} // end of namespace

#endif // include guard

