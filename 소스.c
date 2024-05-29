#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define LEN_MIN 15
#define LEN_MAX 50
#define STM_MIN 0
#define STM_MAX 5
#define PROB_MIN 10
#define PROB_MAX 90
#define AGGRO_MIN 0
#define AGGRO_MAX 5
#define MOVE_LEFT 1
#define MOVE_STAY 0
#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGSEOK 2
#define ACTION_REST 0
#define ACTION_PROVOKE 1
#define ACTION_PULL 2

void sh(int);
void sh(int a) {
	int i;

	for (i = 0; i < a; i++) {
		printf("#");
	}

	return;
}

void bl(int);
void bl(int bl) {
	for (int i = 0; i < bl; i++) {
		printf(" ");
	}

	return;
}

void sl(int);
void sl(int c) {
	int i;

	for (i = 0; i < c; i++) {
		printf("-");
	}

	return;
}

int distance(int, int);
int distance (int first_coordinate, int second_coordinate) {
	int result = second_coordinate - first_coordinate - 1;

	return result;
}

int MAXMIN(int, int, int, char);
int MAXMIN(int fuc, int max_min, int x, char pm) {
	int result = fuc;
	if (pm == 'p') {
		if (fuc + x < max_min) {
			result = fuc + x;
		} 
		else {
			result = max_min;
		}
	}
	else if (pm == 'm') {
		if (fuc - x > max_min) {
			result = fuc - x;
		}
		else {
			result = max_min;
		}
	}
	return result;
}

