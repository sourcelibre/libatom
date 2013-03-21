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

#include "atom/nullvalue.h"

namespace atom {

Value::ptr NullValue::create()
{
    NullValue::ptr ret(new NullValue());
    return std::tr1::static_pointer_cast<Value>(ret);
}

NullValue::ptr NullValue::convert(const Value::ptr &from)
{
    return std::tr1::dynamic_pointer_cast<NullValue>(from);
}

NullValue::NullValue()
{}

char NullValue::doGetTypeTag() const
{
    return TYPE_TAG;
}

std::ostream & operator<<(std::ostream &os, const NullValue& /* value */)
{
	os << "null";
    return os;
}

} // end of namespace


