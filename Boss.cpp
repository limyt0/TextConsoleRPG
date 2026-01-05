#include "Boss.h"
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include "Character.h"

Boss::Boss(Character* player) : Monster("마왕 루시퍼", player)
{
	Health += player->getLevel() * 100; // 보스 추가 체력 보너스
	Attack += player->getLevel() * 20;  // 보스 추가 공격력 보너스

	char text1[] = "\033[1;35m 잘도 여기까지 왔구나 용사여 \033[0m";
	char text2[] = "\033[1;35m 지금까진 운이 좋았겠지만, 지금부터는 그 운을 원망하게 될 것이느라. \033[0m";
	char text3[] = "\033[1;35m 자, 어디 한번 열심히 발버둥 쳐 보아라! 용사여!! \033[0m";

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
		this_thread::sleep_for(chrono::milliseconds(200)); // 줄 단위 대기
		pos = next_pos + 1;
	}

}

//int Boss::attackPlayer(class Character* player) {
//
//}

void Boss::onDeath() {

	std::cout << "\n\n\033[1;33m 당신은 " << Name << " 를 물리쳤다! \033[0m" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));

	std::cout << "\n  당신은 세상의 평화를 되찾았다..." << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(2));

	// 엔딩 크레딧 연출
	std::string credits[] = {
		"  ",
		"  ",
		"  ",
		"  ",
		"  ",
		"          --- ENDING CREDITS ---",
		"          TextConsole RPG by 5조",
		"  ",
		"조장 및 메인 구현 및 팀원 보조 : 임 영택  ",
		"캐릭터 및 상점 클래스구현      : 정 야후  ",
		"게임 매니저 클래스 구현        : 이 병헌  ",
		"아이템 클래스 구현             : 강 민승  ",
		"몬스터 클래스 구현             : 이 현진  ",
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
		std::this_thread::sleep_for(std::chrono::milliseconds(600)); // 0.6초 간격 출력
	}
}