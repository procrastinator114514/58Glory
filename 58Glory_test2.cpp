/**
 * @file 58Glory_test2.cpp
 * @author zju1229
 * @brief 游戏核心角色类定义（含YR武将实现）
 * @version 1.1
 * @date 2025-04-17
 * 
 * @copyright Copyright (c) 2025 58_Glory
 */

#pragma once
#include <memory>
#include <stdexcept>
#include <iostream>

/**
 * @class Position
 * @brief 表示武将在地图上的坐标位置
 * @note 坐标采用直角坐标系，原点(0,0)位于地图左下角
 */
class Position {
public:
    int x; ///< 横坐标，范围[0, 地图最大宽度)
    int y; ///< 纵坐标，范围[0, 地图最大高度)

    /**
     * @brief 构造函数
     * @param x_ 初始横坐标（默认0）
     * @param y_ 初始纵坐标（默认0）
     * @throw std::invalid_argument 坐标值为负数时抛出
     */
    Position(int x_ = 0, int y_ = 0) : x(x_), y(y_)
	{
        if(x < 0 || y < 0)    throw std::invalid_argument("Position coordinates cannot be negative");
    }
};

/**
 * @class Person
 * @brief 角色身份信息（班级和教师身份）
 * @note 班级编号规则：5=五班，6=六班，0=NPC
 */
class Person {
public:
    int class_id;     ///< 班级编号（参见注释规则）
    bool is_teacher;  ///< 是否为教师身份

    /**
     * @brief 构造函数
     * @param cls 班级编号
     * @param teacher 教师身份标识
     */
    Person(int cls, bool teacher) : class_id(cls), is_teacher(teacher) {}
};

/**
 * @class Hero
 * @brief 游戏核心角色类，封装武将属性和行为
 * 
 * @details 包含以下核心要素：
 * - 基础属性：生命值、极值、数学能力
 * - 空间属性：地图坐标位置
 * - 身份属性：班级归属和教师身份
 * 
 * @warning 非线程安全类，多线程操作需外部同步
 */
class Hero {
private:
    std::unique_ptr<Position> pos;       ///< 武将当前位置（智能指针管理）
    std::unique_ptr<Person> identity;    ///< 身份信息（智能指针管理）
    int health;                         ///< 生命值（HP），范围[0, 200]
    int extreme_value;                   ///< 极值，决定【偏移】技能伤害
    int math_ability;                    ///< 数学能力，分神/巨/强/中/弱五档
    bool sex;                           ///< 性别，true=男性，false=女性

public:
    /**
     * @brief 构造函数
     * @param hp 初始生命值（范围50-200）
     * @param g 初始极值（范围0-15）
     * @param math 数学能力（0=神，1=巨，2=强，3=中，4=弱）
     * @param sex 性别标识
     * @param cls 班级编号（参见Person类说明）
     * @param teacher 教师身份标识
     * @throw std::invalid_argument 输入参数超出有效范围时抛出
     */
    Hero(int hp, int g, int math, bool sex, int cls, bool teacher)
        : health(hp), extreme_value(g), math_ability(math), sex(sex),
          pos(std::make_unique<Position>(0, 0)),
          identity(std::make_unique<Person>(cls, teacher)) 
    {
        if(hp < 50 || hp > 200) {
            throw std::invalid_argument("Invalid health value");
        }
        if(g < 0 || g > 15) {
            throw std::invalid_argument("Extreme value out of range");
        }
    }

    /**
     * @brief 移动武将到指定位置
     * @param new_pos 目标位置（常量引用传递）
     * @throw std::invalid_argument 目标位置非法时抛出
     * 
     * @code
     * Hero yr(150, 0, 0, false, 5, true);
     * yr.moveTo(Position(3, 4)); // 移动到坐标(3,4)
     * @endcode
     */
    void moveTo(const Position& new_pos) {
        if (new_pos.x < 0 || new_pos.y < 0) {
            throw std::invalid_argument("Position coordinates cannot be negative");
        }
        pos = std::make_unique<Position>(new_pos);
    }

    /**
     * @brief 获取当前坐标（常引用访问）
     * @return 当前坐标的常量引用
     */
    const Position& getPosition() const { return *pos; }

    /**
     * @brief 获取班级信息
     * @return 班级编号（参见Person类说明）
     */
    int getClass() const { return identity->class_id; }

    /**
     * @brief 判断是否为教师身份
     * @return true表示教师，false表示学生
     */
    bool isTeacher() const { return identity->is_teacher; }

    /// @name 属性访问器
    /// @{
    int getHealth() const { return health; }          ///< 获取当前生命值
    int getExtremeValue() const { return extreme_value; } ///< 获取极值
    int getMathAbility() const { return math_ability; }   ///< 获取数学能力
    /// @}
};

/**
 * @brief 示例：YR角色初始化与移动
 * @return 程序退出码
 * 
 * @par 示例流程：
 * 1. 初始化YR角色（教师身份）
 * 2. 移动至坐标(1,1)
 * 3. 输出新坐标
 */
int main()
{
    try
	{
        // 初始化YR角色（HP=150，极值=0，数学=弱，女性，五班教师）
        Hero yr(150, 0, 0, false, 5, true); 
        yr.moveTo(Position(1, 1));
        std::cout << "New position: (" 
                  << yr.getPosition().x << ", " 
                  << yr.getPosition().y << ")\n";
    }
	catch (const std::exception& e)
	{
        std::cerr << "[ERROR] " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
