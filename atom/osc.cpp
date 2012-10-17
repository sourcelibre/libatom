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

#include "atom/osc.h"


namespace atom {

bool message_build_from_lo_args(Message &result, const char * types, lo_arg ** argv, int argc)
{
    bool ok = true;
    for (int i = 0; i < argc; i++)
    {
        switch (types[i])
        {
            case 'i':
                result.push_back(IntValue::create(argv[i]->i));
                break;
            case 'f':
                result.push_back(FloatValue::create(argv[i]->f));
                break;
            case 'd':
                result.push_back(IntValue::create(argv[i]->d));
                break;
            case 's':
                result.push_back(StringValue::create(static_cast<const char *>(&argv[i]->s)));
                break;
            case 'T':
                result.push_back(BooleanValue::create(true));
                break;
            case 'F':
                result.push_back(BooleanValue::create(false));
                break;
            default:
                ok = false;
        }
    }
    return ok;
}

} // end of namespace

