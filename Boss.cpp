#include "Boss.h"
#include "Character.h"
#include "Potion.h"

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <windows.h>
#include <conio.h>

bool Boss::isFirstPattern = true;

Boss::Boss(Character* player) : Monster("���� �����", player)
{
	Health += player->getLevel() * 1000; // ���� �߰� ü�� ���ʽ�
	Attack += player->getLevel() * 10;  // ���� �߰� ���ݷ� ���ʽ�

	MaxHealth = Health;

	char text1[] = "\033[1;35m �ߵ� ������� �Ա��� ��翩 \033[0m";
	char text2[] = "\033[1;35m ���ݱ��� ���� ���Ұ�����, ���ݺ��ʹ� �� ���� �����ϰ� �� ���̴�. \033[0m";
	char text3[] = "\033[1;35m ��, ��� �ѹ� ������ �߹��� �� ���ƶ�! \033[0m";

	string texts[] = { text1, text2, text3 };

	for (const string& s : texts) {
		for (char c : s) {
			cout << c << flush;
			this_thread::sleep_for(chrono::milliseconds(50));
		}
		this_thread::sleep_for(chrono::milliseconds(200));
		std::cout << std::endl;
	}
	string bossArt = R"(
######################~~..'|.##############.|`..~~#######################
##############~./`.~~./' ./ ################ \. `\. ~~.`\.~##############
############~.' `.`-'   /   ~#############~ .  \   `-'.'  `.~############
##########~.'    |     |  .'\ ~##########~ /`.  |     |     `.~##########
########~.'      |     |  |`.`._ ~####~ _.'.'|  |     |       `.~########
######~.'        `.    |  `..`._|\.--./|_.'..'  |    .'         `.~######
####~.'            \   | #.`.`._`.'--`.'_.'.'.# |   /             `.~####
##~.'       ......  \  | ###.`~'(o\||/o)`~'.### |  /  ......        `.~##
~.`.......'~      `. \  \~####  |\_  _/|  ####~/  / .'      ~`........'.~
;.'                 \ .----.__.'`(n||n)'`.__.----. /                  `;
`.                  .'    .'   `. \`'/ .'   `.    `.                  .'
#:               ..':      :    '. ~~ .`    :      :`..               :#
#:             .'   :     .'     .'  `.     `.     :   `.             :#
#:           .'    .`   .'       . || .       `.   '.    `.           :#
#:         .'    .' :       ....'      `....       : `.    `.         :#
#:       .'    .' ) )        (      )     (      (    )`.    `.       :#
#:     ..'    .  ( ((   )  ) )) (  ((  (  ))  )  ))  ((  `.   `..     :#
#:  ..'      .'# ) ) ) (( ( ( (  ) ) ) ))( ( (( ( (  ) ) #`.     `..  :#
#;.'        .'##|((  ( ) ) ) ) )( (  (( ( ) )) ) ) )( (||##`.       `.:#
#`.        .'###|\__  )( (( ( ( )  )  )) )  (  (( ( )_)/|###`.       .'#
##.`       '#####\__~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~__/#####`      '.##
###        #######  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~  #######       ###
)";
	size_t pos = 0;
	size_t next_pos;
	while ((next_pos = bossArt.find('\n', pos)) != string::npos) {
		string line = bossArt.substr(pos, next_pos - pos);
		cout << line << endl;
		this_thread::sleep_for(chrono::milliseconds(200));
		pos = next_pos + 1;
	}

}

void Boss::takeDamage(int damage) {
	if (isAlive == false) { return; } // �̹� ����� �������� Ȯ��
	Health -= damage;
	cout << "  " << "\033[1;32m" << Name << "���� " << damage << "�� �������� �־����ϴ�!" << "\033[0m" << std::endl;
	if (Health <= 0) {
		isAlive = false; // ����� isAlive ���¸� false�� ����
		onDeath();
	}
	else
	{
		cout << "  " << Name << "�� ���� ü�� : " << getHealth() << std::endl;
	}
}

