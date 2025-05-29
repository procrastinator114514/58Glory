#pragma once

#include "Skill.h"
#include "weapon.h"

using namespace std;

enum class Gender{
	male,
	female,
	any
};

enum class Job{
	student,
	teacher
};

struct status{
	int Class; // 5、6、0，其中0代表非5且非6；
	//对于5、6班共有的武将，应当按照身份认同等方式划归5或6
	Job Standing; // 是否为学生角色
};

// 数学的五个分级
enum class Math{
	Godlike,
	Elite,
	Strong,
	Moderate,
	Weak
};

class base_Hero{
private:
	string name;
	int hp;
	Gender gender;
	int e_value;
	status identity;
	Math math;
	vector<unique_ptr<Skill>> skills; // 技能容器
	
public:
	base_Hero(const string& n,int hp, Gender g, int ev, const status& idt,Math m)
		:name(n),hp(hp),gender(g),e_value(ev),identity(idt),math(m){}
	virtual ~base_Hero() = default;
	int get_hp(){
		return hp;
	}
	Gender getGender(){
		return gender;
	}
	int get_eval(){
		return e_value;
	}
	status get_idt(){
		return identity;
	}
	Math get_math(){
		return math;
	}
	void add_skill();// 还没有实现，待会再说
};

// 当武将被选择上场时，创建10个派生类对象
class Hero:base_Hero{
private:
	Weapon weapon;
public:
	// curr字段的意思是当前的值
	int curr_hp;
	int curr_ev;
	Math curr_math;
	explicit Hero(const base_Hero& base)
		:base_Hero(base),
		curr_hp=base.get_hp(),
		curr_ev=base.get_eval(),
		curr_math=base.get_math() {}
	// 还有一些逻辑先不实现了
};