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

#include "atom/blobvalue.h"

namespace atom {

void BlobValue::setValue(const Byte * value, size_t length)
{
    blob_.setValue(value, length);
}

void BlobValue::append(const Byte * value, size_t length)
{
    blob_.append(value, length);
}

Byte * BlobValue::getValue()
{
    return blob_.get();
}

size_t BlobValue::getSize() const
{
    return blob_.getSize();
}

void BlobValue::clear()
{
    return blob_.clear();
}

Value::ptr BlobValue::create(const Byte * value, size_t length)
{
    BlobValue::ptr ret(new BlobValue(value, length));
    return std::tr1::static_pointer_cast<Value>(ret);
}

Value::ptr BlobValue::create()
{
    Byte *empty = NULL;
    BlobValue::ptr ret(new BlobValue(empty, 0));
    return std::tr1::static_pointer_cast<Value>(ret);
}

BlobValue::ptr BlobValue::convert(const Value::ptr &from)
{
    return std::tr1::dynamic_pointer_cast<BlobValue>(from);
}

BlobValue::BlobValue(const Byte *value, size_t length)
{
    blob_.setValue(value, length);
}

char BlobValue::doGetTypeTag() const
{
    return TYPE_TAG;
}

std::string BlobValue::getHex() const
{
    static const size_t MAX_LENGTH = 20;
    static const bool USE_SPACES = false;
    static const bool USE_COLS = false;
    return Blob::getHexadecimalString(this->blob_, MAX_LENGTH, USE_SPACES, USE_COLS);
}

const Blob& BlobValue::getBlob() const
{
    return blob_;
}

std::ostream &operator<<(std::ostream &os, const BlobValue &value)
{
    os << value.getBlob();
    return os;
}

bool BlobValue::operator==(const BlobValue &other) const
{
    return this->blob_ == other.getBlob();
}

bool BlobValue::operator!=(const BlobValue &other) const
{
    return this->blob_ != other.getBlob();
}

} // end of namespace

