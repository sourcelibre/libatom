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
 * The BadTypeTagError class.
 */

#ifndef __ATOM_EXCEPTIONS_H__
#define __ATOM_EXCEPTIONS_H__

#include <stdexcept>

namespace atom {

/**
 * Base class for errors.
 */
class BaseException : public std::runtime_error
{
    public:
        BaseException(const char *error_message) :
            std::runtime_error(error_message)
        {}
        BaseException() :
            std::runtime_error("")
        {}
};

/**
 * Error when type tag is not what is expected.
 */
class BadTypeTagError : public BaseException
{
    public:
        BadTypeTagError(const char *error_message) :
            BaseException(error_message)
        {}
};

} // end of namespace

#endif // include guard

