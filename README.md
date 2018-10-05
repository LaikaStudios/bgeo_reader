# BGEO reader library and Katana Op

This repository contains code for parsing Sidefx Houdini BGEO formatted files and a Katana Op for generating an appropriate scengraph hierarchy from the BGEO file in Katana. Documentation for the schema used in the BGEO format can be found here: [HDK GA FileFormat](http://www.sidefx.com/docs/hdk/_h_d_k__g_a__using.html#HDK\_GA\_FileFormat).

## Brief History

This code base started in 2014 as a Katana Scenegraph Generator supporting files created by Houdini 13. Since then, it has become a more general library for reading in BGEO files, and we use it internally for a couple PRMan procedurals as well as the Katana Op now contained in the library. The development was driven by production needs and schedule so it has grown somewhat organically and only supports a subset of what Houdini can store in BGEO files.

## Features

* Supports BGEO files exported from Houdini 13.0 14.0 15.0 15.5 16.0 16.5
* Supports ascii, binary, and compressed files with extensions: .bgeo .bgeo.gz .bgeo.sc .geo .geo.gz .geo.sc
* The parsing library only links to Houdini's JSON library which doesn't require a license.
* Good support for Poly, Volume, Particle System, no primitive points, Packed Disk (BGEO files only), Packed Primitive, Packed Points.
* Experimental support for PolySoup, Packed Fragment, Sphere (only supports one).

## Requirements

* [SideFX](https://www.sidefx.com/) [Houdini 16.5](https://www.sidefx.com/products/houdini-fx/)
* [Foundry](https://www.foundry.com/) [Katana 2.1 2.5 3.0](https://www.foundry.com/products/katana)
* a C++11 compatible compiler

The provided make files utilize Houdini's toolkit makefiles so if you can build Houdini plugins with those makefiles you should be able to build. However, it is not robust and should be taken as more of a guide than a final build solution.

## Documentation

https://github.com/LaikaStudios/bgeo_reader/wiki

## License
Licensed under either of

 * Apache License, Version 2.0, ([LICENSE-APACHE](LICENSE-APACHE) or http://www.apache.org/licenses/LICENSE-2.0)
 * MIT license ([LICENSE-MIT](LICENSE-MIT) or http://opensource.org/licenses/MIT)

at your option.

### Contribution
Unless you explicitly state otherwise, any contribution intentionally submitted
for inclusion in the work by you, as defined in the Apache-2.0 license, shall be dual licensed as above, without any
additional terms or conditions.
