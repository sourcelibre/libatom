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

/**
 * @file
 * The Blob class
 */
#ifndef __ATOM_BLOB_H__
#define __ATOM_BLOB_H__

#include <cstddef>
#include <string>

namespace atom {

typedef unsigned char Byte;

/**
 * Dynamic-size binary large object.
 */
class Blob
{
    public:
        /**
         * A recommended initial allocation size is 8 (on 64-bit machines)
         * for small binary objects, and much more (powers of two) for
         * larger ones.
         */
        Blob(size_t initial_allocation_size = 1);
        ~Blob();
        /**
         * Appends a single byte to the large object.
         */
        void append(Byte data);
        /**
         * Appends some bytes to the large object.
         *
         * Note that the sizeof() operator does not give you the number of
         * elements in an array, it gives you the number of bytes a thing
         * occupies in memory.
         * This causes some confusion, because the first time many beginners
         * try to use sizeof() is often with a character string, and a char
         * is always one byte long. An int, however, will be something different.
         */
        void append(const Byte *data, size_t length);
        /**
         * Returns the number of bytes stored.
         */
        size_t getSize() const;
        /**
         * Returns the number of bytes allocated for this large object.
         * Should be a power of two.
         */
        size_t getAllocated() const;
        /**
         * Clears the blob, free its memory and sets its contents to zero.
         */
        void clear();
        /**
         * Retrieves the pointer to the bytes.
         */
        Byte * get() const;
        /**
         * Prints potentially usefull - but very verbose - information about
         * this blob.
         */
        void debugPrint() const;
        static size_t findNextLargerPowerOfTwo(size_t n);
        void setValue(const Byte *data, size_t length);
        static std::string getString(atom::Blob &blob, size_t max_length=1000);
        static std::string getHexadecimalString(const atom::Blob &blob, size_t max_length=1000, bool use_space=true, bool use_columns=true, size_t columns=24);

        bool operator==(const Blob &other) const;
        bool operator!=(const Blob &other) const;

    private:
        Byte *value_;
        size_t size_;
        size_t allocated_;
        // should be a power of two
        size_t initial_allocation_size_;
        /**
         * Returns 256, 512, 1024, 2048, etc... that is closest smaller to target.
         */
        size_t findSizeToStore(size_t target);
        void increaseSize(size_t length);
};

std::ostream &operator<<(std::ostream &os, const Blob &blob);

} // end of namespace

#endif // ifndef


