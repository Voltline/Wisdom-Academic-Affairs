#pragma once
#ifndef COURSESYSTEM_H
#define COURSESYSTEM_H
#include "multicoursetime.h"
#include "coursetime.h"
#include "course.h"
#include "teachercourse.h"
#include "stdAddition.h"
#include "unordered_map"
#include <QString>
namespace CourseSystem
{
    // 一周最大天数
    const int MAX_DAY_IN_WEEK = 7;
    // 一周最大课程数
    const int MAX_CLASS_IN_DAY = 14;
    // 一周最大课程数
    const int MAX_CLASS_ID = 98;
}
#endif // COURSESYSTEM_H
