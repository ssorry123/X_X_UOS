#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

// 라인당 바이트 번호.
// 0~94    * n      95개, '\n' 과 NULL까지
// 0~96    * m		97개

int NUMBER(int number[5], int where);

int oldKey[100] = { -1 }; int oldKeyCount = 0;	// 0 
int trsKey[100] = { -1 }; int trsKeyCount = 0;	// 1

int main(void)
{
	char code = NULL;
	char number[6];	//5로 하면 오류남.
	char name[15];
	char address[40];
	char car[10];
	char work[10];
	char phone[8];
	char c = NULL;
	int i;
	int oldSize, trsSize;
	char temp[100];

	FILE* cfPtr, * oldPtr, * trsPtr, * newPtr;

	/*
	// 올드 마스터 화일 생성.
	cfPtr = fopen("client.txt", "w+");
	printf("Enter the number, name, address, car, work, phone\n");
	printf("Enter EOF to end input\n? ");
	while (scanf("%s %s %s %s %s %s", number, name, address, car, work, phone) != NULL) {
		fprintf(cfPtr, "%-5s %-15s %-40s %-10s %-10s %-8s\n", number, name, address, car, work, phone);
		//fprintf(stdout, "--%-5s %-15s %-40s %-10s %-10s %-8s\n", number, name, address, car, work, phone);
		printf("? ");
	}
	fclose(cfPtr);
	*/

	/*
	// 트랜잭션 파일 생성.
	cfPtr = fopen("trans.txt", "w+");
	printf("Enter the number, name, address, car, work, phone, CODE\n");
	printf("Enter EOF to end input\n? ");
	while (scanf("%s %s %s %s %s %s %c", number, name, address, car, work, phone, &code ) != NULL) {
		fprintf(cfPtr, "%-5s %-15s %-40s %-10s %-10s %-8s %c\n", number, name, address, car, work, phone, code);
		printf("? ");
	}
	fclose(cfPtr);
	*/

	oldPtr = fopen("client.txt", "r");
	trsPtr = fopen("trans.txt", "r");
	newPtr = fopen("newClient.txt", "w+");

	// Size 측정
	fseek(oldPtr, 0, SEEK_END);
	oldSize = ftell(oldPtr);
	fseek(oldPtr, 0, SEEK_SET);
	printf("OLDMASTER화일의 크기 = %d \n", oldSize);

	printf("올드마스터화일출력>>>시작>>>\n");
	while (fread(&c, 1, 1, oldPtr))
		fprintf(stdout, "%c", c);
	printf("올드마스터화일출력>>>끝>>>\n");
	fseek(oldPtr, 0, SEEK_SET);


	fseek(trsPtr, 0, SEEK_END);
	trsSize = ftell(trsPtr);
	fseek(trsPtr, 0, SEEK_SET);
	printf("TRSMASTER화일의 크기 = %d \n", trsSize);

	printf("트랜스화일출력>>>시작>>>\n");
	while (fread(&c, 1, 1, trsPtr))
		fprintf(stdout, "%c", c);
	printf("트랜스화일출력>>>끝>>>\n");
	fseek(trsPtr, 0, SEEK_SET);

	// 키 추출
	i = 0;
	while (i < oldSize) {
		int arr[5];
		fseek(oldPtr, i, SEEK_SET);		fread(&c, 1, 1, oldPtr); arr[0] = c - '0';
		fseek(oldPtr, i + 1, SEEK_SET);	fread(&c, 1, 1, oldPtr); arr[1] = c - '0';
		fseek(oldPtr, i + 2, SEEK_SET);	fread(&c, 1, 1, oldPtr); arr[2] = c - '0';
		fseek(oldPtr, i + 3, SEEK_SET);	fread(&c, 1, 1, oldPtr); arr[3] = c - '0';
		fseek(oldPtr, i + 4, SEEK_SET);	fread(&c, 1, 1, oldPtr); arr[4] = c - '0';
		NUMBER(arr, 0);
		i = i + 95;
	}

	i = 0;
	while (i < trsSize) {
		int arr[5];
		fseek(trsPtr, i, SEEK_SET);		fread(&c, 1, 1, trsPtr); arr[0] = c - '0';
		fseek(trsPtr, i + 1, SEEK_SET);	fread(&c, 1, 1, trsPtr); arr[1] = c - '0';
		fseek(trsPtr, i + 2, SEEK_SET);	fread(&c, 1, 1, trsPtr); arr[2] = c - '0';
		fseek(trsPtr, i + 3, SEEK_SET);	fread(&c, 1, 1, trsPtr); arr[3] = c - '0';
		fseek(trsPtr, i + 4, SEEK_SET);	fread(&c, 1, 1, trsPtr); arr[4] = c - '0';
		NUMBER(arr, 1);
		i = i + 97;
	}

	// key 체크
	for (i = 0; i < oldKeyCount; i++)
		printf("%d ", oldKey[i]);
	for (i = 0; i < trsKeyCount; i++)
		printf("%d ", trsKey[i]);
	printf("\n");

	// 트랜잭션 시작

	{	printf("트랜잭션 시작...................................\n");
	int t = 0, o = 0;
	int tKey, oKey;
	tKey = trsKey[t];
	oKey = oldKey[o];
	fseek(oldPtr, 0, SEEK_SET);
	fseek(trsPtr, 0, SEEK_SET);
	fseek(newPtr, 0, SEEK_SET);
	while (1) {
		printf("tKey = %d, oKey = %d\n", tKey, oKey);
		if (tKey == -1)
			if (oKey == -1)
				break;
			else {	//나머지 구 마스터 레코드를 신 마스터 화일에 복사하라.
				while (fread(&c, 1, 1, oldPtr))
					fprintf(newPtr, "%c", c);
				break;
			}

		if (oKey == -1) {	// 트랜잭션 레코드에서 삽입인 것만 전부 복사하고 나머지는 오류로 거절.
			while (tKey != -1) {
				printf("[%d]의 트랜잭션이 실행되었습니다.(삽입)\n", tKey);
				fseek(trsPtr, 94, SEEK_CUR);
				fread(&c, 1, 1, trsPtr);
				fseek(trsPtr, -95, SEEK_CUR);
				switch (c)
				{
				case '0':	//삽입인 경우
					while (fread(&c, 1, 1, trsPtr) && c != '\n')
						fprintf(newPtr, "%c", c);
					fseek(newPtr, -2, SEEK_CUR);
					fprintf(newPtr, "%c", '\n');
					tKey = trsKey[++t];
					break;
				default:
					printf("[%d]의 트랜잭션이 거절되었습니다.\n", tKey);
					fseek(trsPtr, 97, SEEK_CUR);
					tKey = trsKey[++t];
					break;
				}
			}
			break;
		}

		// tKey 와 oKey 를 비교.
		if (tKey < oKey) {
			fseek(trsPtr, 94, SEEK_CUR);
			fread(&c, 1, 1, trsPtr);
			fseek(trsPtr, -95, SEEK_CUR);
			switch (c)
			{
			case '0':	//삽입인 경우
				printf("[%d]의 트랜잭션이 실행되었습니다.(삽입)\n", tKey);
				while (fread(&c, 1, 1, trsPtr) && c != '\n')
					fprintf(newPtr, "%c", c);
				fseek(newPtr, -2, SEEK_CUR);
				fprintf(newPtr, "%c", '\n');
				tKey = trsKey[++t];
				break;
			default:
				printf("[%d]의 트랜잭션이 거절되었습니다.\n", tKey);
				fseek(trsPtr, 97, SEEK_CUR);
				tKey = trsKey[++t];
				break;
			}
			//fseek(trsPtr, 97, SEEK_CUR);
		}
		else if (tKey == oKey) {
			fseek(trsPtr, 94, SEEK_CUR);
			fread(&c, 1, 1, trsPtr);
			fseek(trsPtr, -95, SEEK_CUR);
			switch (c)
			{
			case '1': case '3': case '4': case '5':	//수정인 경우 트랜스레코드를 신 화일에 복사하라.
				printf("[%d]의 트랜잭션이 실행되었습니다.(수정)\n", tKey);
				while (fread(&c, 1, 1, trsPtr) && c != '\n')
					fprintf(newPtr, "%c", c);
				fseek(newPtr, -2, SEEK_CUR);
				fprintf(newPtr, "%c", '\n');
				oKey = oldKey[++o];
				tKey = trsKey[++t];
				fseek(oldPtr, 95, SEEK_CUR);
				//printf("%d\n",ftell(trsPtr));

				break;
			case '2':								//삭제인경우
				printf("[%d]의 트랜잭션이 실행되었습니다.(삭제)\n", tKey);
				oKey = oldKey[++o];
				tKey = trsKey[++t];
				fseek(oldPtr, 95, SEEK_CUR);
				fseek(trsPtr, 97, SEEK_CUR);
				break;
			default:								//그외는 오류
				printf("[%d]의 트랜잭션이 거절되었습니다.\n", tKey);
				tKey = trsKey[++t];
				fseek(trsPtr, 97, SEEK_CUR);
				break;
			}
		}
		else {	// 구 마스터 레코드를 신 마스터 화일에 복사하라. 다음 구 마스터 레코드를 읽어라.
			printf("구마스터 레코드가 그대로 신 마스터화일로 이동하였습니다.\n");
			while (fread(&c, 1, 1, oldPtr) && c != '\n')
				fprintf(newPtr, "%c", c);
			fprintf(newPtr, "%c", '\n');
			oKey = oldKey[++o];
		}

	}
	printf("트랜잭션 적용 완료..............................\n");
	}

	fseek(newPtr, 0, SEEK_SET);
	while (fread(&c, 1, 1, newPtr))
		fprintf(stdout, "%c", c);

	fclose(oldPtr);
	fclose(trsPtr);
	fclose(newPtr);

	return 0;
}
int NUMBER(int number[5], int where) {
	int key = 0;

	key = number[0] * 10000 + number[1] * 1000 + number[2] * 100 + number[3] * 10 + number[4];

	if (where == 0) {
		oldKey[oldKeyCount++] = key;
		oldKey[oldKeyCount] = -1;
	}
	else if (where == 1) {
		trsKey[trsKeyCount++] = key;
		trsKey[trsKeyCount] = -1;
	}

	return key;
}
