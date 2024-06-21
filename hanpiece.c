/*
2) 항해 (O)
3) 스텟 추가 (O)
4) 보물상자 발견 이벤트 (O)
5) 아이템 발견 이벤트 (O)
6) 전투 이벤트 (O)
7) 전투 결과 정산 (O)
8) 게임 종료 (O)
9) 기타 (O) :
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define LUF_ATTACK 1
#define LUF_HOLD 2

#define CRC_ATTACK 0
#define CRC_TRANS 1
#define CRC_HOLD 2

int LHP, LAT, KI, ATK;
int CHP, CAT, CATK, CHANGE;
int BREAK_NO;
int MEET = 20;
int MONEY = 1000;
int PLUS_ATK;
int EVENT_NO;
int PLUS_MONEY;
int EVENT_SWITCH;
int LV = 1;
int PLUS_HP;

enum Color { BLACK, DARK_BLUE, DARK_GREEN, DARK_SKYBLUE, DARK_RED, DARK_VOILET, DAKR_YELLOW, GRAY, DARK_GRAY, BLUE, GREEN, SKYBLUE, RED, VIOLET, YELLOW, WHITE };

void setColor(unsigned short clr);
void intro(void);
void print_set(void);
void print_info(void);
void print_condition(void);
void luffy_turn(void);
void crocodile_turn(void);
void fight(void);
void voya(void);
void event(void);
void end(void);

void setColor(unsigned short clr) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}

void intro(void) {
	printf("===한피스 시작===\n");
	printf("\n해적왕이 될 사나이 루피는\n고잉 메리호를 타고 길을 떠난다.\n");
	printf("\n바다를 떠돌던 중\n칠무해 크로커다일을 만나 전투가 벌어지는데...\n강적을 만난 루피!\n과연 이길 수 있을 것인가?\n두둥!\n\n");
	printf("Press <Enter> to continue...\n");
	getchar();
	printf("======== 기 본 정 보 ========\n");
}

void print_set(void) {
	srand((unsigned int)time(NULL));
	LHP = (rand() % 21 + 20) + PLUS_HP, LAT = rand() % 11 + 5 + PLUS_ATK;
	CHP = rand() % 21 + 30, CAT = rand() % 11 + 10;
	KI = 1;
	CHANGE = 0;
}

void print_info(void) {
	printf("루피       HP : %d, 공격력: %d, LV : %d\n", LHP, LAT, LV);
	printf("크로커다일 HP : %d, 공격력: %d\n\n", CHP, CAT);
}

void print_condition(void) {
	printf("\n루피       HP : %d, 기 : %d배, LV : %d\n", LHP, KI, LV);
	printf("크로커다일 HP : %d", CHP);
	if (CHANGE == 1) {
		printf(", 모래로 변신");
	}
	printf("\n");
}

void luffy_turn(void) {
	printf("\n========= 루피 차례 =========\n1. 공격!\n2. 기 모으기\n");
	printf("=============================\n\n루피가 할 행동을 선택하세요(1/2):");
	scanf_s("%d", &ATK);
	if (ATK == LUF_ATTACK) {
		printf("\n루피의 공격: '고무고무 총!' X %d\n", KI);
		if (CHANGE == 1) {
			printf("크로커다일의 방어로 데미지가 반감됩니다.\n");
			printf("크로커다일: %d - %d = ", CHP, (LAT * KI) / 2);
			CHP -= (LAT * KI) / 2;
		}
		else {
			printf("크로커다일: %d - %d = ", CHP, LAT * KI);
			CHP -= LAT * KI;
		}
		if (CHP < 0) CHP = 0;
		printf("%d\n", CHP); KI = 1;
	}
	else if (ATK = LUF_HOLD) {
		printf("\n루피가 기를 모으고 있습니다...\n"); KI *= 2;
	}
	if (CHP == 0) {
		printf("\n루피가 크로커다일을 쓰러뜨렸다!\n");
		PLUS_MONEY = rand() % 501 + 500;
		printf("승자는 루피!\n크로커다일에게 %d원을 갈취했다!\n", PLUS_MONEY);
		MONEY += PLUS_MONEY; LV++; PLUS_HP = LV * 3;
		printf("루피 LV: %d\n루피의 추가 체력이 %d이(가) 되었다.\n", LV, PLUS_HP);
		BREAK_NO = 1;
	}
}

void crocodile_turn(void) {
	printf("\n======== 크로커다일 차례 ========\n");
	CATK = rand() % 3;
	CHANGE = 0;
	if (CATK == CRC_ATTACK) {
		printf("크로커다일의 공격: '사막의 폭풍 !'\n");
		if (KI > 1) {
			printf("\n데미지를 받아서 루피가 모아둔 기가 흩어집니다.\n");
			KI = 1;
		}
		printf("루피: %d - %d = ", LHP, CAT);
		LHP -= CAT;
		if (LHP < 0) {
			LHP = 0;
		}
		printf("%d\n", LHP);
	}
	else if (CATK == CRC_TRANS) {
		printf("크로커다일이 몸을 모래로 바꿉니다.\n");
		CHANGE = 1;
	}
	else if (CATK == CRC_HOLD) {
		printf("크로커다일은 여유를 부립니다: '니가 칠무해가 뭔지 알아? \n\n");
	}
	if (LHP == 0) {
		printf("\n칠무해의 벽은 너무 높았다...\n승자는 크로커다일!\n크로커다일에게 가진 돈을 모두 빼앗겼다!\n");
		MONEY = 0;
		BREAK_NO = 2;
	}
}

void fight(void) {
	print_set();
	print_info();
	while (1) {
		BREAK_NO = 0;
		luffy_turn();
		if (BREAK_NO == 1) {
			break;
		}
		print_condition();
		crocodile_turn();
		if (BREAK_NO == 2) {
			break;
		}
		print_condition();
	}
}

void voya(void) {
	EVENT_SWITCH = 0;
	printf("소지금: %d골드\n", MONEY);
	printf("추가 공격력: %d\n", PLUS_ATK);
	printf("추가 체력: %d\n", PLUS_HP);
	printf("*********************\n");
	int i = 0;
	while (i < 21) {
		if (MEET == 10 && i == 10) {
			setColor(RED);
			printf("!");
			setColor(WHITE);
			EVENT_SWITCH = 1;
		}
		else if (i == 10) {
			printf("M");
		}
		else if (i == MEET) {
			printf("?");
		}
		else {
			printf(" ");
		}
		i++;
	}
	MEET--;
	if (MEET == -1) {
		MEET = 20;
	}
	printf("\n*********************\n");
}

void event(void) {
	EVENT_NO = rand() % 3 + 1;
	while (1) {
		if (EVENT_NO == 1) {
			PLUS_MONEY = rand() % 501;
			printf("\n보물상자에서 %d골드를 발견했다!\n", PLUS_MONEY);
			MONEY += PLUS_MONEY;
			Sleep(3000);
			break;
		}
		else if (EVENT_NO == 2) {
			printf("\n무기를 발견했다!\n");
			PLUS_ATK = rand() % 6 + 5;
			printf("루피의 추가 공격력이 %d이(가) 되었다.\n", PLUS_ATK);
			Sleep(3000);
			break;

		}
		else {
			printf("\n\n아니 저자는! 칠무해 크로커다일!\n\n");
			fight();
			Sleep(3000);
			break;
		}
	}
}

void end(void) {
	if (MONEY >= 2000) {
		printf("루피는 %d골드를 모아 해적왕이 되었다고 한다...\n", MONEY);
		exit(0);
	}
	else if (MONEY <= 0) {
		printf("가진 돈을 모두 잃은 루피는 해적을 은퇴하게 된다...\n");
		exit(0);
	}
}


int main(void) {
	intro();
	while (1) {
		voya();
		if (EVENT_SWITCH == 1) {
			srand((unsigned int)time(NULL));
			event();
		}
		Sleep(200);
		end();
		system("cls");
	}
}
