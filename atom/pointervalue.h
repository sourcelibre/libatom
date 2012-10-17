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
 * The PointerValue class.
 */

#ifndef __ATOM_POINTERVALUE_H__
#define __ATOM_POINTERVALUE_H__

#include "atom/value.h"

namespace atom {

/**
 * Base class for objects to store in a PointerValue.
 * Extend this class to store data into PointerValue
 */
class AbstractObject
{
    public:
        typedef std::tr1::shared_ptr<AbstractObject> ptr;
};

/**
 * Stores a shared pointer to a child of the AbstractObject class.
 */
class PointerValue: public Value
{
    public:
        typedef std::tr1::shared_ptr<PointerValue> ptr;
        static const char TYPE_TAG = 'P';
        PointerValue(AbstractObject::ptr &value) :
            value_(value)
        {}
        void setPointer(AbstractObject::ptr &value)
        {
            this->value_ = value;
        }
        AbstractObject::ptr & getPointer()
        {
            return value_;
        }
        static Value::ptr create(AbstractObject::ptr value)
        {
            return Value::ptr(new PointerValue(value));
        }
        static PointerValue::ptr convert(Value::ptr from)
        {
            return std::tr1::dynamic_pointer_cast<PointerValue>(from);
        }
    private:
        AbstractObject::ptr value_;
        virtual char doGetTypeTag() const
        {
            return TYPE_TAG;
        }
};

} // end of namespace

#endif // include guard

