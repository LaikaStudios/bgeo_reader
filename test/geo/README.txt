
Description of geo files:

badheader.geo: For testing header error checking.
    The json file finishes an array before it ought in the "header".

grid.geo: For testing 1 poly.
    Contains a single quad.

grid_tetra.geo: For testing poly run.
    Contains a quad and disconnected tetrahedron.

sphere_grid.geo: For testing multiple primitives especially since P and uv for each
    primitive should be a subset of the whole.

points_noprim.geo: For testing point cloud from points only.

points_partsys.geo: For testing poing cloud from particle system primitive.

vol.geo: For testing single volume.
