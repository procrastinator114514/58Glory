/**
 *@file test1.cpp
 *@author zju1229
 *@brief 以YR为例处理武将 
**/
#include<cstdio>
#include<cstdlib>
typedef struct Person{
	int c;		///<	所属班级 
	bool is_teacher;	///<	是否为老师 
};
typedef struct Position{
	int x,y;	///<	武将坐标 
};
typedef struct Hero{
	int hp,g,math;		///<	生命、极值、数学 
	bool sex;	///<	性别 
	Position* p;	///<	武将坐标 
	Person* a;		///<	武将身份 
};
/**
 *@name ray_f
 *@param[in] h1		一个武将指针
 *@brief 将h1武将指针赋予Ray信息 
**/ 
void ray_f(Hero *h1)
{
	h1->a=(Person *)malloc(sizeof(Person));
	h1->p=(Position *)malloc(sizeof(Position));
	h1->p->x=0;
	h1->p->y=0;
	h1->a->c=5;
	h1->a->is_teacher=true;
}
/**
 *@name move
 *@param[in] target		目标位置
 *@param[in] h1		操作武将
 *@brief 对武将进行操作 
**/ 
void move(Position *target,Hero* h1)
{
	free(h1->p);
	h1->p=target;
} 
/**
 *@name kill
 *@param[in] h1		一个武将指针
 *@brief 销毁该武将 
**/
void kill(Hero *h1)
{
	free(h1->p);
	free(h1->a);
	free(h1);
} 
//一个接口 
int main()
{
	Hero *ray=(Hero *)malloc(sizeof(Hero));
	ray_f(ray);
	kill(ray); 
	return 0;
} 
