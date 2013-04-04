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
 * The BlobValue class.
 */

#ifndef __ATOM_BLOBVALUE_H__
#define __ATOM_BLOBVALUE_H__

#include <string>
#include <ostream>
#include "atom/value.h"
#include "atom/blob.h"

namespace atom {

/**
 * Stores binary data.
 */
class BlobValue: public Value
{
    public:
        typedef std::tr1::shared_ptr<BlobValue> ptr;
        static const char TYPE_TAG = 'B';
        void setValue(const Byte * value, size_t length);
        /**
         * Returns the actual bytes data.
         * Use at your own risk, since this pointer points to internal data in this class.
         */
        Byte * getValue();
        /**
         * Zeros the bytes, frees them, and make the size 0.
         */
        void clear();
        /**
         * Factory with some data to fill it up with.
         */
        static Value::ptr create(const Byte * value, size_t length);
        /**
         * Factory for an empty blob.
         */
        static Value::ptr create();
        /**
         * Returns the size of the data.
         */
        size_t getSize() const;
        /**
         * Appends some bytes to the blob.
         */
        void append(const Byte * value, size_t size);
        /**
         * Converts from a Value::ptr to a BlobValue::ptr.
         * The Value::ptr's type must be a blob!
         */
        static BlobValue::ptr convert(const Value::ptr &from);
        /**
         * Returns a string representing the data as hexadecimal.
         */
        std::string getHex() const;
        /**
         * Returns a reference to the internal Blob that is stored in this BlobValue.
         */
        const Blob& getBlob() const;

        bool operator==(const BlobValue &other) const;
        bool operator!=(const BlobValue &other) const;

    private:
        Blob blob_;
        BlobValue(const Byte *value, size_t size);
        virtual char doGetTypeTag() const;
};

std::ostream &operator<<(std::ostream &os, const BlobValue &value);

} // end of namespace

#endif // include guard

