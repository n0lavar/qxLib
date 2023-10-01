/**

    @file      geom.h
    @author    Khrapov
    @date      4.04.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/render/draw_mode.h>
#include <qx/typedefs.h>

#include <glm/geometric.hpp>
#include <glm/vec3.hpp>

#include <array>
#include <cmath>
#include <numbers>
#include <span>
#include <unordered_map>
#include <vector>

namespace qx
{

struct vertex
{
    glm::vec3 pos     = glm::vec3(0.f);
    glm::vec3 normal  = glm::vec3(0.f);
    glm::vec3 tangent = glm::vec3(0.f);
};

using index_type   = u32;
using vertices     = std::vector<vertex>;
using indices      = std::vector<index_type>;
using indices_view = std::span<const index_type>;

struct geometry
{
    vertices  geomVertices;                          //!< vertices array
    indices   geomIndices;                           //!< indices array
    glm::vec3 offset    = glm::vec3(0.f);            //!< offset of the center
    draw_mode eDrawMode = draw_mode::triangles_list; //!< draw mode
};

namespace shape_indices
{

constexpr std::array<index_type, 60> icosahedron { {
    1, 4,  0, 4,  9, 0, 4, 5,  9, 8, 5, 4,  1, 8, 4, 1,  10, 8, 10, 3, 8, 8, 3,  5, 3, 2, 5, 3,  7, 2,
    3, 10, 7, 10, 6, 7, 6, 11, 7, 6, 0, 11, 6, 1, 0, 10, 1,  6, 11, 0, 9, 2, 11, 9, 5, 2, 9, 11, 2, 7,
} };

constexpr std::array<index_type, 36> parallelogram = {
    3, 1, 0, 2, 1, 3, 2, 5, 1, 6, 5, 2, 6, 4, 5, 7, 4, 6, 7, 0, 4, 3, 0, 7, 7, 2, 3, 6, 2, 7, 0, 5, 4, 1, 5, 0,
};

constexpr std::array<index_type, 6> rect = { 0, 1, 3, 1, 2, 3 };

} // namespace shape_indices

/**
    @brief  Create tangent vector for a given normal
    @param  normal - normal vector
    @retval        - tangent vector
**/
glm::vec3 create_tangent(const glm::vec3& normal);

/**
    @brief  Transform triangle indices to line indices
    @param  triangles - triangle indices
    @retval           - line indices
**/
indices transform_triangle_indices_to_lines(indices_view triangles);

/**
    @brief  Create parallelogram geometry
    @param  fSide1       - side 1 length
    @param  fSide2       - side 2 length
    @param  fSide3       - side 3 length
    @param  bFlatNormals - if true, each vertex will have independent normal
    @retval              - parallelogram geometry
**/
geometry create_parallelogram(float fSide1, float fSide2, float fSide3, bool bFlatNormals = true);

/**
    @brief  Create parallelogram geometry for lines drawing
    @param  fSide1 - side 1 length
    @param  fSide2 - side 2 length
    @param  fSide3 - side 3 length
    @retval        - parallelogram geometry
**/
geometry create_parallelogram_lines(float fSide1, float fSide2, float fSide3);

/**
    @brief  Create cube geometry
    @param  fSide        - cube side length
    @param  bFlatNormals - if true, each vertex will have independent normal
    @retval              - cube geometry
**/
geometry create_cube(float fSide, bool bFlatNormals = true);

/**
    @brief  Create cube geometry for lines drawing
    @param  fSide - cube side length
    @retval       - cube geometry
**/
geometry create_cube_lines(float fSide);

/**
    @brief  Create icosahedron geometry
    @param  fRadius      - icosahedron radius
    @param  bFlatNormals - if true, each vertex will have independent normal
    @retval              - icosahedron geometry
**/
geometry create_icosahedron(float fRadius, bool bFlatNormals = true);

/**
    @brief  Create icosahedron geometry for lines drawing
    @param  fRadius - icosahedron radius
    @retval         - icosahedron geometry
**/
geometry create_icosahedron_lines(float fRadius);

/**
    @brief  Create icosphere geometry
    @param  fRadius      - icosphere radius
    @param  nDivides     - num of divides of icosahedron (bigger is higher precision)
    @param  bFlatNormals - if true, each vertex will have independent normal
    @retval              - icosphere geometry
**/
geometry create_icosphere(float fRadius, size_t nDivides, bool bFlatNormals = false);

/**
    @brief  Create icosphere geometry for lines drawing
    @param  fRadius  - icosphere radius 
    @param  nDivides - num of divides of icosahedron (bigger is higher precision) 
    @retval          - icosphere geometry 
**/
geometry create_icosphere_lines(float fRadius, size_t nDivides);

/**
    @brief  Create rectangle geometry
    @param  fWidth  - rectangle width
    @param  fHeight - rectangle height
    @retval         - rectangle geometry
**/
geometry create_rect(float fWidth, float fHeight);

/**
    @brief  Create rectangle geometry for lines drawing
    @param  fWidth  - rectangle width
    @param  fHeight - rectangle height
    @retval         - rectangle geometry
**/
geometry create_rect_lines(float fWidth, float fHeight);

/**
    @brief  Create square geometry
    @param  fSideLength - square side length
    @retval             - square geometry
**/
geometry create_square(float fSideLength);

/**
    @brief  Create square geometry for lines drawing
    @param  fSideLength - square side length
    @retval             - square geometry
**/
geometry create_square_lines(float fSideLength);

/**
    @brief  Create ellipse geometry
    @param  fHorRadius  - ellipse horizontal radius
    @param  fVertRadius - ellipse vertical radius
    @param  nSides      - number of lines in ellipse edge, must be > 3
                          the greater value, the smoother еру edge
    @retval             - ellipse geometry
**/
geometry create_ellipse(float fHorRadius, float fVertRadius, size_t nSides);

/**
    @brief  Create ellipse geometry for lines drawing
    @param  fHorRadius  - ellipse horizontal radius
    @param  fVertRadius - ellipse vertical radius
    @param  nSides      - number of lines in ellipse edge, must be > 3
                          the greater value, the smoother еру edge
    @retval             - ellipse geometry
**/
geometry create_ellipse_lines(float fHorRadius, float fVertRadius, size_t nSides);

/**
    @brief  Create circle geometry for lines drawing
    @param  fRadius - circle radius
    @param  nSides  - number of lines in ellipse edge, must be > 3
                      the greater value, the smoother еру edge
    @retval         - circle geometry
**/
geometry create_circle(float fRadius, size_t nSides);

/**
    @brief  Create circle geometry for lines drawing
    @param  fRadius - circle radius
    @param  nSides  - number of lines in ellipse edge, must be > 3
                      the greater value, the smoother еру edge
    @retval         - circle geometry
**/
geometry create_circle_lines(float fRadius, size_t nSides);

} // namespace qx

#include <qx/render/geom.inl>
