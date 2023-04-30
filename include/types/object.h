#ifndef OBJECT_H
#define OBJECT_H

#include <string>
#include <memory>
#include <unordered_map>

class object
{
public:
    virtual ~object() {}
    virtual std::string to_string() const = 0; 
    std::string type_name() const;

    object &operator+(const std::shared_ptr<object> other);

    friend std::ostream& operator<< (std::ostream& stream, const object &o);
    friend std::ostream& operator<< (std::ostream& stream, const object *o);
    friend std::ostream& operator<< (std::ostream& stream, const std::shared_ptr<object> &o);

protected:

    object(std::string type_name);

private:
    
    uint16_t type_id;
    std::string name;
    static std::unordered_map<std::string, int> types;  
    static int current_id;  
};

#endif