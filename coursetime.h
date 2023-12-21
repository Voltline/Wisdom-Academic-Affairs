#pragma once
#ifndef COURSESYSTEM_COURSETIME_H
#define COURSESYSTEM_COURSETIME_H
#include "CourseSystem.h"
#include "classinfo.h"
#include <QDebug>
namespace CourseSystem
{
    // 课程时间类 仅处理某一个上课时间 提供人id/课时的转换
    class CourseTime
    {
    public:
        CourseTime() = default;
        CourseTime(ClassPeriod);
        CourseTime(int day, int start_class, int end_class);
        CourseTime(int time_id_1, int time_id_2);
        CourseTime(const CourseTime &time);
        CourseTime &operator=(const CourseTime &time);
        /// @brief 获取星期几
        /// @return 星期几
        const int &get_day() const;
        /// @brief 获取开始课时
        /// @return 开始课时
        const int &get_start_class() const;
        /// @brief 获取结束课时
        /// @return 结束课时
        const int &get_end_class() const;
        /// @brief 获取开始课时ID
        /// @return 开始课时ID
        const int &get_start_class_id() const;
        /// @brief 获取结束课时ID
        /// @return 结束课时ID
        const int &get_end_class_id() const;
        friend bool judge_conflict(CourseTime &c1, CourseTime &c2);
        void debug()
        {
            qDebug() << "day:" << day << "start_class:" << start_class << "end_class:" << end_class << "start_class_id:" << start_class_id << "end_class_id:" << end_class_id << "re" << reverse;
        }

        int reverse; //用于网络流流量计算
    private:
        int day;                          // 星期几
        int start_class, end_class;       // 开始和结束课时
        int start_class_id, end_class_id; // 开始和结束课时id
    };
    // 判断两个课时是否冲突
    bool judge_conflict(CourseTime &c1, CourseTime &c2);
    bool operator==(const CourseTime &c1,const CourseTime &c2);

} // namespace CourseSystem

#endif // COURSESYSTEM_COURSETIME_H
