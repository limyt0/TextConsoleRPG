#include "Skill.h"

random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dis(11, 15);
Skill :: Skill()
	:_Finisher(0),_Strike(0),_Cleave(0)
{
}
int	Skill :: getFinisher()const
{
	return _Finisher;
}

void Skill :: setFinisher(int skilldemege)
{
	_Finisher = skilldemege * 3;
}

int Skill :: getStrike()const
{
	return _Strike;
}

void Skill :: setStrike(int skilldemege)
{
	_Strike =  skilldemege * (dis(gen)/10);
}

int Skill:: getCleave()const
{
	return _Cleave;
}

void Skill::setCleave(int skilldemege)
{
	_Cleave = skilldemege * 1.3f;
}