int Boss::attackPlayer() {
	if (player == nullptr) return 2; // �÷��̾ null���� Ȯ��
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(1, 100);
	int UseBossSkill = dis(gen);

	if (UseBossSkill <= 55) // Ȯ�� �б�
	{
		cout << "\n  " << "\033[1;31m" << Name << "�� ����� �����մϴ�!" << "\033[0m" << std::endl; // 55% �Ϲ� ����
		player->takeDamage(getAttack());
	}
	else { // 45% Ȯ���� ���� �̺�Ʈ �߻�
		int currentPotions = Potion::countTotalPotions(player->getInventory());

		GuardSummary summary = BossAttackGuard(currentPotions);

		// ��� Ÿ���� ������ ���� �������� �ݰ�
		if (summary.allSuccess && player->getHealth() > 0) {
			int counterDamage = player->getAttack() * summary.successCount; // ���带 ������ Ƚ����ŭ �ݰ� ������ ���ϱ�
			cout << "\n  \033[1;36m[ī����] �Ϻ��� ����! �������� ������ �ݰ��� �����ϴ�!\033[0m" << endl;
			cout << "  �������� " << counterDamage << "�� ������!" << endl;
			this->takeDamage(counterDamage);
			player->setHealth(player->getHealth() + counterDamage); // �ݰ� ��������ŭ ü�� ȸ��
			cout << "\n  \033  ������ �Ծ�Ǿ� ü���� " << counterDamage << " ��ŭ ȸ���Ǿ����ϴ�!\033[0m" << endl;
			cout << "  ���� ���� ü��: " << player->getHealth() << endl;
			this_thread::sleep_for(chrono::seconds(1));
		}

		return (player->getHealth() <= 0) ? 0 : 1;
	}

	if (player->getHealth() <= 0)
	{
		return 0;
	}
	else {
		return 1;
	}

}

void Boss::onDeath() {

	std::cout << "\n\n\033[1;33m ����� " << Name << " �� �����ƴ�! \033[0m" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));

	std::cout << "\n  ����� ������ ��ȭ�� ��ã�Ҵ�..." << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(2));

	// ���� ũ���� ����
	std::string credits[] = {
		"  ",
		"  ",
		"  ",
		"  ",
		"  ",
		"          --- ENDING CREDITS ---",
		"          TextConsole RPG by 5��",
		"  ",
		"���� �� ���� ���� �� ���� ���� : �� ����  ",
		"ĳ���� �� ���� Ŭ��������      : �� ����  ",
		"���� �Ŵ��� Ŭ���� ����        : �� ����  ",
		"������ Ŭ���� ����             : �� �ν�  ",
		"���� Ŭ���� ����             : �� ����  ",
		"------------------------------------------",
		"           THANKS FOR PLAYING!  "
		"  ",
		"  ",
		"  ",
		"  ",
		"  ",
		"  ",
		"  ",
		"  ",
		"  ",
		"  ",
		"  ",
	};

	for (const std::string& line : credits) {
		std::cout << "      " << line << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(600)); // 0.6�� ���� ���
	}
}


