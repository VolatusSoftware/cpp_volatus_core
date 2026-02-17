#ifndef volatusconfig_h_
#define volatusconfig_h_

#include <memory>
#include <string>

#include "simdjson.h"

using namespace simdjson;

class VolatusConfig : public std::enable_shared_from_this<VolatusConfig>
{
public:
    VolatusConfig();

    //Destructor
    ~VolatusConfig();

    //Copy constructor
    VolatusConfig(const VolatusConfig& other);

    //Move constructor
    VolatusConfig(VolatusConfig&& from) noexcept;

    //Copy Assignment
    VolatusConfig& operator=(const VolatusConfig& other);

    //Move Assignment
    VolatusConfig& operator=(VolatusConfig&& from);

private:
    std::unique_ptr<
};

#endif //volatusconfig_h_
