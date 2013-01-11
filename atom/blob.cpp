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

#include <iostream>
#include <stdlib.h>
#include <cstring>
#include "atom/blob.h"

namespace atom {

Blob::Blob(size_t initial_allocation_size) :
    size_(0)
{
    initial_allocation_size_ = findNextLargerPowerOfTwo(initial_allocation_size);
    allocated_ = initial_allocation_size_;
    value_ = (char *) malloc(initial_allocation_size_);
    memset(value_, 0, initial_allocation_size_);
}

char * Blob::get() const
{
    return value_;
}

Blob::~Blob()
{
    free(value_);
}

void Blob::append(char data)
{
    char array[1];
    array[0] = data;
    append(array, 1);
}

void Blob::append(const char *data, size_t length)
{
    size_t newsize = size_ + length;
    if (newsize > allocated_)
    {
        size_t resize_to = findSizeToStore(newsize);
        increaseSize(resize_to);
    }
    memcpy((void *) (value_ + size_), (const void *) data, length);
    //memcpy((void *) (& value_[size_]), (const void *) data, length);
    size_ = size_ + length;
}

void Blob::increaseSize(size_t size)
{
    size_t how_many_byte_more = size - allocated_;
    value_ = (char *) realloc((void *) value_, size);
    memset(value_ + allocated_, 0, how_many_byte_more);
    allocated_ = size;
}

size_t Blob::findSizeToStore(size_t target)
{
    size_t ret = allocated_;
    while (ret < target)
        ret = ret * 2;
    return ret;
}

size_t Blob::findNextLargerPowerOfTwo(size_t n)
{
    size_t ret = 1;
    while (ret < n)
        ret *= 2;
    return ret;
}

size_t Blob::getSize() const
{
    return size_;
}

size_t Blob::getAllocated() const
{
    return allocated_;
}

void Blob::clear()
{
    free(value_);
    value_ = (char *) malloc(initial_allocation_size_);
    memset(value_, 0, initial_allocation_size_);
    allocated_ = initial_allocation_size_;
}

void Blob::debugPrint() const
{
    std::cout << "-----------" << std::endl;
    std::cout << "Blob info: " << std::endl;
    std::cout << " size: " << getSize() << std::endl;
    std::cout << " allocated: " << getAllocated() << std::endl;
    std::cout << " value: ";
    for (size_t i = 0; i < getSize(); i++)
    {
        std::cout << ( (int) value_[i] ) << " ";
    }
    for (size_t i = getSize(); i < getAllocated(); i++)
    {
        std::cout << "_ ";
    }
    std::cout << std::endl;
    std::cout << " text: " << value_ << std::endl; // maybe it doesnt end with zero!
    std::cout << "-----------" << std::endl;
}

} // end of namespace

