/**

    @file      copyable_movable.h
    @brief     Contains macros to set class as copyable/movable
    @details   ~
    @author    Khrapov
    @date      7.08.2022
    @copyright © Nick Khrapov, 2022. All right reserved.

**/
#pragma once

/**
    @def   QX_COPYABLE
    @brief Define class as default copyable
    @param className - class name
**/
#define QX_COPYABLE(className)             \
    className(const className&) = default; \
    className& operator=(const className&) = default

/**
    @def   QX_MOVABLE
    @brief Define class as default movable
    @param className - class name
**/
#define QX_MOVABLE(className)                  \
    className(className&&) noexcept = default; \
    className& operator=(className&&) noexcept = default

/**
    @def   QX_COPYMOVABLE
    @brief Define class as default copyable and movable
    @param className - class name
**/
#define QX_COPYMOVABLE(className) \
    QX_COPYABLE(className);       \
    QX_MOVABLE(className)

/**
    @def   QX_NONCOPYABLE
    @brief Define class as non copyable
    @param className - class name
**/
#define QX_NONCOPYABLE(className)         \
    className(const className&) = delete; \
    className& operator=(const className&) = delete

/**
    @def   QX_NONMOVABLE
    @brief Define class as non movable
    @param className - class name
**/
#define QX_NONMOVABLE(className)              \
    className(className&&) noexcept = delete; \
    className& operator=(className&&) noexcept = delete

/**
    @def   QX_NONCOPYMOVABLE
    @brief Define class as non copyable and non movable
    @param className - class name
**/
#define QX_NONCOPYMOVABLE(className) \
    QX_NONCOPYABLE(className);       \
    QX_NONMOVABLE(className)
