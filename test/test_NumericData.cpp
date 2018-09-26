/*
 *  Copyright 2018 Laika, LLC. Authored by Peter Stuart
 *
 *  Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
 *  http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
 *  http://opensource.org/licenses/MIT>, at your option. This file may not be
 *  copied, modified, or distributed except according to those terms.
 */

#include <hboost/test/unit_test.hpp>

#include <UT/UT_JSONParser.h>
#include <UT/UT_IStream.h>

#include "bgeo/parser/storage.h"
#include "bgeo/parser/NumericData.h"
#include "bgeo/parser/util.h"
using namespace ika::bgeo::parser;

namespace ika
{
namespace bgeo
{
namespace test_NumericData
{

namespace test_fundamentals
{

HBOOST_AUTO_TEST_CASE(compare_equal_numeric_data)
{
    NumericData nd1(1);
    NumericData nd2(1);
    HBOOST_CHECK_EQUAL(nd1, nd2);
}

HBOOST_AUTO_TEST_CASE(compare_not_equal_numeric_data)
{
    NumericData nd1(1);
    NumericData nd2(2);
    HBOOST_CHECK_NE(nd1, nd2);
}

} // namespace test_fundamentals

namespace test_create_methods
{

HBOOST_AUTO_TEST_CASE(create_one_fpreal32_tuple4)
{
    std::vector<fpreal32> expected_tuples = {
        0, 0, 0, 1
    };

    NumericData nd = NumericData::create(1, 4, expected_tuples);

    HBOOST_CHECK_EQUAL(4, nd.tupleSize);
    HBOOST_CHECK_EQUAL(storage::Fpreal32, nd.storage);
    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_tuples.begin(), expected_tuples.end(),
                                  nd.data.beginAs<fpreal32>(),
                                  nd.data.endAs<fpreal32>());
}

HBOOST_AUTO_TEST_CASE(create_multiple_fpreal32_tuple4)
{
    std::vector<fpreal32> expected_tuples = {
        0, 0, 0, 1, 0.1, 0.2, 0.3, 0.4
    };

    NumericData nd = NumericData::create(2, 4, expected_tuples);

    HBOOST_CHECK_EQUAL(4, nd.tupleSize);
    HBOOST_CHECK_EQUAL(storage::Fpreal32, nd.storage);
    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_tuples.begin(), expected_tuples.end(),
                                  nd.data.beginAs<fpreal32>(),
                                  nd.data.endAs<fpreal32>());
}

HBOOST_AUTO_TEST_CASE(create_fpreal32_packed_4_page_size_2)
{
    std::vector<fpreal32> rawdata = {
        0, 0, 0, 1, 0.1, 0.2, 0.3, 0.4
    };

    std::vector<int32> packing(1, 4);
    std::vector<bool> flags;
    NumericData nd = NumericData::create(2, 4, packing, 2, flags, rawdata);

    HBOOST_CHECK_EQUAL(4, nd.tupleSize);
    HBOOST_CHECK_EQUAL(storage::Fpreal32, nd.storage);
    HBOOST_CHECK_EQUAL_COLLECTIONS(rawdata.begin(), rawdata.end(),
                                  nd.data.dataAs<fpreal32>(),
                                  nd.data.dataAs<fpreal32>() + nd.data.sizeAs<fpreal32>());

    HBOOST_CHECK_EQUAL_COLLECTIONS(packing.begin(), packing.end(),
                                  nd.packing.begin(), nd.packing.end());

    HBOOST_CHECK_EQUAL(2, nd.pageSize);
}

HBOOST_AUTO_TEST_CASE(create_fpreal32_packed_3_1_page_size_2)
{
    std::vector<fpreal32> rawdata = {
    //  x0 y0 z0 x1   y1   z1   w0 w1    page0
        0, 0, 0, 0.1, 0.2, 0.3, 1, 0.4,
    //  x2   y2   z2   w2                page1
        2.5, 2.6, 2.7, 2.8,
    };

    std::vector<int32> packing = { 3 , 1 };
    std::vector<bool> flags;

    NumericData nd = NumericData::create(3, 4, packing, 2, flags, rawdata);

    HBOOST_CHECK_EQUAL(4, nd.tupleSize);
    HBOOST_CHECK_EQUAL(storage::Fpreal32, nd.storage);
    HBOOST_CHECK_EQUAL_COLLECTIONS(rawdata.begin(), rawdata.end(),
                                  nd.data.beginAs<fpreal32>(),
                                  nd.data.endAs<fpreal32>());

    HBOOST_CHECK_EQUAL_COLLECTIONS(packing.begin(), packing.end(),
                                  nd.packing.begin(), nd.packing.end());

    HBOOST_CHECK_EQUAL(2, nd.pageSize);
}

HBOOST_AUTO_TEST_CASE(create_fpreal32_packed_1_1_1_1_page_size_2)
{
    std::vector<fpreal32> rawdata = {
    //  x0 x1   y0 y1   z0 z1   w0 w1    page0
        0, 0.1, 0, 0.2, 0, 0.3, 1, 0.4,
    //  x2   y2   z2   w2                page1
        2.5, 2.6, 2.7, 2.8,
    };

    std::vector<int32> packing = { 1, 1, 1, 1 };
    std::vector<bool> flags;

    NumericData nd = NumericData::create(3, 4, packing, 2, flags, rawdata);

    HBOOST_CHECK_EQUAL(4, nd.tupleSize);
    HBOOST_CHECK_EQUAL(storage::Fpreal32, nd.storage);
    HBOOST_CHECK_EQUAL_COLLECTIONS(rawdata.begin(), rawdata.end(),
                                  nd.data.beginAs<fpreal32>(),
                                  nd.data.endAs<fpreal32>());

    HBOOST_CHECK_EQUAL_COLLECTIONS(packing.begin(), packing.end(),
                                  nd.packing.begin(), nd.packing.end());

    HBOOST_CHECK_EQUAL(2, nd.pageSize);
}

HBOOST_AUTO_TEST_CASE(create_fpreal32_packed_3_1_page_size_2_constant)
{
    std::vector<fpreal32> rawdata = {
    //  x0   y0   z0            w0 w1    page0
        0.4, 0.5, 0.6,          1, 0.8,
    //  x2   y2   z2   w2                page1
        2.5, 2.6, 2.7, 2.8,
    };

    std::vector<int32> packing = { 3, 1 };
    std::vector<bool> flags = { 1, 0, 0, 0 };

    NumericData nd = NumericData::create(3, 4, packing, 2, flags, rawdata);

    HBOOST_CHECK_EQUAL(4, nd.tupleSize);
    HBOOST_CHECK_EQUAL(storage::Fpreal32, nd.storage);
    HBOOST_CHECK_EQUAL_COLLECTIONS(rawdata.begin(), rawdata.end(),
                                  nd.data.beginAs<fpreal32>(),
                                  nd.data.endAs<fpreal32>());

    HBOOST_CHECK_EQUAL_COLLECTIONS(packing.begin(), packing.end(),
                                  nd.packing.begin(), nd.packing.end());

    HBOOST_CHECK_EQUAL(2, nd.pageSize);

    HBOOST_CHECK_EQUAL_COLLECTIONS(flags.begin(), flags.end(),
                                  nd.constantPageFlags.begin(),
                                  nd.constantPageFlags.end());
}

HBOOST_AUTO_TEST_CASE(create_int32)
{
    std::vector<int32> rawdata = {
        1, 2, 3, 4
    };
    NumericData nd = NumericData::create(4, 1, rawdata);

    HBOOST_CHECK_EQUAL(1, nd.tupleSize);
    HBOOST_CHECK_EQUAL(storage::Int32, nd.storage);
    HBOOST_CHECK_EQUAL_COLLECTIONS(rawdata.begin(), rawdata.end(),
                                  nd.data.beginAs<int32>(),
                                  nd.data.endAs<int32>());
}

HBOOST_AUTO_TEST_CASE(create_int32_page_size_4_constant_page_1)
{
    std::vector<int32> rawdata = {
        1,
        2, 3, 4, 5,
        6, 7, 8, 9
    };

    std::vector<bool> flags = { 1, 0, 0 };

    NumericData nd = NumericData::create(10, 1, {}, 4, flags, rawdata);

    HBOOST_CHECK_EQUAL(1, nd.tupleSize);
    HBOOST_CHECK_EQUAL(storage::Int32, nd.storage);
    HBOOST_CHECK_EQUAL_COLLECTIONS(rawdata.begin(), rawdata.end(),
                                  nd.data.beginAs<int32>(),
                                  nd.data.endAs<int32>());

    std::vector<int32> packing = { 1 };
    HBOOST_CHECK_EQUAL_COLLECTIONS(packing.begin(), packing.end(),
                                  nd.packing.begin(), nd.packing.end());

    HBOOST_CHECK_EQUAL(4, nd.pageSize);

    HBOOST_CHECK_EQUAL_COLLECTIONS(flags.begin(), flags.end(),
                                  nd.constantPageFlags.begin(),
                                  nd.constantPageFlags.end());
}

} // namespace test_create_methods

namespace test_unpack
{

HBOOST_AUTO_TEST_CASE(unpack_fpreal32_tuple4)
{
    std::vector<fpreal32> expected_tuples = {
        0, 0, 0, 1
    };

    NumericData nd = NumericData::create(1, 4, expected_tuples);

    std::vector<fpreal32> unpacked;
    nd.getUnpackedData(unpacked);

    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_tuples.begin(), expected_tuples.end(),
                                  unpacked.begin(), unpacked.end());
}

HBOOST_AUTO_TEST_CASE(unpack_multiple_fpreal32_tuple4)
{
    std::vector<fpreal32> expected_tuples = {
        0, 0, 0, 1, 0.1, 0.2, 0.3, 0.4
    };

    NumericData nd = NumericData::create(2, 4, expected_tuples);

    std::vector<fpreal32> unpacked;
    nd.getUnpackedData(unpacked);

    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_tuples.begin(), expected_tuples.end(),
                                  unpacked.begin(), unpacked.end());
}

