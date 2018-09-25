/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#ifndef BGEO_PART_H
#define BGEO_PART_H

#include <vector>
#include <cinttypes>

#include "rtti.h"
#include "Bgeo.h"

namespace ika
{
namespace bgeo
{

namespace parser
{
class Part;
}

class Part : public Primitive
{
    RTTI_DECLARE(Prim, Primitive)

public:
    // FIXME probably ought to be shared ptr
    Part(const parser::Part& part);

    void getPointList(std::vector<int32_t>& points) const;
    void getVertexList(std::vector<int32_t>& vertices) const;

    /*virtual*/ int32_t getVertexCount() const;

private:
    const parser::Part& m_part;
};

} // namespace ika
} // namespace bgeo

#endif // BGEO_PART_H
