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
 * The Value class.
 */

#ifndef __ATOM_VALUE_H__
#define __ATOM_VALUE_H__

#include <tr1/memory>

namespace atom {

typedef char TypeTag;

/**
 * Generic container for data.
 */
class Value
{
    public:
        typedef std::tr1::shared_ptr<Value> ptr;

        TypeTag getTypeTag() const;
        bool isType(char type_tag) const;
        virtual ~Value() {}
    private:
        virtual char doGetTypeTag() const = 0;
};

} // end of namespace

#endif // include guard

