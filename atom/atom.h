/*
 * This file is part of Spatosc.
 *
 * Copyright (c) 2010 Society for Arts and Technologies <info@sat.qc.ca>
 *
 * Spatosc is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Spatosc is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Spatosc.  If not, see <http://www.gnu.org/licenses/>.
 */

/** @file
 * The Atom class.
 */

#ifndef _ATOM_H_
#define _ATOM_H_

#include <vector>
#include <string>
#include <iostream>
#include <lo/lo.h>

namespace atom {

/**
 * Contains a value.
 * See boost::any
 */
class Atom
{
    public:
        Atom(double value);
        Atom(float value);
        Atom(const char *value);
        Atom(int value);
        Atom(bool value);
        bool isDouble() const;
        bool isFloat() const;
        bool isString() const;
        bool isInt() const;
        bool isBool() const;
        std::string getString() const;
        void getString(std::string &result) const;
        double getDouble() const;
        double getFloat() const;
        int getInt() const;
        char getType() const;
        bool getBool() const;
    private:
        typedef enum
        {
            ATOM_DOUBLE = 'd',
            ATOM_STRING = 's',
            ATOM_FLOAT = 'f',
            ATOM_INT = 'i',
            ATOM_BOOL = 'b'
        } Type;

        Type type_;
        double double_value_;
        float float_value_;
        int int_value_;
        int bool_value_;
        std::string string_value_;
};

typedef std::vector<Atom> Message;

std::string message_get_types(const Message &message);
std::ostream & operator<< (std::ostream &out, const Atom &atom);
std::ostream & operator<< (std::ostream &out, const Message &message);

bool message_build_from_lo_args(Message &result, const char * types, lo_arg ** argv, int argc);

} // end namespace spatosc

#endif // include guard

