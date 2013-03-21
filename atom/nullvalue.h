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
 * The NullValue class.
 */

#ifndef __ATOM_NULLVALUE_H__
#define __ATOM_NULLVALUE_H__

#include "atom/value.h"

namespace atom {

class NullValue: public Value
{
    public:
        typedef std::tr1::shared_ptr<NullValue> ptr;
        static const char TYPE_TAG = 'N';
        static Value::ptr create();
        static NullValue::ptr convert(const Value::ptr &from);
    private:
        std::string value_;
        NullValue();
        virtual char doGetTypeTag() const;
};

std::ostream & operator<<(std::ostream &os, const NullValue& value);

} // end of namespace

#endif // include guard

