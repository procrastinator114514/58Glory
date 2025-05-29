/**
 * @file ts_weapon.h
 * @author zju1229
 * @brief Weapon相关内容实现,接口为Hero的Weapon指针
**/
#ifndef TS_WEAPON_H
#define TS_WEAPON_H
enum class Weapontype : int {
	M202=0,		/**< @var 武器M202*/
	RPG=1,		/**< @var 武器RPG*/
	Jtl=2		/**< @var 武器加特林*/
};
struct W_Data{
	int hurt[7];	/**< 基础伤害数据,数组下标表示距离*/
	int surhurt[2];	/**< 溅射伤害数据*/
	int cost_M;		/**< 制作所耗经济*/
	int cost_F;		/**< 开火所耗经济*/
};
struct TS_Weapon
{
	bool Flag_exist;	/**< 检验武器是否存在*/
	bool Flag_fire;		/**< 检验武器是否能开火*/
	int W_type;			/**< 武器的类型*/
	W_Data *data;		/**< 武器数据指针,用于存储武器的相关数据*/
};
/**
 * @name W_Create
 * @param[in] h 获得武器的武将指针
 * @param[in] W_type 获得的武器类型
 * @brief 给应当获得的武将创造武器
**/
void W_Create(Hero* h,int W_type);
void W_Hurt(int distance,int W_type);
void W_Extrahurt(Hero* h1,Hero* h2);
/**
 * @name W_Create
 * @param[in] h 失去武器的武将指针
 * @brief 销毁该武将手中的武器
**/
void W_Demage(Hero* h);
#endif
