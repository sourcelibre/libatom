#include "tempi/entity.h"
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <tr1/memory>

using namespace tempi;

class EntityMap
{
    public:
        typedef std::tr1::shared_ptr<EntityMap> ptr;
        typedef std::map<std::string, std::map<std::string, Entity::ptr> > MapType;
        template<typename T>
        typename std::tr1::shared_ptr<T> getEntity(const char *type, const char *name)
        {
            return std::tr1::dynamic_pointer_cast<T>(map_[type][name]);
        }
        // template<typename T>
        // bool write(const char *type, const char *name, T::ptr value)
        // {
        //     T::ptr tmp = std::tr1::dynamic_pointer_cast<T>(value);
        //     map_[type][name] = tmp;
        //     return true;
        // }
        template<typename T>
        bool createEntity(const char *type, const char *name, std::tr1::shared_ptr<T> value)
        {
            if (this->hasType(type))
            {
                if (this->hasEntity(type, name))
                    return false;
                std::string typeString(type);
                std::string nameString(name);
                Entity::ptr tmp = std::tr1::dynamic_pointer_cast<Entity>(value);
                map_[type][name] = tmp;
                return true;
            }
            else
                return false;
        }
        bool createType(const char *type)
        {
            if (this->hasType(type))
                return false;
            else
            {
                std::string typeString(type);
                std::map<std::string, Entity::ptr> tmp;
                this->map_[typeString] = tmp;
                return true;
            }
        }
        std::vector<std::string> listTypes()
        {
            std::vector<std::string> ret;
            MapType::const_iterator iter;
            for (iter = this->map_.begin(); iter != this->map_.end(); ++iter)
            {
                ret.push_back((*iter).first);
            }
            return ret;
        }
        bool hasType(const char *type)
        {
            std::string typeString(type);
            MapType::iterator iter = map_.find(typeString);
            if (iter == map_.end())
                return false;
            else
                return true;
        }
        bool hasEntity(const char *type, const char *name)
        {
            if (! hasType(type))
                return false;
            std::string typeString(type);
            std::string nameString(name);
            std::map<std::string, Entity::ptr>::iterator iter = map_[typeString].find(nameString);
            if (iter == map_[typeString].end())
                return false;
            else
                return true;
        }
        bool listEntities(const char *type, std::vector<std::string> &ret)
        {
            std::string typeString(type);
            if (! this->hasType(type))
                return false;
            std::map<std::string, Entity::ptr>::const_iterator iter;
            for (iter = this->map_[typeString].begin(); iter != this->map_[typeString].end(); ++iter)
            {
                ret.push_back((*iter).first);
            }
            return true;
        }

        bool destroyEntity(const char *type, const char *name)
        {
            if (this->hasEntity(type, name))
            {
                std::string typeString(type);
                std::string nameString(name);
                std::map<std::string, Entity::ptr>::iterator iter = map_[typeString].find(nameString);
                map_[typeString].erase(iter);
                return true;
            }
            else
                return false;
        }
        bool destroyType(const char *type)
        {
            if (this->hasType(type))
            {
                std::string typeString(type);
                MapType::iterator iter = map_.find(typeString);
                map_.erase(iter);
                return true;
            }
            else
                return false;
        }
    private:
        MapType map_;
};

class Foo : public Entity
{
    public:
        typedef std::tr1::shared_ptr<Foo> ptr;
        Foo(const char *name) :
            Entity(name)
        {}
};
class FooEgg : public Foo
{
    public:
        typedef std::tr1::shared_ptr<FooEgg> ptr;
        FooEgg(const char *name) :
            Foo(name)
        {}
};
class Bar : public Entity
{
    public:
        typedef std::tr1::shared_ptr<Bar> ptr;
        Bar(const char *name) :
            Entity(name)
        {}
};
class BarSpam : public Bar
{
    public:
        typedef std::tr1::shared_ptr<BarSpam> ptr;
        BarSpam(const char *name) :
            Bar(name)
        {}
};

int main(int argc, char **argv)
{
    EntityMap map;

    map.createType("bar");
    BarSpam::ptr spam(new BarSpam("spam"));
    map.createEntity<BarSpam>("bar", spam->getName().c_str(), spam);

    map.createType("foo");
    FooEgg::ptr egg(new FooEgg("egg"));
    map.createEntity<FooEgg>("foo", egg->getName().c_str(), egg);

    std::vector<std::string> types = map.listTypes();
    std::vector<std::string>::const_iterator iter;
    for (iter = types.begin(); iter != types.end(); ++iter)
        std::cout << "type " << (*iter) << std::endl;

    std::vector<std::string> entities;
    map.listEntities("foo", entities);
    for (iter = entities.begin(); iter != entities.end(); ++iter)
        std::cout << "foo " << (*iter) << std::endl;

    return 0;
}