GuardSummary Boss::BossAttackGuard(int& potionCount) {

	if (isFirstPattern) {
		showPatternGuide();
	}

	system("cls");
	system("color 07");

	random_device rd;
	mt19937 gen(rd());

	bool isEnraged = (getHealth() < (getMaxHealth() / 2)); // ü�� 50% �̸� �϶� ����ȭ

	// �Ϲ�: 1.0�� / ����ȭ: 0.4�� (���� �ð�)
	int judgeTime = isEnraged ? 400 : 1000;

	// �Ϲ�: 500~2500ms / ����ȭ: 300~1200ms (��� �ð�)
	int minWait = isEnraged ? 300 : 500;
	int maxWait = isEnraged ? 1200 : 2500;

	uniform_int_distribution<> disCount(2, 4); //�ּ�, �ִ� ���� ���� Ƚ��
	int totalPhase = disCount(gen);

	int successCount = 0;
	int failCount = 0;

	for (int phase = 1; phase <= totalPhase; ++phase) {
		system("cls");
		if (isEnraged) system("color 0C");
		else system("color 07");

		cout << "\n\n\n";
		if (isEnraged) cout << "  \033[1;31m[ !!!!! ENRAGED: ����۰� �����մϴ� !!!!! ]\033[0m" << endl;
		else cout << "  \033[1;33m[ !!!!!!!! WARNING !!!!!!!! ]\033[0m" << endl;

		cout << "  --------------------------------------------------" << endl;
		cout << "  ������ ���� ����: " << phase << " / " << totalPhase << endl;
		cout << "  ���� ���� ü��: " << player->getHealth() << endl;
		cout << "  ���� ���� ����: ";
		for (int i = 0; i < potionCount; ++i) cout << "\033[1;35m�� \033[0m";
		cout << "(" << potionCount << "��)" << endl;
		cout << "  --------------------------------------------------" << endl;
		cout << "\n  �����ϼ���... (��Ÿ ����!)" << endl;

		uniform_int_distribution<> disWait(minWait, maxWait);
		int waitTime = disWait(gen);

		auto waitStart = chrono::steady_clock::now();
		bool cheated = false; 

		while (chrono::steady_clock::now() - waitStart < chrono::milliseconds(waitTime)) {
			if (_kbhit()) {
				_getch();
				cheated = true;
				break;
			}
			this_thread::sleep_for(chrono::milliseconds(10));
		}

		bool pressed = false;

		// ���� ����
		if (!cheated) {
			system("color 47");
			cout << "\n  >> �����Դϴ�!!! <<" << endl;

			auto startTime = chrono::steady_clock::now();
			while (chrono::steady_clock::now() - startTime < chrono::milliseconds(judgeTime)) {
				if (_kbhit()) {
					if (_getch() == ' ') {
						pressed = true;
						break;
					}
				}
			}
		}

		// ����
		if (pressed) {
			successCount++;
			system("color 17");
			cout << "\n  [ ���� ] ������ ���Ƴ½��ϴ�!" << endl;
		}
		else {
			failCount++;
			system("color 40");

			if (cheated) {
				cout << "\n  [ ���� ] �ʹ� �����߽��ϴ�! (��Ÿ ����)" << endl;
			}
			else {
				cout << "\n  [ ���� ] ���� Ÿ�̹��� ���ƽ��ϴ�!" << endl;
			}

			// �÷��̾��� ���� ���� üũ
			vector<Item*> inv = player->getInventory();
			int potionIdx = -1;
			for (int j = 0; j < (int)inv.size(); ++j) {
				if (dynamic_cast<Potion*>(inv[j])) {
					potionIdx = j;
					break;
				}
			}

			// ���� ��� ������ �Ǵ� ���� �Ҹ�
			if (potionIdx != -1) {
				cout << "\n  [ ���� ] ���� ����! ������ ������ �������� ���ҽ��ϴ�." << endl;
				player->deleteItem(potionIdx);
				potionCount--; // ���� �Լ� ǥ�ÿ� ī��Ʈ ����
			}
			else {
				cout << "\n  [ ���� ] ���� ����! �������� �Խ��ϴ�!" << endl;
				player->takeDamage(getAttack() * 2);
			}

			// �÷��̾ �׾����� Ȯ��
			if (player->getHealth() <= 0) {
				cout << "\n  �÷��̾ ���������ϴ�..." << endl;
				this_thread::sleep_for(chrono::seconds(1));
				break; // ���� �ߴ�
			}
		}
		this_thread::sleep_for(chrono::milliseconds(800));
	}

	system("cls");
	system("color 07");

	return { (successCount == totalPhase), failCount, successCount };
}



void Boss::showPatternGuide() {
	system("cls");
	cout << "\n\n";
	cout << "                   ==================================================" << endl;
	cout << "                             [ ���� ��� �˸�: ���� ���� ]" << endl;
	cout << "                   ==================================================" << endl;
	cout << "              ������ �⸦ ���� �� ������ �ð� �� ȭ���� \033[1;31m������\033[0m���� ���մϴ�!" << endl;
	cout << "                    �� ���� ������ \033[1;36m[SPACE]\033[0m Ű�� ���� ����ϼ���." << endl;
	cout << "\n                            \033[1;32m - ����: ������ ��ȿȭ \033[0m" << endl;
	cout << "\n               \033[1;31m  - ����: ��� �ǰ� (������ �ִٸ� ������ ��� �ı���) \033[0m" << endl;
	cout << "\n            \033[1;34m   - �Ϻ� ����: ��� ��Ÿ�� ���Ƴ��� �÷��̾ �ݰݰ� ���ÿ� ü���� ȸ���մϴ�! \033[0m" << endl;
	cout << "                  ==================================================" << endl;
	cout << "\n                     �غ� �Ǿ��ٸ� [Enter] Ű�� ��������..." << endl;

	// Enter �Է� ���
	while (true) {
		if (_kbhit()) {
			if (_getch() == 13) break;
		}
	}
	system("color 07");
	isFirstPattern = false;
}