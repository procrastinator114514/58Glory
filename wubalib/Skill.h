#pragma once

#include <memory>
#include <vector>
#include <string>
#include <unordered_map>

#include "loginfo.h"
#include "wubaHero.h"

using namespace std;

class Skill{
// Skill基类，用于派生出不同的技能类
private:
	string name;
	int cd;
	int curr_cd;
	int lim; // 次数限制
	int curr_lim; // 当前次数限制
	bool available; // 基类默认为false，因为基类对象不会被实例化

public:
	// 构造函数，在class中，用于新建一个对象
	Skill(string n,int cooldown=0,int limit=114514,bool available=false)
		:name(n),cd(cooldown),curr_cd(0),lim(limit),curr_lim(limit),available(available){}
	// 析构函数，用于删除对象，一般使用默认
	virtual ~Skill() = default;
	// 更新cd
	void reset_cd(){
		if (curr_cd>0) --curr_cd;
	}
	// 更新使用次数限制
	void reset_lim(){
		--curr_lim;
	}
	// 更新发动条件（基类不提供逻辑）
	void set_ava(){
		available = true;
	}
	void ban_ava(){
		available = false;
	}
	// 检查技能发动条件
	bool check_ava(){
		if (curr_cd==0 && curr_lim>0 && available){
			return true;
		}
		return false;
	}
	// 技能效果（点对点）
	virtual void execute(Hero& caster, Hero& target) = 0;
	// 技能效果（点对面）
	virtual void execute(Hero& caster, vector<Hero>& target) = 0;
	virtual void execute(Hero& caster, coordinate &c) = 0; // 这里的coordinate需要在map.h中定义，甚至可能需要pybind
	// 技能效果（作用于自身或整个队伍）
	virtual void execute(Hero& caster, Team& team) =0;
};

class Healing:Skill{
// Healing 既是一个派生类也是一个基类，用于派生出581、Fakeflower等不同的医疗技能
private:
	vector<int> amount;// 一般医疗分为3档，则0、1、2可以作为索引
	Gender t_gender; // 用于郑阁
public:
	// 构造函数
	Healing(vector<int> amo,Gender g=Gender::any,int limit=3)
		:Skill(0,limit,false),
		amount(amo),t_gender(g) {}
	virtual void update_ava(Hero& target){
		if (target.getGender() != t_gender && t_gender!=Gender::any) ban_ava();
		set_ava();
	}
	// 返回0、1、2作为索引
	virtual int check_condition(Hero& target) = 0;// 特别地，返回-1作为错误值
	void execute(Hero& caster,Hero& target) override{
		int idx = check_condition(target);
		if (!check_ava() || idx==-1){
			cerr<<"Inavailable to use the skill!"<<endl; // 对接其他错误处理逻辑
			return;
		}
		target.curr_hp+=amount[idx];
		if (target.curr_hp > target.get_hp()) target.curr_hp = target.get_hp();
		reset_lim();
	}
};