HBOOST_AUTO_TEST_CASE(unpack_fpreal32_packed_4_page_size_2)
{
    std::vector<fpreal32> rawdata = {
        0, 0, 0, 1, 0.1, 0.2, 0.3, 0.4
    };

    std::vector<int32> packing(1, 4);
    std::vector<bool> flags;
    NumericData nd = NumericData::create(2, 4, packing, 2, flags, rawdata);

    std::vector<fpreal32> unpacked;
    nd.getUnpackedData(unpacked);
    HBOOST_CHECK_EQUAL_COLLECTIONS(rawdata.begin(), rawdata.end(),
                                  unpacked.begin(), unpacked.end());
}


HBOOST_AUTO_TEST_CASE(unpack_read_fpreal32_packed_3_1_page_size_2)
{
    std::vector<fpreal32> rawdata = {
    //  x0 y0 z0 x1   y1   z1   w0 w1    page0
        0, 0, 0, 0.1, 0.2, 0.3, 1, 0.4,
    //  x2   y2   z2   w2                page1
        2.5, 2.6, 2.7, 2.8,
    };

    std::vector<int32> packing = { 3 , 1 };
    std::vector<bool> flags;

    NumericData nd = NumericData::create(3, 4, packing, 2, flags, rawdata);

    std::vector<fpreal32> expected_unpacked = {
        0, 0, 0, 1,
        0.1, 0.2, 0.3, 0.4,
        2.5, 2.6, 2.7, 2.8,
    };

    std::vector<fpreal32> unpacked;
    nd.getUnpackedData(unpacked);
    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_unpacked.begin(), expected_unpacked.end(),
                                  unpacked.begin(), unpacked.end());
}


