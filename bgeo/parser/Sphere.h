/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef BGEO_PARSER_SPHERE_H
#define BGEO_PARSER_SPHERE_H

#include "Primitive.h"

namespace ika
{
namespace bgeo
{
namespace parser
{

class Sphere : public Primitive
{
public:
    Sphere(const Detail& detail);

    /*virtual*/ PrimType getType() const
    {
        return SphereType;
    }

    /*virtual*/ void loadData(UT_JSONParser &parser);

    /*virtual*/ std::ostream& encode(std::ostream& co) const;

    void getTranslate(fpreal64 translate[3]) const;
    void getMatrix(fpreal64 matrix[16]) const;

    int32 vertex;
    double transform[9];
};

} // namespace parser
} // namespace ika
} // namespace bgeo

#endif // BGEO_PARSER_SPHERE_H
