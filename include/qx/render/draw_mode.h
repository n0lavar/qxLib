/**

    @file      draw_mode.h
    @brief     Contains qx::draw_mode enum
    @author    Khrapov
    @date      9.04.2021
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

namespace qx
{

enum class draw_mode
{
    /*
        Separate points.

        { 0 }, { 1 }, { 2 }, { 3 }
    */
    points,

    /*
        Vertices 0 and 1 are considered a line.
        Vertices 2 and 3 are considered a line.
        And so on.

        { 0, 1 },
                  { 2, 3 },
    */
    lines_list,

    /*
        The adjacent vertices are considered lines.

        { 0, 1 },
           { 1, 2 },
              { 2, 3 }
    */
    lines_strip,

    /*
        Vertices 0, 1, and 2 form a triangle.
        Vertices 3, 4, and 5 form a triangle.
        And so on.

        { 0, 1, 3 },
                     { 4, 5, 6 },
                                  { 7, 8, 9 }
    */
    triangles_list,

    /*
        Every group of 3 adjacent vertices forms a triangle.

        { 0, 1, 3 },
           { 1, 2, 4 },
              { 2, 3, 5 }
    */
    triangles_strip,

    /*
        The first vertex is always held fixed.
        From there on, every group of 2 adjacent vertices
        form a triangle with the first.

        { 0, 1, 2 }
        { 0,    2, 3 }
        { 0,       3, 4 }
        { 0,           4, 5}
    */
    triangles_fan,
};

}
