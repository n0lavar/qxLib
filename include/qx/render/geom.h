/**

    @file      geom.h
    @brief     Contains functions for creating primitives geometry
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
#include <unordered_map>
#include <vector>

namespace qx
{

using index_type = u32;
using vertices   = std::vector<glm::vec3>;
using indices    = std::vector<index_type>;

/**
    @struct geometry
    @date   4.04.2021
**/
struct geometry
{
    vertices  geomVertices; //!< vertices array
    indices   geomIndices;  //!< indices array
    glm::vec3 offset;       //!< offset of the center
    draw_mode eDrawMode;    //!< draw mode
};

/**
    @brief  Create parallelogram geometry
    @param  fSide1 - side 1 length
    @param  fSide2 - side 2 length
    @param  fSide3 - side 3 length
    @retval        - parallelogram geometry
**/
geometry create_parallelogram(float fSide1, float fSide2, float fSide3);

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
    @param  fSide - cube side length
    @retval       - cube geometry
**/
geometry create_cube(float fSide);

/**
    @brief  Create cube geometry for lines drawing
    @param  fSide - cube side length
    @retval       - cube geometry
**/
geometry create_cube_lines(float fSide);

/**
    @brief  Create icosahedron geometry
    @param  fRadius - icosahedron radius
    @retval         - icosahedron geometry
**/
geometry create_icosahedron(float fRadius);

/**
    @brief  Create icosahedron geometry for lines drawing
    @param  fRadius - icosahedron radius
    @retval         - icosahedron geometry
**/
geometry create_icosahedron_lines(float fRadius);

/**
    @brief  Create icosphere geometry
    @param  fRadius  - icosphere radius
    @param  nDivides - num of divides of icosahedron (bigger is higher precision)
    @retval          - icosphere geometry
**/
geometry create_icosphere(float fRadius, size_t nDivides);

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
geometry create_ellipse_lines(
    float  fHorRadius,
    float  fVertRadius,
    size_t nSides);

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