HBOOST_AUTO_TEST_CASE(unpack_fpreal32_packed_1_1_1_1_page_size_2)
{
    std::vector<fpreal32> rawdata = {
    //  x0 x1   y0 y1   z0 z1   w0 w1    page0
        0, 0.1, 0, 0.2, 0, 0.3, 1, 0.4,
    //  x2   y2   z2   w2                page1
        2.5, 2.6, 2.7, 2.8,
    };

    std::vector<int32> packing = { 1, 1, 1, 1 };
    std::vector<bool> flags;

    NumericData nd = NumericData::create(3, 4, packing, 2, flags, rawdata);

    std::vector<fpreal32> expected_unpacked = {
        0, 0, 0, 1,
        0.1, 0.2, 0.3, 0.4,
        2.5, 2.6, 2.7, 2.8,
    };

    std::vector<fpreal32> unpacked;
    nd.getUnpackedData(unpacked);
    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_unpacked.begin(), expected_unpacked.end(),
                                  unpacked.begin(), unpacked.end());
}


HBOOST_AUTO_TEST_CASE(unpack_fpreal32_packed_3_1_page_size_2_constant)
{
    std::vector<fpreal32> rawdata = {
    //  x0   y0   z0            w0 w1    page0
        0.4, 0.5, 0.6,          1, 0.8,
    //  x2   y2   z2   w2                page1
        2.5, 2.6, 2.7, 2.8,
    };

    std::vector<int32> packing = { 3, 1 };
    std::vector<bool> flags = { 1, 0, 0, 0 };

    NumericData nd = NumericData::create(3, 4, packing, 2, flags, rawdata);

    std::vector<fpreal32> expected_unpacked = {
        0.4, 0.5, 0.6, 1,
        0.4, 0.5, 0.6, 0.8,
        2.5, 2.6, 2.7, 2.8
    };

    std::vector<fpreal32> unpacked;
    nd.getUnpackedData(unpacked);
    HBOOST_CHECK_EQUAL_COLLECTIONS(expected_unpacked.begin(),
                                  expected_unpacked.end(),
                                  unpacked.begin(), unpacked.end());
}

