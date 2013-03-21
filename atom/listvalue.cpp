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

#include "atom/listvalue.h"

namespace atom {

ListValue::ListValue(const std::vector<Value::ptr> &value) :
    value_(value)
{}

void ListValue::setList(const std::vector<Value::ptr> &value)
{
    this->value_ = value;
}

const std::vector<Value::ptr> & ListValue::getList() const
{
    return value_;
}

static Value::ptr ListValue::create(std::vector<Value::ptr> value)
{
    return Value::ptr(new ListValue(value));
}

static ListValue::ptr ListValue::convert(Value::ptr from)
{
    return std::tr1::dynamic_pointer_cast<ListValue>(from);
}

char ListValue::doGetTypeTag() const
{
    return TYPE_TAG;
}

std::ostream & operator<<(std::ostream &os, const ListValue& value)
{
	os << value.getList();
    return os;
}

} // end of namespace

#endif // include guard

