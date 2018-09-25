/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef BGEO_PARSER_PRIMITIVES_H
#define BGEO_PARSER_PRIMITIVES_H

#include <UT/UT_JSONParser.h>

namespace ika
{
namespace bgeo
{
namespace parser
{

class Detail;
class Primitive;
class Primitives
{
public:
    Primitives(const Detail& detail);
    ~Primitives();

    void load(UT_JSONParser& parser);
    void loadSharedData(UT_JSONParser& parser);

    friend std::ostream& operator << (std::ostream& co, const Primitives& primitives);

    const Primitive* getPrimitive(int64 index) const;
    int64 getCount() const
    {
        return primitives.size();
    }

private:
    typedef std::vector<Primitive*> PrimitiveVector;
    PrimitiveVector primitives;

    const Detail& detail;
};

} // namespace parser
} // namespace ika
} // namespace bgeo

#endif // BGEO_PARSER_PRIMITIVES_H
