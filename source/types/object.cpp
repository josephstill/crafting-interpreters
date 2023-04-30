#include "types/object.h"

int object::current_id = 0;

std::unordered_map<std::string, int> object::types;

object::object(std::string type_name)
{
    this->name = type_name;
    auto type_info = object::types.find(type_name);
    if (type_info != object::types.end())
    {
        this->type_id = type_info->second;            
    }
    else
    {
        this->type_id = object::current_id++;
        object::types.insert({type_name, this->type_id});
    }
}

std::string object::type_name() const
{
    return this->name;
}

std::ostream& operator<<(std::ostream& stream, const object &o)
{
    stream << o.to_string();
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const object *o)
{
    stream << o->to_string();
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const std::shared_ptr<object> &o)
{
    stream << o->to_string();
    return stream;
}   