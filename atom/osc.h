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
 * Liblo utilities
 */

#ifndef __ATOM_OSC_H__
#define __ATOM_OSC_H__

#include "atom/message.h"
#include <lo/lo.h>

namespace atom {

bool message_build_from_lo_args(Message &result, const char * types, lo_arg ** argv, int argc);
bool message_build_to_lo_message(Message &source, lo_message &message);

} // end namespace

#endif // include guard