HBOOST_AUTO_TEST_CASE(unpack_int32_page_size_4_constant_page_1)
{
    std::vector<int32> rawdata = {
        1, 2, 3, 4,
        5,
        6, 7
    };

    NumericData nd = NumericData::create(10, 1, {}, 4, { 0, 1, 0 }, rawdata);

    std::vector<int32> unpacked;
    nd.getUnpackedData(unpacked);

    std::vector<int32> expected = {
        1, 2, 3, 4,
        5, 5, 5, 5,
        6, 7
    };
    HBOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(),
                                  unpacked.begin(), unpacked.end());
}

} // namespace test_unpack

namespace test_parsing
{

HBOOST_AUTO_TEST_CASE(parse_one_fpreal32_tuple4)
{
    const char* one_fpreal32_tuple4 =
    "[ \
        \"size\",4, \
        \"storage\",\"fpreal32\", \
        \"tuples\",[[0,0,0,1] \
        ] \
    ] \
    ";

    UT_IStream stream(one_fpreal32_tuple4, strlen(one_fpreal32_tuple4), UT_ISTREAM_ASCII);
    UT_AutoJSONParser parserSetup(stream);
    UT_JSONParser parser = parserSetup.parser();

    NumericData nd(1);
    nd.load(parser);

    HBOOST_CHECK_EQUAL(NumericData::create<fpreal32>(1, 4, {0, 0, 0, 1}), nd);
}

HBOOST_AUTO_TEST_CASE(parse_multiple_fpreal32_tuple4)
{
    const char* multiple_fpreal32_tuple4 =
    "[ \
        \"size\",4, \
        \"storage\",\"fpreal32\", \
        \"tuples\",[[0,0,0,1],[0.1,0.2,0.3,0.4] \
        ] \
    ] \
    ";

    UT_IStream stream(multiple_fpreal32_tuple4,
                      strlen(multiple_fpreal32_tuple4),
                      UT_ISTREAM_ASCII);
    UT_AutoJSONParser parserSetup(stream);
    UT_JSONParser parser = parserSetup.parser();

    NumericData nd(2);
    nd.load(parser);

    auto expected = NumericData::create<fpreal32>(2, 4, {0, 0, 0, 1, 0.1, 0.2, 0.3, 0.4});
    HBOOST_CHECK_EQUAL(expected, nd);
}

HBOOST_AUTO_TEST_CASE(parse_fpreal32_packed_4_page_size_2)
{
    const char* fpreal32_packed_4_page_size_2 =
    "[ \
        \"size\",4, \
        \"storage\",\"fpreal32\", \
        \"packing\",[4], \
        \"pagesize\",2, \
        \"rawpagedata\",[0,0,0,1,0.1,0.2,0.3,0.4 \
        ] \
    ] \
    ";

    UT_IStream stream(fpreal32_packed_4_page_size_2,
                      strlen(fpreal32_packed_4_page_size_2),
                      UT_ISTREAM_ASCII);
    UT_AutoJSONParser parserSetup(stream);
    UT_JSONParser parser = parserSetup.parser();

    NumericData nd(2);
    nd.load(parser);

    auto expected = NumericData::create<fpreal32>(2, 4, {4}, 2, {},
        {0, 0, 0, 1, 0.1, 0.2, 0.3, 0.4});
    HBOOST_CHECK_EQUAL(expected, nd);
}

HBOOST_AUTO_TEST_CASE(parse_fpreal32_packed_3_1_page_size_2)
{
    const char* fpreal32_packed_3_1_page_size_2 = "[ \
        \"size\",4, \
        \"storage\",\"fpreal32\", \
        \"packing\",[3,1], \
        \"pagesize\",2, \
        \"rawpagedata\",[0,0,0, 0.1,0.2,0.3, 1,0.4, \
                         2.5,2.6,2.7,2.8 \
        ] \
    ] \
    ";

    UT_IStream stream(fpreal32_packed_3_1_page_size_2,
                      strlen(fpreal32_packed_3_1_page_size_2),
                      UT_ISTREAM_ASCII);
    UT_AutoJSONParser parserSetup(stream);
    UT_JSONParser parser = parserSetup.parser();

    NumericData nd(3);
    nd.load(parser);

    std::vector<fpreal32> rawdata = {
    //  x0 y0 z0 x1   y1   z1   w0 w1    page0
        0, 0, 0, 0.1, 0.2, 0.3, 1, 0.4,
    //  x2   y2   z2   w2                page1
        2.5, 2.6, 2.7, 2.8,
    };

    HBOOST_CHECK_EQUAL(NumericData::create(3, 4, {3, 1}, 2, {}, rawdata), nd);
}

HBOOST_AUTO_TEST_CASE(read_fpreal32_packed_1_1_1_1_page_size_2)
{
    const char* fpreal32_packed_1_1_1_1_page_size_2 = "[ \
        \"size\",4, \
        \"storage\",\"fpreal32\", \
        \"packing\",[1,1,1,1], \
        \"pagesize\",2, \
        \"rawpagedata\",[0,0.1, 0,0.2, 0,0.3, 1,0.4, \
                         2.5,2.6,2.7,2.8 \
        ] \
    ] \
    ";

    UT_IStream stream(fpreal32_packed_1_1_1_1_page_size_2,
                      strlen(fpreal32_packed_1_1_1_1_page_size_2),
                      UT_ISTREAM_ASCII);
    UT_AutoJSONParser parserSetup(stream);
    UT_JSONParser parser = parserSetup.parser();

    NumericData nd(3);
    nd.load(parser);

    std::vector<fpreal32> rawdata = {
    //  x0 x1   y0 y1   z0 z1   w0 w1    page0
        0, 0.1, 0, 0.2, 0, 0.3, 1, 0.4,
    //  x2   y2   z2   w2                page1
        2.5, 2.6, 2.7, 2.8,
    };

    HBOOST_CHECK_EQUAL(NumericData::create(3, 4, {1, 1, 1, 1}, 2, {}, rawdata), nd);
}

HBOOST_AUTO_TEST_CASE(read_fpreal32_packed_3_1_page_size_2_constant)
{
    const char* fpreal32_packed_3_1_page_size_2 = "[ \
        \"size\",4, \
        \"storage\",\"fpreal32\", \
        \"packing\",[3,1], \
        \"pagesize\",2, \
        \"constantpageflags\",[[1,0],[0,0]], \
        \"rawpagedata\",[0.4,0.5,0.6,1,0.8,\
                         2.5,2.6,2.7,2.8 \
        ] \
    ] \
    ";

    UT_IStream stream(fpreal32_packed_3_1_page_size_2,
                      strlen(fpreal32_packed_3_1_page_size_2),
                      UT_ISTREAM_ASCII);
    UT_AutoJSONParser parserSetup(stream);
    UT_JSONParser parser = parserSetup.parser();

    NumericData nd(3);
    nd.load(parser);

    std::vector<fpreal32> rawdata = {
    //  x0   y0   z0            w0 w1    page0
        0.4, 0.5, 0.6,          1, 0.8,
    //  x2   y2   z2   w2                page1
        2.5, 2.6, 2.7, 2.8,
    };

    HBOOST_CHECK_EQUAL(NumericData::create(3, 4, {3, 1}, 2, {1, 0, 0, 0}, rawdata), nd);
}

HBOOST_AUTO_TEST_CASE(parse_unspecified_packing_is_tuple_size)
{
    const char* json =
    "[ \
        \"size\",4, \
        \"storage\",\"fpreal32\", \
        \"pagesize\",2, \
        \"constantpageflags\",[[1]], \
        \"rawpagedata\",[1.1, 2.2, 3.3, 4.4] \
    ] \
    ";

    UT_IStream stream(json, strlen(json), UT_ISTREAM_ASCII);
    UT_AutoJSONParser parserSetup(stream);
    UT_JSONParser parser = parserSetup.parser();

    NumericData nd(2);
    nd.load(parser);

    std::vector<fpreal32> rawdata = { 1.1, 2.2, 3.3, 4.4 };
    HBOOST_CHECK_EQUAL_COLLECTIONS(rawdata.begin(), rawdata.end(),
                                  nd.data.beginAs<fpreal32>(),
                                  nd.data.endAs<fpreal32>());

    std::vector<fpreal32> unpacked;
    nd.getUnpackedData(unpacked);

    std::vector<fpreal32> expected = {
        1.1, 2.2, 3.3, 4.4,
        1.1, 2.2, 3.3, 4.4
    };
    HBOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(),
                                  unpacked.begin(), unpacked.end());
}

HBOOST_AUTO_TEST_CASE(parse_int32_page_size_4_constant_page_1)
{
    const char* json =
    "[ \
        \"size\",1, \
        \"storage\",\"int32\", \
        \"pagesize\",4, \
        \"constantpageflags\",[[0, 1, 0]], \
        \"rawpagedata\",[ \
            1, 2, 3, 4, \
            5, \
            6, 7 \
        ] \
    ] \
    ";

    UT_IStream stream(json, strlen(json), UT_ISTREAM_ASCII);
    UT_AutoJSONParser parserSetup(stream);
    UT_JSONParser parser = parserSetup.parser();

    NumericData nd(10);
    nd.load(parser);

    std::vector<int32> rawdata = {
        1, 2, 3, 4,
        5,
        6, 7
    };

    auto expected = NumericData::create(10, 1, {}, 4, { 0, 1, 0 }, rawdata);

    HBOOST_CHECK_EQUAL(expected, nd);
}

}

} // namespace test_NumericData
} // namespace bgeo
} // namespace ika