int main() {
	int tl = 0, p = 0, stm = -1;

	while (tl > LEN_MAX || tl < LEN_MIN) {
		printf("train lenght (%d ~ %d) : ", LEN_MIN, LEN_MAX);
		scanf_s("%d", &tl);
	}
	while (stm > STM_MAX || stm < STM_MIN) {
		printf("madongseokstamina (%d ~ %d) : ", STM_MIN, STM_MAX);
		scanf_s("%d", &stm);
	}
	while (p > PROB_MAX || p < PROB_MIN) {
		printf("percentile probability 'p' (%d ~ %d) : ", PROB_MIN, PROB_MAX);
		scanf_s("%d", &p);
	}

	sl(tl);
	printf("\n");
	sh(tl);
	printf("\n#");
	bl(tl - 7);
	printf("C  ZM#\n");
	sh(tl);

	int prob_of_citizen, prob_of_zombie, prob_of_mds;
	int coordinate_of_citizen = tl - 5, coordinate_of_zombie = tl - 2, coordinate_of_mds = tl - 1;
	int pre_coordinate_of_zombie;
	int distance_of_citizen, distance_of_c2z, distance_of_z2m=0, distance_of_m2d=0;
	int tr = 0;
	int movement_of_citizen, movement_of_zombie, movement_of_mds = 2;
	int aggro_of_citizen=0, aggro_of_mds=0;
	int mds_takes_zombie = 0;
	int stay_aggro_of_citizen = 0, pre_aggro_of_citizen = 0, stay_aggro_of_mds = 0, pre_aggro_of_mds = 0, pre_stm;
	int action_of_mds = 3;
	while (1) {
		srand(time(NULL));
		printf("\n\n");
		sl(tl);
		printf("\nturn: : %d", tr + 1);

		printf("\n\n");
		prob_of_citizen = rand() * rand() % 101 % 101;
		prob_of_zombie = rand() * rand() % 101 % 101;
		prob_of_mds = rand() * rand() % 101 % 101;
		pre_aggro_of_citizen = aggro_of_citizen;

		//printf("\n%d %d", prob_of_citizen, prob_of_zombie);
		//Sleep(2000);

		//printf("%d.%d\n", aggro_of_citizen, pre_aggro_of_citizen);

		//2-3

		if (prob_of_citizen < 100 - p ) {		//�ù� �̵�
			coordinate_of_citizen--;
			movement_of_citizen = 1;
			aggro_of_citizen = MAXMIN(aggro_of_citizen, AGGRO_MAX, 1, 'p');
			stay_aggro_of_citizen = 1;
		}
		else {
			movement_of_citizen = 0;
			aggro_of_citizen = MAXMIN(aggro_of_citizen, AGGRO_MIN, 1, 'm');
			stay_aggro_of_citizen = 0;
		}

		//printf("%d.%d\n", aggro_of_citizen, pre_aggro_of_citizen);
		
		distance_of_c2z = distance(coordinate_of_citizen, coordinate_of_zombie) - 1;
		distance_of_z2m = distance(coordinate_of_zombie, coordinate_of_mds);

		pre_coordinate_of_zombie = coordinate_of_zombie;

		if (tr % 2 == 0 && mds_takes_zombie == 0) {		//���� ¦���� ���� ���������� ������ �ʾ��� ��� ���� �̵�
			if (prob_of_zombie < p && aggro_of_citizen >= aggro_of_mds && distance_of_c2z > 0) {		//���� �̵� ����, �ù� ��׷� > ������ ��׷�, �ù�-���� �Ÿ� 0 �ʰ�
				//coordinate_of_zombie = MAXMIN(coordinate_of_zombie, distance_of_c2z, 1, "m");
				coordinate_of_zombie--;
				movement_of_zombie = 1;
			}
			else if (prob_of_zombie < p && aggro_of_citizen < aggro_of_mds && distance_of_z2m > 0) {		// ���� �̵� ����, ������ ��׷� > �ù� ��׷�, ����-������ �Ÿ� 0 �ʰ�
				//coordinate_of_zombie = MAXMIN(coordinate_of_zombie, distance_of_z2m, 1, "p");
				coordinate_of_zombie++;
				movement_of_zombie = 1;
			}
			else {
				movement_of_zombie = 0;
			}
		}
		else {
			movement_of_zombie = 0;
		}

		distance_of_citizen = coordinate_of_citizen - 1;
		distance_of_c2z = distance(coordinate_of_citizen, coordinate_of_zombie) -1;
		distance_of_z2m = distance(coordinate_of_zombie, coordinate_of_mds);
		distance_of_m2d = distance(coordinate_of_mds, tl);

		printf("%d.%d.%d.%d\n", coordinate_of_citizen, distance_of_c2z, distance_of_z2m, distance_of_m2d);

		sh(tl);
		printf("\n#");
		bl(distance_of_citizen);
		printf("C");
		bl(distance_of_c2z);
		printf("Z");
		bl(distance_of_z2m);
		printf("M");
		bl(distance_of_m2d);
		printf("#\n");
		sh(tl);
		printf("\n\n");

		if (movement_of_citizen == 1) {
			printf("citiizen : %d > %d", coordinate_of_citizen + 1, coordinate_of_citizen);
		}
		else {
			printf("citizen : stay %d", coordinate_of_citizen);
		}
		
		printf(" (aggro: %d > %d)\n", pre_aggro_of_citizen, aggro_of_citizen);

		if (movement_of_zombie == 1) {
			printf("zombie: %d > %d", pre_coordinate_of_zombie, coordinate_of_zombie);
		}
		else {
			printf("zombie: stay %d", coordinate_of_zombie);
		}

		if (tr % 2 == 0) {
			printf("\n\n");
		}
		else if ( tr % 2 != 0) {
			printf(" (cannot move)\n\n");
		}
		else if (mds_takes_zombie == 1) {
			printf(" (zombie pulled by Madongseoek, cannot move)");
		}

		mds_takes_zombie == 0;

		if (coordinate_of_citizen == 1) {
			printf("\nSUCCES! \n Citizen(s) to the next train.\n");

			return 0;
		}

		//printf("%d\n", distance_of_z2m);

		if (distance_of_z2m != 0) {		//������ �̵�
			while (movement_of_mds != MOVE_LEFT && movement_of_mds != MOVE_STAY) {
				printf("Madongseok move (0 : stay, 1 : left) : ");
				scanf_s("%d", &movement_of_mds);
			}
			printf("\n");
		}
		else {
			movement_of_mds = 0;
		}
		
		pre_aggro_of_mds = aggro_of_mds;		//��׷� ��ġ ���� �� ���� �� ����
		pre_stm = stm;		//���׹̳� ��ġ ���� �� ���� �� ����

		if(movement_of_mds == 1) {		//�������� �̵���/���� ���� ��� ��׷� ����/����
			coordinate_of_mds--;
			aggro_of_mds = MAXMIN(aggro_of_mds, AGGRO_MAX, 1, 'p');
			stay_aggro_of_mds = 1;
		}
		else if (movement_of_mds == 0) {
			aggro_of_mds = MAXMIN(aggro_of_mds, AGGRO_MIN, 1, 'm');
			stay_aggro_of_mds = 2;
		}

		distance_of_z2m = distance(coordinate_of_zombie, coordinate_of_mds);		//����-������ �Ÿ� �� ���
		distance_of_m2d = distance(coordinate_of_mds, tl);	//������-�� �Ÿ� �� ���

		//printf("%d\n", distance_of_z2m);

		sh(tl);		//������ �̵� �� ���
		printf("\n#");
		bl(coordinate_of_citizen - 1);
		printf("C");
		bl(distance_of_c2z);
		printf("Z");
		bl(distance_of_z2m);
		printf("M");
		bl(distance_of_m2d);
		printf("#\n");
		sh(tl);
		printf("\n\n");

		if (movement_of_mds != MOVE_LEFT ) {		//������ ��ġ�� ���
			printf("Madongseok : stay %d", coordinate_of_mds);
		}
		else {
			printf("Madongseok : %d > %d", coordinate_of_mds-1, coordinate_of_mds);
		}
		if (stay_aggro_of_mds > 0) {		//������ �̵��� ���� ��׷ΰ� ���� '��ġ�� ���'�� �̾ ���
			printf(" (aggro: %d > %d, stamina: %d)\n", pre_aggro_of_mds, aggro_of_mds, stm);
		}
		else {
			printf(" (aggro: %d, stamina: %d)\n", aggro_of_mds, stm);
		}

		//2-4
		printf("\ncitizen does nothing.\n");	
		if (distance_of_c2z == 0 && distance_of_z2m == 0) {		//���� �ùΰ� ������ ��ο� ������ ���
			if (aggro_of_citizen > aggro_of_mds) {		//��׷ΰ��� ���������� �ù��� ū ��� ����� �ù��� ���� > ���ӿ���
				printf("GAME OVER! citizen dead...");
				
				return 0;
			}
			else {		//�� �ݴ��� ��� �ùΰ� ������ ��׷� �� �� ������ ���׹̳� ���� ���
				printf("Zombie attacked Madongseok (aggro : %d vs %d) Madongseok stamina : %d > %d\n", aggro_of_citizen, aggro_of_mds, pre_stm, stm);
				stm = MAXMIN(stm, STM_MAX, 1, 'm');
				if (stm < 1) {
					printf("GAME OVER! Madongseok dead...");
					
					return 0;
				}
			}
		}
		else if (distance_of_c2z == 0) {		//���� �ùΰ� ������ ��� ���ӿ���
			printf("GAME OVER! citizen dead...");
			return 0;
		}
		else if (distance_of_z2m == 0 && movement_of_mds == 1) {		//���� �������� �����ϰ� �������� �̵����� ���
			while (action_of_mds != ACTION_PROVOKE && action_of_mds != ACTION_REST && action_of_mds != ACTION_PULL) {		//������ �ൿ �Է�
				printf("Madongseok action (0:rest, 1:provoke, 2:pull) : ");
				scanf_s("%d", &action_of_mds);
			}
			if(action_of_mds == ACTION_REST) {	
				aggro_of_mds = MAXMIN(aggro_of_mds, AGGRO_MIN, 1, 'm');
				stm = MAXMIN(stm, STM_MAX, 1, 'p');
				printf("Madongseok rests...\nMadongseok: %d (aggro: %d > %d, stamina: %d > %d)", coordinate_of_mds, pre_aggro_of_mds, aggro_of_mds, pre_stm, stm);
			}
			else if (action_of_mds == ACTION_PROVOKE) {
				aggro_of_mds = AGGRO_MAX;
				printf("Madongsoek provided zombie...\nMadongsoek: %d (aggro: %d > %d, stamina: %d)", coordinate_of_mds, pre_aggro_of_mds, aggro_of_mds, stm);
			}
			else if (action_of_mds == ACTION_PULL) {
				aggro_of_mds = MAXMIN(aggro_of_mds, AGGRO_MAX, 2, 'p');
				stm = MAXMIN(stm, STM_MAX, 1, 'm');
				printf("%d\n", prob_of_mds);
				if (stm > STM_MIN) {
					if (prob_of_mds < 101 - p) {
						mds_takes_zombie = 1;
						printf("Madongseok pulled zombie... Next turn, it can't move\nMadongseok: %d (aggro: %d > %d, stamina: %d > %d)", coordinate_of_mds, pre_aggro_of_mds, aggro_of_mds, pre_stm, stm);
					}
					else {
						printf("Madongsoek failed to pull zomibe\nMadongseok: %d (aggro: %d > %d, stamina: %d > %d)", coordinate_of_mds, pre_aggro_of_mds, aggro_of_mds, pre_stm, stm);
						mds_takes_zombie = 0;
					}
				}
				else {
					printf("GAME OVER! Madongseok dead...");

					return 0;
				}
				
			}
		}
		else if (distance_of_c2z != 0 && distance_of_z2m != 0) {		//�ùΰ� ���� �������� �ʰ� �������� ����� �������� ���� ���
			while (action_of_mds != ACTION_PROVOKE && action_of_mds != ACTION_REST) {
				printf("Madongseok action (0:rest, 1:provoke) : ");
				scanf_s("%d", &action_of_mds);
			}
			if (action_of_mds == ACTION_REST) {
				aggro_of_mds = MAXMIN(aggro_of_mds, AGGRO_MIN, 1, 'p');
				stm = MAXMIN(stm, STM_MAX, 1, 'p');
				printf("Madongseok rests...\nMadongseok: %d (aggro: %d > %d, stamina: %d > %d)", coordinate_of_mds, pre_aggro_of_mds, aggro_of_mds, pre_stm, stm);
			}
			else if (action_of_mds == ACTION_PROVOKE) {
				aggro_of_mds = AGGRO_MAX;
				printf("Madongsoek provided zombie...\nMadongsoek: %d (aggro: %d > %d, stamina: %d)", coordinate_of_mds, pre_aggro_of_mds, aggro_of_mds, stm);
			}
		}

		action_of_mds = 3;
		movement_of_mds = 2;		//'������ �̵�'�� 0,1�� �ƴ� ��� ���� �ݺ� > 0,1�� �ƴ� �� ����

		//Sleep(4000);

		tr++;
	}

	return 0;
}