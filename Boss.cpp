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

Boss::Boss(Character* player) : Monster("마왕 루시퍼", player)
{
    Health += player->getLevel() * 1000; // 보스 추가 체력 보너스
    Attack += player->getLevel() * 10;   // 보스 추가 공격력 보너스

    MaxHealth = Health;

    char text1[] = "\033[1;35m 잘도 여기까지 왔구나 용사여 \033[0m";
    char text2[] = "\033[1;35m 지금까진 운이 좋았겠지만, 지금부터는 그 운을 원망하게 될 것이다. \033[0m";
    char text3[] = "\033[1;35m 자, 어디 한번 열심히 발버둥 쳐 보아라! \033[0m";

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
    if (isAlive == false) { return; }
    Health -= damage;
    cout << "  " << "\033[1;32m" << Name << "에게 " << damage << "의 데미지를 주었습니다!" << "\033[0m" << std::endl;
    if (Health <= 0) {
        isAlive = false;
        onDeath();
    }
    else {
        cout << "  " << Name << "의 남은 체력 : " << getHealth() << std::endl;
    }
}

EntityState Boss::attackPlayer() {
    if (player == nullptr) return EntityState::NotFound;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 100);
    int UseBossSkill = dis(gen);

    if (UseBossSkill <= 55) {
        cout << "\n  " << "\033[1;31m" << Name << "이 당신을 공격합니다!" << "\033[0m" << std::endl;
        player->takeDamage(getAttack());
    }
    else {
        int currentPotions = Potion::countTotalPotions(player->getInventory());
        GuardSummary summary = BossAttackGuard(currentPotions);

        if (summary.allSuccess && player->getHealth() > 0) {
            int counterDamage = player->getAttack() * summary.successCount;
            cout << "\n  \033[1;36m[카운터] 완벽한 가드! 보스에게 강력한 반격을 날립니다!\033[0m" << endl;
            cout << "  보스에게 " << counterDamage << "의 데미지!" << endl;
            this->takeDamage(counterDamage);

            player->setHealth(player->getHealth() + counterDamage);
            cout << "\n  \033[1;32m의지가 함양되어 체력이 " << counterDamage << " 만큼 회복되었습니다!\033[0m" << endl;
            cout << "  현재 남은 체력: " << player->getHealth() << endl;
            this_thread::sleep_for(chrono::seconds(1));
        }
        return (player->getHealth() <= 0) ? EntityState::Dead : EntityState::ALIVE;
    }

    return (player->getHealth() <= 0) ? EntityState::Dead : EntityState::ALIVE;
}

void Boss::onDeath() {
    std::cout << "\n\n\033[1;33m 당신은 " << Name << " 를 물리쳤다! \033[0m" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "\n  당신은 세상의 평화를 되찾았다..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::string credits[] = {
        " ", " ", " ", " ", " ",
        "          --- ENDING CREDITS ---",
        "          TextConsole RPG by 5조",
        " ",
        "조장 및 메인 구현 및 팀원 보조 : 임영택  ",
        "캐릭터 및 상점 클래스 구현     : 정야후  ",
        "게임 매니저 클래스 구현        : 이병헌  ",
        "아이템 클래스 구현             : 강민승  ",
        "몬스터 클래스 구현             : 이현진  ",
        "------------------------------------------",
        "           THANKS FOR PLAYING!  "
    };

    for (const std::string& line : credits) {
        std::cout << "      " << line << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(600));
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

    bool isEnraged = (getHealth() < (getMaxHealth() / 2));
    int judgeTime = isEnraged ? 400 : 1000;
    int minWait = isEnraged ? 300 : 500;
    int maxWait = isEnraged ? 1200 : 2500;

    uniform_int_distribution<> disCount(2, 4);
    int totalPhase = disCount(gen);

    int successCount = 0;
    int failCount = 0;

    for (int phase = 1; phase <= totalPhase; ++phase) {
        system("cls");
        if (isEnraged) system("color 0C");
        else system("color 07");

        cout << "\n\n\n";
        if (isEnraged) cout << "  \033[1;31m[ !!!!! ENRAGED: 루시퍼가 폭주합니다 !!!!! ]\033[0m" << endl;
        else cout << "  \033[1;33m[ !!!!!!!! WARNING !!!!!!!! ]\033[0m" << endl;

        cout << "  --------------------------------------------------" << endl;
        cout << "  보스의 연속 공격: " << phase << " / " << totalPhase << endl;
        cout << "  현재 남은 체력: " << player->getHealth() << endl;
        cout << "  남은 포션 개수: ";
        for (int i = 0; i < potionCount; ++i) cout << "\033[1;35m■ \033[0m";
        cout << "(" << potionCount << "개)" << endl;
        cout << "  --------------------------------------------------" << endl;
        cout << "\n  집중하세요... (연타 금지!)" << endl;

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
        if (!cheated) {
            system("color 47");
            cout << "\n  >> 지금입니다!!! <<" << endl;

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

        if (pressed) {
            successCount++;
            system("color 17");
            cout << "\n  [ 성공 ] 공격을 막아냈습니다!" << endl;
        }
        else {
            failCount++;
            system("color 40");
            if (cheated) cout << "\n  [ 실패 ] 너무 성급했습니다! (연타 감지)" << endl;
            else cout << "\n  [ 실패 ] 가드 타이밍을 놓쳤습니다!" << endl;

            vector<Item*> inv = player->getInventory();
            int potionIdx = -1;
            for (int j = 0; j < (int)inv.size(); ++j) {
                if (dynamic_cast<Potion*>(inv[j])) {
                    potionIdx = j;
                    break;
                }
            }

            if (potionIdx != -1) {
                cout << "\n  [ 실패 ] 가드 실패! 포션이 깨지며 데미지를 막았습니다." << endl;
                player->deleteItem(potionIdx);
                potionCount--;
            }
            else {
                cout << "\n  [ 실패 ] 가드 실패! 데미지를 입습니다!" << endl;
                player->takeDamage(getAttack() * 2);
            }

            if (player->getHealth() <= 0) {
                cout << "\n  플레이어가 쓰러졌습니다..." << endl;
                this_thread::sleep_for(chrono::seconds(1));
                break;
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
    cout << "               ==================================================" << endl;
    cout << "                        [ 보스 기믹 알림: 연속 공격 ]" << endl;
    cout << "               ==================================================" << endl;
    cout << "            보스가 기를 모아 무작위로 화면이 \033[1;31m빨간색\033[0m으로 변합니다!" << endl;
    cout << "                그 순간 빠르게 \033[1;36m[SPACE]\033[0m 키를 눌러 방어하세요." << endl;
    cout << "\n                      \033[1;32m - 성공: 데미지 무효화 \033[0m" << endl;
    cout << "\n           \033[1;31m  - 실패: 즉시 피격 (포션이 있다면 포션이 대신 파괴됨) \033[0m" << endl;
    cout << "\n  \033[1;34m  - 완벽 성공: 모든 연타를 막아내면 플레이어가 반격과 동시에 체력을 회복합니다! \033[0m" << endl;
    cout << "               ==================================================" << endl;
    cout << "\n                 준비가 되었다면 [Enter] 키를 누르세요..." << endl;

    while (true) {
        if (_kbhit()) {
            if (_getch() == 13) break;
        }
    }
    system("color 07");
    isFirstPattern = false;
}