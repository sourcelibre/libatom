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
 * The Message typedef
 */

#ifndef __ATOM_MESSAGE_H__
#define __ATOM_MESSAGE_H__

#include "atom/value.h"
#include "atom/blobvalue.h"
#include "atom/intvalue.h"
#include "atom/floatvalue.h"
#include "atom/stringvalue.h"
#include "atom/listvalue.h"
#include "atom/booleanvalue.h"
#include "atom/nullvalue.h"
#include "atom/dictvalue.h"
#include "atom/pointervalue.h"
#include <vector>
#include <map>
#include <string>
#include <ostream>

namespace atom {

typedef std::vector<Value::ptr> Message;

std::ostream & operator<<(std::ostream &os, const Message& message);
std::ostream & operator<<(std::ostream &os, const Value& value);
std::ostream & operator<<(std::ostream &os, const std::map<std::string, Value::ptr>& map);

std::string getTypeTags(const Message &message);

Message createMessage(const char *types, ...)
    throw(BadTypeTagError);

} // end of namespace

#endif // include guard

