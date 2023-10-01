/**

    @file      geom.inl
    @author    Khrapov
    @date      4.04.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/

namespace qx
{

namespace details
{

inline vertex create_vertex(const glm::vec3& pos, bool bUnitLengthPosNormal = false)
{
    vertex ret;
    ret.pos = pos;

    auto normalPos = pos;
    if (bUnitLengthPosNormal)
    {
        normalPos.x = normalPos.x > 0.f ? 1.f : -1.f;
        normalPos.y = normalPos.y > 0.f ? 1.f : -1.f;
        normalPos.z = normalPos.z > 0.f ? 1.f : -1.f;
    }
    ret.normal  = glm::normalize(normalPos);
    ret.tangent = create_tangent(ret.normal);
    return ret;
}

inline geometry create_figure(
    std::span<const glm::vec3>  positions,
    std::span<const index_type> _indices,
    const glm::vec3&            offset,
    bool                        bFlatNormals,
    bool                        bUnitLengthPosNormal = false)
{
    geometry ret;
    ret.offset = offset;

    if (bFlatNormals)
    {
        for (size_t i = 0; i < _indices.size(); i += 3)
        {
            const glm::vec3 pos0 = positions[_indices[i + 0]];
            const glm::vec3 pos1 = positions[_indices[i + 1]];
            const glm::vec3 pos2 = positions[_indices[i + 2]];

            const glm::vec3 normal  = glm::cross(pos2 - pos1, pos0 - pos1);
            const glm::vec3 tangent = create_tangent(normal);

            ret.geomVertices.emplace_back(pos0, normal, tangent);
            ret.geomVertices.emplace_back(pos1, normal, tangent);
            ret.geomVertices.emplace_back(pos2, normal, tangent);

            ret.geomIndices.push_back(static_cast<index_type>(i + 0));
            ret.geomIndices.push_back(static_cast<index_type>(i + 1));
            ret.geomIndices.push_back(static_cast<index_type>(i + 2));
        }
    }
    else
    {
        for (const glm::vec3& pos : positions)
            ret.geomVertices.emplace_back(create_vertex(pos, bUnitLengthPosNormal));

        ret.geomIndices = indices(_indices.begin(), _indices.end());
    }

    return ret;
}

inline std::array<glm::vec3, 12> create_icosahedron_positions(float fRadius)
{
    const float X = 0.525731112119133606f * fRadius;
    const float Z = 0.850650808352039932f * fRadius;

    return { {
        { -X, 0.f, Z },
        { X, 0.f, Z },
        { -X, 0.f, -Z },
        { X, 0.f, -Z },
        { 0.f, Z, X },
        { 0.f, Z, -X },
        { 0.f, -Z, X },
        { 0.f, -Z, -X },
        { Z, X, 0.f },
        { -Z, X, 0.f },
        { Z, -X, 0.f },
        { -Z, -X, 0.f },
    } };
}

inline geometry create_parallelogram(
    float fSide1,
    float fSide2,
    float fSide3,
    bool  bFlatNormals,
    bool  bUnitLengthPosNormal)
{
    const float fHalfSide1 = fSide1 / 2.f;
    const float fHalfSide2 = fSide2 / 2.f;
    const float fHalfSide3 = fSide3 / 2.f;

    const std::array<glm::vec3, 8> parallelogramPositions = { { { -fHalfSide1, -fHalfSide2, -fHalfSide3 },
                                                                { fHalfSide1, -fHalfSide2, -fHalfSide3 },
                                                                { fHalfSide1, fHalfSide2, -fHalfSide3 },
                                                                { -fHalfSide1, fHalfSide2, -fHalfSide3 },
                                                                { -fHalfSide1, -fHalfSide2, fHalfSide3 },
                                                                { fHalfSide1, -fHalfSide2, fHalfSide3 },
                                                                { fHalfSide1, fHalfSide2, fHalfSide3 },
                                                                { -fHalfSide1, fHalfSide2, fHalfSide3 } } };

    return details::create_figure(
        parallelogramPositions,
        shape_indices::parallelogram,
        { fHalfSide1, fHalfSide2, fHalfSide3 },
        bFlatNormals,
        bUnitLengthPosNormal);
}

} // namespace details

inline glm::vec3 create_tangent(const glm::vec3& normal)
{
    // tangent vector is pointing up (positive y)
    constexpr auto negativeZVector = glm::vec3(0.f, 0.f, -1.f);
    return glm::normalize(glm::cross(negativeZVector, normal));
}

inline indices transform_triangle_indices_to_lines(indices_view triangles)
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

inline geometry create_parallelogram(float fSide1, float fSide2, float fSide3, bool bFlatNormals)
{
    return details::create_parallelogram(fSide1, fSide2, fSide3, bFlatNormals, true);
}

inline geometry create_parallelogram_lines(float fSide1, float fSide2, float fSide3)
{
    auto geom        = create_parallelogram(fSide1, fSide2, fSide3, false);
    geom.eDrawMode   = draw_mode::lines_list;
    geom.geomIndices = transform_triangle_indices_to_lines(geom.geomIndices);

    return geom;
}

inline geometry create_cube(float fSide, bool bFlatNormals)
{
    return details::create_parallelogram(fSide, fSide, fSide, bFlatNormals, false);
}

inline geometry create_cube_lines(float fSide)
{
    auto geom        = create_cube(fSide, false);
    geom.eDrawMode   = draw_mode::lines_list;
    geom.geomIndices = transform_triangle_indices_to_lines(geom.geomIndices);

    return geom;
}

inline geometry create_icosahedron(float fRadius, bool bFlatNormals)
{
    return details::create_figure(
        details::create_icosahedron_positions(fRadius),
        shape_indices::icosahedron,
        { fRadius, fRadius, fRadius },
        bFlatNormals);
}

inline geometry create_icosahedron_lines(float fRadius)
{
    auto geom        = create_icosahedron(fRadius, false);
    geom.eDrawMode   = draw_mode::lines_list;
    geom.geomIndices = transform_triangle_indices_to_lines(geom.geomIndices);

    return geom;
}

inline geometry create_icosphere(float fRadius, size_t nDivides, bool bFlatNormals)
{
    const auto icosahedronPositions = details::create_icosahedron_positions(fRadius);

    std::vector<glm::vec3> icospherePositions = std::vector(icosahedronPositions.cbegin(), icosahedronPositions.cend());

    indices thisLevelIndices;
    indices prevLevelIndices = indices(shape_indices::icosahedron.cbegin(), shape_indices::icosahedron.cend());

    std::unordered_map<size_t, index_type> edgeMap;

    for (size_t i = 0; i < nDivides; ++i)
    {
        edgeMap.clear();
        const size_t end = prevLevelIndices.size();

        for (size_t j = 0; j < end; j += 3)
        {
            std::array<index_type, 3> indicesOuter;
            std::array<index_type, 3> indicesEdge;

            for (size_t k = 0; k < 3; ++k)
            {
                const index_type k1 = (k + 1) % 3;
                index_type       e0 = prevLevelIndices[j + k];
                index_type       e1 = prevLevelIndices[j + k1];
                indicesOuter[k]     = e0;

                if (e1 > e0)
                    std::swap(e0, e1);

                const size_t nEdgeKey = e0 | e1 << 16; //-V101

                if (auto it = edgeMap.find(nEdgeKey); it != edgeMap.end())
                {
                    indicesEdge[k] = it->second;
                }
                else
                {
                    indicesEdge[k]    = static_cast<index_type>(icospherePositions.size());
                    edgeMap[nEdgeKey] = indicesEdge[k];

                    const auto& e0pos = icospherePositions[e0]; //-V108
                    const auto& e1pos = icospherePositions[e1]; //-V108
                    glm::vec3   newVertex { e0pos.x + e1pos.x, e0pos.y + e1pos.y, e0pos.z + e1pos.z };

                    const float fScale = fRadius / glm::length(newVertex);
                    newVertex *= fScale;

                    icospherePositions.push_back(newVertex);
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

    return details::create_figure(icospherePositions, prevLevelIndices, { fRadius, fRadius, fRadius }, bFlatNormals);
}

inline geometry create_icosphere_lines(float fRadius, size_t nDivides)
{
    auto geom        = create_icosphere(fRadius, nDivides, false);
    geom.eDrawMode   = draw_mode::lines_list;
    geom.geomIndices = transform_triangle_indices_to_lines(geom.geomIndices);

    return geom;
}

inline geometry create_rect(float fWidth, float fHeight)
{
    const float fHalfWidth  = fWidth / 2.f;
    const float fHalfHeight = fHeight / 2.f;

    return { { { details::create_vertex({ fHalfWidth, fHalfHeight, 0.f }),
                 details::create_vertex({ fHalfWidth, -fHalfHeight, 0.f }),
                 details::create_vertex({ -fHalfWidth, -fHalfHeight, 0.f }),
                 details::create_vertex({ -fHalfWidth, fHalfHeight, 0.f }) } },
             std::vector(shape_indices::rect.cbegin(), shape_indices::rect.cend()),
             { fHalfWidth, fHalfHeight, 0.f },
             draw_mode::triangles_list };
}

inline geometry create_rect_lines(float fWidth, float fHeight)
{
    const float fLinesWidth  = fWidth - 1.f;
    const float fLinesHeight = fHeight - 1.f;

    const float fHalfWidth  = fLinesWidth / 2.f;
    const float fHalfHeight = fLinesHeight / 2.f;

    // one additional line for missing corner pixel fix
    return { { { details::create_vertex({ fHalfWidth, fHalfHeight, 0.f }),
                 details::create_vertex({ fHalfWidth, -fHalfHeight, 0.f }),
                 details::create_vertex({ -fHalfWidth, -fHalfHeight, 0.f }),
                 details::create_vertex({ -fHalfWidth, -fHalfHeight - 1.f, 0.f }),
                 details::create_vertex({ -fHalfWidth, fHalfHeight, 0.f }) } },
             { 0, 1, 2, 3, 4, 0 },
             { fHalfWidth + 1.f, fHalfHeight + 1.f, 0.f },
             draw_mode::lines_strip };
}

inline geometry create_square(float fSideLength)
{
    return create_rect(fSideLength, fSideLength);
}

inline geometry create_square_lines(float fSideLength)
{
    return create_rect_lines(fSideLength, fSideLength);
}

inline geometry create_ellipse(float fHorRadius, float fVertRadius, size_t nSides)
{
    const size_t    nVertices = nSides + 2;
    const float     fSides    = static_cast<float>(nSides);
    constexpr float f2Pi      = 2.0f * std::numbers::pi_v<float>;

    geometry ret;
    ret.geomIndices.reserve(nVertices);
    ret.geomVertices.reserve(nVertices);

    ret.geomIndices.push_back(0);
    ret.geomVertices.emplace_back(details::create_vertex({ 0.f, 0.f, 0.f }));

    for (size_t i = 1; i < nVertices; ++i)
    {
        ret.geomIndices.push_back(static_cast<index_type>(i));
        ret.geomVertices.emplace_back(
            details::create_vertex({ fHorRadius * std::cos(static_cast<float>(i) * f2Pi / fSides),
                                    fVertRadius * std::sin(static_cast<float>(i) * f2Pi / fSides),
                                    0.f }));
    }

    ret.eDrawMode = draw_mode::triangles_fan;
    ret.offset    = { fHorRadius, fVertRadius, 0.f };

    return ret;
}

inline geometry create_ellipse_lines(float fHorRadius, float fVertRadius, size_t nSides)
{
    geometry ret       = create_ellipse(fHorRadius, fVertRadius, nSides);
    ret.geomIndices[0] = ret.geomIndices[ret.geomIndices.size() - 1];
    ret.eDrawMode      = draw_mode::lines_strip;
    return ret;
}

inline geometry create_circle(float fRadius, size_t nSides)
{
    return create_ellipse(fRadius, fRadius, nSides);
}

inline geometry create_circle_lines(float fRadius, size_t nSides)
{
    return create_ellipse_lines(fRadius, fRadius, nSides);
}

} // namespace qx
