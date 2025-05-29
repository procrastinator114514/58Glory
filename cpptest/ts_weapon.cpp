#include<map>
#include<algorithm>
#include<cstdio>
#include"ts_weapon.h"
const std::map<int,W_Data> map_Weapon=
{
	{Weapontype::M202 , {{50,35,30,25,25,20,15},{10,7},2,2}},
	{Weapontype::RPG  , {{30,25,25,20,20,15,10},{5,5},1,1}},
	{Weapontype::Jtl  , {{40,35,20,20,15,10,10},{0,0},2,0}}
};
void W_Create(Hero* h,int W_type)
{
	TS_Weapon *nw=new TS_Weapon;
	nw->data=new W_Data;
	auto it= map_Weapon.find(W_type);
	if(it == map_Weapon.end())
	{
		delete nw->data;
		delete nw;
		printf("[Fail] 检测到非法数据!\n");
		return;
	}
	
	const auto& w_temp= it->second;
	for(int i=0;i<=6;i++)
	{
		nw->data->hurt[i]=w_temp.hurt[i];
	}
	nw->data->surhurt[0]=w_temp.surhurt[0];
	nw->data->surhurt[1]=w_temp.surhurt[1]; 
	nw->data->cost_M=w_temp.cost_M;
	nw->data->cost_F=w_temp.cost_F;
	nw->Flag_exist=true;
	nw->Flag_fire=true;
	h->H_weapon=nw;
	printf("[Pass] 成功赋予武器!\n");
}
void W_Demage(Hero *h)
{
	delete h->H_weapon->data;
	delete h->H_weapon;
	printf("[Pass] 成功销毁武器!\n");
}
