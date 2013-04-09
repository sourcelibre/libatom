/*
 * Copyright (C) 2011 Alexandre Quessy
 *
 * This file is part of Tempi.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software ither version 3 of the License, or
 * (at your option) any later version.
 * 
 * Tempi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with Tempi.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#include "entity/entitysignal.h"
//#include <boost/bind.hpp>
#include <iostream>

namespace entity {

EntitySignal::EntitySignal(
        const char *name,
        const char *short_documentation,
        const char *long_documentation,
        const char *type) :
    Documented(name, short_documentation, long_documentation),
    type_(type),
    type_strict_(true)
{}

EntitySignal::EntitySignal(
        const char *name, 
        const char *short_documentation,
        const char *long_documentation) :
    Documented(name, short_documentation, long_documentation),
    type_("*"),
    type_strict_(false)
{}

bool EntitySignal::isTypeStrict() const
{
    return type_strict_;
}

EntitySignal::~EntitySignal()
{
    // TODO
    //signal_.disconnect_all_slots();
}

std::string EntitySignal::getType() const
{
    return type_;
}

// TODO:
// EntitySignal::Signal &EntitySignal::getSignal()
// {
//     return signal_;
// }

bool EntitySignal::trigger(const atom::Message &message)
{
    if (isTypeStrict())
    {
        std::string types = atom::getTypeTags(message);
        if (types == getType().c_str())
        {
            //TODO signal_(message);
            std::cerr << "FIXME: " << __FILE__ << ":" << __FUNCTION__ << ":signals are not implemented right now." << std::endl;
            return true;
        }
        else
        {
            std::cerr << "Bad type " << types << " for signal " << getName() << " while expected " << getType() << std::endl;
            return false;
        }
    }
    else
    {
        std::cerr << "FIXME: " << __FILE__ << ":" << __FUNCTION__ << ":signals are not implemented right now." << std::endl;
        //TODO signal_(message);
        return true;
    }
}

} // end of namespace

