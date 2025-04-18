#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cstring>
enum class mathtype :int{
	weak=0,
	low=1,
	mid=2,
	strong=3,
	god=4
};
enum class weapontype :int{
	M202=1,
	RPG=2,
	Jtl=3
};
typedef struct H_Data{
	int num;
	std::string name;
	int hp,g,math;
	bool sex;
};
typedef struct H_Identity{
	int c;
	bool is_teacher;
};
typedef struct H_Positon{
	int x,y;
};
typedef struct H_Condition{
	int hp,g,math;
};
typedef struct H_Weapon{
	int type;
	int cd;
};
typedef struct H_Skill{
	std::string name;
	bool state;
	int num;
	int cd;
};
typedef struct TS_Hero{
	H_Data *data;
	H_Identity *person;
	H_Positon *where;
	H_Condition *now;
	H_Weapon *weapon;
	//H_Skill *skill;
};
TS_Hero* TS_Create_emptyHero()
{
	TS_Hero *h=new TS_Hero;
	h->data=new H_Data;
	h->person=new H_Identity;
	h->where=NULL;
	h->now=NULL;
	h->weapon=NULL; 
	return h;
}
void TS_Distroy_emptyHero(TS_Hero *h)
{
	if(h->data) 	delete h->data;
	if(h->person) 	delete h->person;
	if(h->where)	delete h->where;
	if(h->now)		delete h->now;
	if(h->weapon)	delete h->weapon;
	delete h;
}
TS_Hero* search_Hero(int num)
{
	TS_Hero *h=TS_Create_emptyHero();
	switch(num)
	{
		case 1:
			h->data->name="Birdman";
			h->data->hp=110;
			h->data->g=5;
			h->data->math=2;
			h->data->sex=true;
			h->person->c=5;
			h->person->is_teacher=false;
			break;
		case 2:
			h->data->name="Lyj";
			h->data->hp=125;
			h->data->g=2;
			h->data->math=4;
			h->data->sex=true;
			h->person->c=5;
			h->person->is_teacher=false;
			break;
		case 3:
			h->data->name="581";
			h->data->hp=100;
			h->data->g=11;
			h->data->math=0;
			h->data->sex=false;
			h->person->c=6;
			h->person->is_teacher=false;
			break;
		case 4:
			h->data->name="582";
			h->data->hp=100;
			h->data->g=11;
			h->data->math=1;
			h->data->sex=false;
			h->person->c=1;
			h->person->is_teacher=false;
			break;
		case 5:
			h->data->name="583";
			h->data->hp=100;
			h->data->g=10;
			h->data->math=2;
			h->data->sex=false;
			h->person->c=6;
			h->person->is_teacher=false;
			break;
		case 6:
			h->data->name="YR";
			h->data->hp=150;
			h->data->g=0;
			h->data->math=0;
			h->data->sex=true;
			h->person->c=5;
			h->person->is_teacher=true;
			break;
		case 7:
			h->data->name="DXD";
			h->data->hp=135;
			h->data->g=2;
			h->data->math=0;
			h->data->sex=true;
			h->person->c=6;
			h->person->is_teacher=true;
			break;
		case 8:
			h->data->name="Fakeflower";
			h->data->hp=100;
			h->data->g=6;
			h->data->math=3;
			h->data->sex=false;
			h->person->c=5;
			h->person->is_teacher=true;
			break;
		case 9:
			h->data->name="SJK";
			h->data->hp=130;
			h->data->g=100;
			h->data->math=4;
			h->data->sex=true;
			h->person->c=4;
			h->person->is_teacher=true;
			break;
		case 10:
			h->data->name="An";
			h->data->hp=125;
			h->data->g=5;
			h->data->math=3;
			h->data->sex=false;
			h->person->c=5;
			h->person->is_teacher=true;
			break;
		case 11:
			h->data->name="Office";
			h->data->hp=100;
			h->data->g=6;
			h->data->math=0;
			h->data->sex=false;
			h->person->c=5;
			h->person->is_teacher=true;
			break;
		case 12:
			h->data->name="Drrra";
			h->data->hp=130;
			h->data->g=3;
			h->data->math=3;
			h->data->sex=true;
			h->person->c=5;
			h->person->is_teacher=false;
			break;
		case 13:
			h->data->name="zhengge";
			h->data->hp=100;
			h->data->g=0;
			h->data->math=3;
			h->data->sex=true;
			h->person->c=4;
			h->person->is_teacher=false;
			break;
		case 14:
			h->data->name="Yangtze";
			h->data->hp=115;
			h->data->g=8;
			h->data->math=3;
			h->data->sex=false;
			h->person->c=6;
			h->person->is_teacher=false;
			break;
		case 15:
			h->data->name="142";
			h->data->hp=110;
			h->data->g=6;
			h->data->math=2;
			h->data->sex=false;
			h->person->c=6;
			h->person->is_teacher=false;
			break;
		default:
			return NULL; 
	}
	return h;
}
void H_show(int num)
{
	TS_Hero *h=search_Hero(num);
	if(h==NULL)		printf(" Error!\n The Hero DONOT exist!\n");
	printf("+----------------------+´\n");
	printf("| Name  | %-12s |\n",h->data->name.c_str());
	printf("| Hp    | %-12d |\n",h->data->hp);
	printf("| G     | %-12d |\n",h->data->g);
	printf("| Math  | %-12d |\n",h->data->math);
	printf("| Sex   | %-12s |\n",h->data->sex ?"Male":"Female");
	printf("| Class | %-12d |\n",h->person->c);
	printf("| Person| %-12s |\n",h->person->is_teacher?"Teacher":"Student");
	printf("+----------------------+¼\n");
	TS_Distroy_emptyHero(h);
}
int main()
{
	int order;
	scanf("%d",&order);
	H_show(order); 
	return 0;
} 
