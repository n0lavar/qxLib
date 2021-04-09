//==============================================================================
//
//!\file                            geom.inl
//
//!\brief       Contains functions for creating primitives geometry
//!\details     ~
//
//!\author      Khrapov
//!\date        4.04.2021
//!\copyright   (c) Nick Khrapov, 2021. All right reserved.
//
//==============================================================================

namespace qx
{

namespace detail
{

inline indices transform_triangle_indices_to_lines(const indices& triangles)
{
    indices lines;

    for (size_t i = 0; i < triangles.size(); i += 3)
    {
        lines.push_back(triangles[i + 0]);
        lines.push_back(triangles[i + 1]);

        lines.push_back(triangles[i + 1]);
        lines.push_back(triangles[i + 2]);

        lines.push_back(triangles[i + 2]);
        lines.push_back(triangles[i + 0]);
    }

    return lines;
}

}

//==============================================================================
//!\fn                      qx::create_parallelogram
//
//!\brief  Create parallelogram geometry
//!\param  fSide1 - side 1 length
//!\param  fSide2 - side 2 length
//!\param  fSide3 - side 3 length
//!\retval        - parallelogram geometry
//!\author Khrapov
//!\date   4.04.2021
//==============================================================================
inline geometry create_parallelogram(float fSide1, float fSide2, float fSide3)
{
    const float fHalfSide1 = fSide1 / 2.f;
    const float fHalfSide2 = fSide2 / 2.f;
    const float fHalfSide3 = fSide3 / 2.f;

    return
    {
        {
            { -fHalfSide1, -fHalfSide2, -fHalfSide3 },
            {  fHalfSide1, -fHalfSide2, -fHalfSide3 },
            {  fHalfSide1,  fHalfSide2, -fHalfSide3 },
            { -fHalfSide1,  fHalfSide2, -fHalfSide3 },
            { -fHalfSide1, -fHalfSide2,  fHalfSide3 },
            {  fHalfSide1, -fHalfSide2,  fHalfSide3 },
            {  fHalfSide1,  fHalfSide2,  fHalfSide3 },
            { -fHalfSide1,  fHalfSide2,  fHalfSide3 }
        },
        {
            3, 1, 0,
            2, 1, 3,
            2, 5, 1,
            6, 5, 2,
            6, 4, 5,
            7, 4, 6,
            7, 0, 4,
            3, 0, 7,
            7, 2, 3,
            6, 2, 7,
            0, 5, 4,
            1, 5, 0,
        },
        draw_mode::triangles_list
    };
}

//==============================================================================
//!\fn                   qx::create_parallelogram_lines
//
//!\brief  Create parallelogram geometry for lines drawing
//!\param  fSide1 - side 1 length
//!\param  fSide2 - side 2 length
//!\param  fSide3 - side 3 length
//!\retval        - parallelogram geometry
//!\author Khrapov
//!\date   9.04.2021
//==============================================================================
inline geometry create_parallelogram_lines(
    float fSide1,
    float fSide2,
    float fSide3)
{
    auto geom = create_parallelogram(fSide1, fSide2, fSide3);
    geom.eDrawMode = draw_mode::lines_list;
    geom.geomIndices = detail::transform_triangle_indices_to_lines(geom.geomIndices);
    return geom;
}

//==============================================================================
//!\fn                          qx::create_cube
//
//!\brief  Create cube geometry
//!\param  fSide - cube side length
//!\retval       - cube geometry
//!\author Khrapov
//!\date   4.04.2021
//==============================================================================
inline geometry create_cube(float fSide)
{
    return create_parallelogram(fSide, fSide, fSide);
}

//==============================================================================
//!\fn                       qx::create_cube_lines
//
//!\brief  Create cube geometry for lines drawing
//!\param  fSide - cube side length
//!\retval       - cube geometry
//!\author Khrapov
//!\date   9.04.2021
//==============================================================================
inline geometry create_cube_lines(float fSide)
{
    auto geom = create_cube(fSide);
    geom.eDrawMode = draw_mode::lines_list;
    geom.geomIndices = detail::transform_triangle_indices_to_lines(geom.geomIndices);
    return geom;
}

//==============================================================================
//!\fn                       qx::create_icosahedron
//
//!\brief  Create icosahedron geometry
//!\param  fRadius - icosahedron radius
//!\retval         - icosahedron geometry
//!\author Khrapov
//!\date   5.04.2021
//==============================================================================
inline geometry create_icosahedron(float fRadius)
{
    const float X = 0.525731112119133606f * fRadius;
    const float Z = 0.850650808352039932f * fRadius;

    return
    {
        { {
            {  -X, 0.f,   Z },
            {   X, 0.f,   Z },
            {  -X, 0.f,  -Z },
            {   X, 0.f,  -Z },
            { 0.f,   Z,   X },
            { 0.f,   Z,  -X },
            { 0.f,  -Z,   X },
            { 0.f,  -Z,  -X },
            {   Z,   X, 0.f },
            {  -Z,   X, 0.f },
            {   Z,  -X, 0.f },
            {  -Z,  -X, 0.f }
        } },
        {
              1,  4,  0,
              4,  9,  0,
              4,  5,  9,
              8,  5,  4,
              1,  8,  4,
              1, 10,  8,
             10,  3,  8,
              8,  3,  5,
              3,  2,  5,
              3,  7,  2,
              3, 10,  7,
             10,  6,  7,
              6, 11,  7,
              6,  0, 11,
              6,  1,  0,
             10,  1,  6,
             11,  0,  9,
              2, 11,  9,
              5,  2,  9,
             11,  2,  7,
        },
        draw_mode::triangles_list
    };
}

//==============================================================================
//!\fn                    qx::create_icosahedron_lines
//
//!\brief  Create icosahedron geometry for lines drawing
//!\param  fRadius - icosahedron radius
//!\retval         - icosahedron geometry
//!\author Khrapov
//!\date   9.04.2021
//==============================================================================
inline geometry create_icosahedron_lines(float fRadius)
{
    auto geom = create_icosahedron(fRadius);
    geom.eDrawMode = draw_mode::lines_list;
    geom.geomIndices = detail::transform_triangle_indices_to_lines(geom.geomIndices);
    return geom;
}

//==============================================================================
//!\fn                        qx::create_icosphere
//
//!\brief  Create icosphere geometry
//!\param  fRadius  - icosphere radius
//!\param  nDivides - num of divides of icosahedron (bigger is higher precision)
//!\retval          - icosphere geometry
//!\author Khrapov
//!\date   9.04.2021
//==============================================================================
inline geometry create_icosphere(float fRadius, size_t nDivides)
{
    geometry ret = create_icosahedron(fRadius);

    indices thisLevelIndices;
    indices prevLevelIndices = ret.geomIndices;
    std::unordered_map<size_t, index_type> edgeMap;

    for (size_t i = 0; i < nDivides; ++i)
    {
        edgeMap.clear();
        const size_t end = prevLevelIndices.size();

        for (size_t j = 0; j < end; j += 3)
        {
            std::array<size_t, 3> indicesOuter;
            std::array<size_t, 3> indicesEdge;

            for (size_t k = 0; k < 3; ++k)
            {
                size_t k1 = (k + 1) % 3;
                size_t e0 = prevLevelIndices[j + k];
                size_t e1 = prevLevelIndices[j + k1];
                indicesOuter[k] = e0;

                if (e1 > e0)
                    std::swap(e0, e1);

                const size_t nEdgeKey = e0 | e1 << 32;

                if (auto it = edgeMap.find(nEdgeKey); it != edgeMap.end())
                {
                    indicesEdge[k] = it->second;
                }
                else
                {
                    indicesEdge[k] = ret.geomVertices.size();
                    edgeMap[nEdgeKey] = indicesEdge[k];

                    glm::vec3 newVertex
                    {
                        ret.geomVertices[e0].x + ret.geomVertices[e1].x,
                        ret.geomVertices[e0].y + ret.geomVertices[e1].y,
                        ret.geomVertices[e0].z + ret.geomVertices[e1].z
                    };

                    const float fScale = fRadius / glm::length(newVertex);
                    newVertex *= fScale;

                    ret.geomVertices.push_back(newVertex);
                }
            }

            thisLevelIndices.push_back(indicesOuter[0]);
            thisLevelIndices.push_back(indicesEdge[0]);
            thisLevelIndices.push_back(indicesEdge[2]);
            thisLevelIndices.push_back(indicesOuter[1]);
            thisLevelIndices.push_back(indicesEdge[1]);
            thisLevelIndices.push_back(indicesEdge[0]);
            thisLevelIndices.push_back(indicesOuter[2]);
            thisLevelIndices.push_back(indicesEdge[2]);
            thisLevelIndices.push_back(indicesEdge[1]);
            thisLevelIndices.push_back(indicesEdge[0]);
            thisLevelIndices.push_back(indicesEdge[1]);
            thisLevelIndices.push_back(indicesEdge[2]);
        }

        prevLevelIndices = std::move(thisLevelIndices);
    }

    ret.geomIndices = std::move(prevLevelIndices);

    return ret;
}

//==============================================================================
//!\fn                     qx::create_icosphere_lines
//
//!\brief  Create icosphere geometry for lines drawing
//!\param  fRadius  - icosphere radius
//!\param  nDivides - num of divides of icosahedron (bigger is higher precision)
//!\retval          - icosphere geometry
//!\author Khrapov
//!\date   9.04.2021
//==============================================================================
inline geometry create_icosphere_lines(float fRadius, size_t nDivides)
{
    auto geom = create_icosphere(fRadius, nDivides);
    geom.eDrawMode = draw_mode::lines_list;
    geom.geomIndices = detail::transform_triangle_indices_to_lines(geom.geomIndices);
    return geom;
}

}
