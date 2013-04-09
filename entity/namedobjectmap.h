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

/**
 * @file
 * The NamedObjectMap template class.
 */
#ifndef __ENTITY_NAMEDOBJECTMAP_H__
#define __ENTITY_NAMEDOBJECTMAP_H__

#include <map>
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include "entity/namedobject.h"
#include "entity/exceptions.h"
// #include "entity/logger.h"
#include <tr1/memory>

namespace entity {

/**
 * Map containing named instances of children of NamedObject.
 * T must be a child of NamedObject.
 */
template <typename T>
class NamedObjectMap
{
    public:
        typedef std::tr1::shared_ptr<T> T_ptr;
        typedef std::map<std::string, T_ptr> MapType;
        typedef typename MapType::const_iterator ConstIter;
        typedef typename MapType::iterator Iter;
        /**
         * Adds a named object to this map.
         */
        void add(T_ptr entity)
            throw(BadIndexException)
        {
            if (entity.get() == 0)
            {
                std::cerr << "Null pointer in " << "NamedObjectMap::" << __FUNCTION__ << std::endl; // FIXME: throw another exception type?
            }
            if (has(entity->getName().c_str()))
            {
                std::ostringstream os;
                os << "ERROR in NamedObjectMap::" << __FUNCTION__ << ": Already has entity named " << entity->getName();
                throw (BadIndexException(os.str().c_str()));
            }
            objects_[entity->getName()] = entity;
        }
        /**
         * Checks if this map has an named object named with a given name.
         */
        bool has(const char *name) const
            throw(BadIndexException)
        {
            if (name == 0)
                throwNullStringException(__FUNCTION__);
            return (objects_.find(std::string(name)) != objects_.end());
        }
        /**
         * Lists the names of all the object in this map.
         */
        std::vector<std::string> listNames() const
        {
            std::vector<std::string> ret;
            ConstIter iter;
            for (iter = objects_.begin(); iter != objects_.end(); ++iter)
                ret.push_back((*iter).first);
            return ret;
        }
        /**
         * Removes a named object with a given name from this map.
         */
        void remove(const char *name)
            throw(BadIndexException)
        {
            if (name == 0)
                throwNullStringException(__FUNCTION__);
            if (! has(name))
            {
                std::ostringstream os;
                os << "ERROR in NamedObjectMap::" << __FUNCTION__ << ": Map doesn't have an entity named " << name;
                throw (BadIndexException(os.str().c_str()));
            }
            Iter iter = objects_.find(std::string(name));
            objects_.erase(iter);
        }
        /**
         * Retrieves a named object in this map.
         */
        T_ptr get(const char *name) const
            throw(BadIndexException)
        {
            if (name == 0)
                throwNullStringException(__FUNCTION__);
            ConstIter iter = objects_.find(std::string(name));
            if (iter == objects_.end())
            {
                std::ostringstream os;
                os << "ERROR in NamedObjectMap::" << __FUNCTION__ << ": Map doesn't have an entity named \"" << name << "\".";
                os << " Names are: ";
                ConstIter iter2;
                for (iter2 = objects_.begin(); iter2 != objects_.end(); ++iter2)
                {
                    if (iter2 != objects_.begin())
                        os << " ";
                    os << (*iter2).first;
                }
                throw (BadIndexException(os.str().c_str()));
            }
            return (*iter).second;
        }
    private:
        void throwNullStringException(const char *method_name) const
            throw(BadIndexException)
        {
                std::ostringstream os;
                os << "ERROR in NamedObjectMap::" << method_name << ": Got a null string as a NamedObject name.";
                throw (BadIndexException(os.str().c_str()));
        }
        MapType objects_;
};

} // end of namespace

#endif // ifndef

