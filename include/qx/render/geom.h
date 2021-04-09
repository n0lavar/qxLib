//==============================================================================
//
//!\file                             geom.h
//
//!\brief       Contains functions for creating primitives geometry
//!\details     ~
//
//!\author      Khrapov
//!\date        4.04.2021
//!\copyright   (c) Nick Khrapov, 2021. All right reserved.
//
//==============================================================================
#pragma once

#include <qx/typedefs.h>
#include <qx/render/draw_mode.h>

#include <array>
#include <unordered_map>
#include <vector>
#include <glm/geometric.hpp>
#include <glm/vec3.hpp>

namespace qx
{

using index_type    = u32;
using vertices      = std::vector<glm::vec3>;
using indices       = std::vector<index_type>;

//==============================================================================
//
//!\struct                        qx::geometry
//!\author  Khrapov
//!\date    4.04.2021
//==============================================================================
struct geometry
{
    vertices    geomVertices;
    indices     geomIndices;
    draw_mode   eDrawMode;
};

geometry create_parallelogram       (float fSide1, float fSide2, float fSide3);
geometry create_parallelogram_lines (float fSide1, float fSide2, float fSide3);
geometry create_cube                (float fSide);
geometry create_cube_lines          (float fSide);
geometry create_icosahedron         (float fRadius);
geometry create_icosahedron_lines   (float fRadius);
geometry create_icosphere           (float fRadius, size_t nDivides);
geometry create_icosphere_lines     (float fRadius, size_t nDivides);

}

#include <qx/render/geom.inl>
