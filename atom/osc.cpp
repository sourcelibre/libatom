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

bool message_build_to_lo_message(Message &source, lo_message &message)
{
    bool ok = true;

    Message::const_iterator iter;
    for(iter = source.begin(); iter != source.end(); ++iter)
    {
        if (iter->get()->getTypeTag() == IntValue::TYPE_TAG)
            lo_message_add_int32(message, IntValue::convert(*iter)->getInt());
        else if (iter->get()->getTypeTag() == StringValue::TYPE_TAG)
            lo_message_add_string(message, StringValue::convert(*iter)->getString().c_str());
        else if (iter->get()->getTypeTag() == FloatValue::TYPE_TAG)
            lo_message_add_float(message, FloatValue::convert(*iter)->getFloat());
        else if (iter->get()->getTypeTag() == BooleanValue::TYPE_TAG)
        {
            bool value = BooleanValue::convert(*iter)->getBoolean();
            if (value)
                lo_message_add_true(message);
            else
                lo_message_add_false(message);
        }
        else
            ok = false;
    }

    return ok;
}

} // end of namespace

