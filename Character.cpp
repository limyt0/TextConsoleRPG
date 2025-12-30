#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Character
{
private:
	string _Name;
	int _Level;
	/*int _MaxLevel;*/
	int _Health;
	int _MaxHealth;
	int _Attack;
	int _Experence;
	int _Gold;

public:
	Character(string name) :
		_Name(name), _Level(1), _Health(200), _MaxHealth(200), _Attack(30), _Experence(0), _Gold(0)
	{
	}
	int GetLevel()const
	{
		return _Level;
	}
	/*int GetMaxLevel()const
	{
		return _MaxLevel;
	}*/
	int GetHealth()const
	{
		return _Health;
	}
	int GetMaxHealth()const
	{
		return _MaxHealth;
	}
	int GetAttack()const
	{
		return _Attack;
	}

	int GetExperence()const
	{
		return _Experence;
	}

	int GetGold()const
	{
		return _Gold;
	}
	int SetLevel()
	{	//시작시 레벨 1로 초기
		// 경험치가 100이되면 레벨이 증가하고 
		//최대체력이 현재체력 + (레벨 * 20)만큼 증가
		//공력력이증가함 현재공격력 +(레벨 *5)만큼 증가
		return _Level;
	}
	//int SetMaxLevel()
	///*{
	//	_MaxLevel = 10;
	//}*/
	int SetHealth()
	{
		return _Health;
		// 포션사용시 50 회복
		// 레벨업시 maxhealth만큼 회복
	}
	int SetMaxHealth()
	{
		return _MaxHealth;
		//최대체력이 현재체력 + (레벨 * 20)만큼 증가
	}
	int SetAttack()
	{
		return _Attack;
		//최대체력이 현재체력 + (레벨 * 20)만큼 증가
	}
	int SetExperence()
	{
		return _Experence;
		//몬스터 처치시 50증가
		// 경험치가 100이되면 레벨이 증가하고 
	}
	int SetGold()
	{
		return _Gold;
		//몬스터 처치시 10~20골드 랜덤획득
	}

	void ShowStatus()const
	{
		cout << "현재 스테이터스창" << endl;
		cout << "이       름:" << _Name << endl;
		cout << "현재   레벨:" << _Level << endl;
		cout << "현재 공격력:" << _Attack << endl;
		cout << "현재   체력:" << _Health << endl;
		cout << "현재   골드:" << _Gold << endl;
		cout << "현재 경험치:" << _Experence << endl;

	}
};



int main()
{
	Character a("Yahoo");
	a.ShowStatus();
}