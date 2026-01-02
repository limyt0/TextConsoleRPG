#pragma once
#include "Character.h"
#include <random>
using namespace std;


class Skill
{
private:
	int _Finisher; //1퍼확률로
	int _Strike; // 공격력의 1.1배에서 1.5배 사이만큼 데미지 20퍼
	int _Cleave; // 공격력의 1.3배정도? 20퍼
	//기본공격 99퍼

public:
	Skill();
	int	getFinisher()const;
	int getStrike()const;
	int getCleave()const;
	void setFinisher(int skilldemege);
	void setStrike(int skilldemege);
	void setCleave(int skilldemege);
};