#pragma warning (disable: 4996)
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstring>
#include <Windows.h>

#define AND 0
#define OR 1
#define XOR 2
#define DONUT 3

////// 컴퓨터과학부 2015920019 박서원
//////- 실험 과제
//////(1) AND, OR, XOR 구분 실험
//////(2) 도우넛 모양 구분 실험(아래 데이터 이용)
//////
//////- Layer 수, Layer 당 node 수는 변수로 지정할 것.-
//////- weight는 행렬 형식으로 파일에 저장
//////- Learning 과정을 그래프로 보여주기(X1, X2 2차원 직선 그래프).
//////- 각 노드마다 직선을 그림으로 표시.
//////- iteration에 따른 Error 그래프
//////- 구현언어: C, C++
//////- 제출물 : 프로그램, 결과 보고서
//////실행 10 %, 출력 10, 주석 10, 완성도 25, 오류 10, 창의 10 보고서 25 %


// train sets
double AND_x[4][2] = { {0, 0}, {0 ,1}, {1, 0}, {1, 1} };
double AND_y[4] = { 0, 0, 0, 1 };

double OR_x[4][2] = { {0, 0}, {0 ,1}, {1, 0}, {1, 1} };
double OR_y[4] = { 0, 1, 1, 1 };

double XOR_x[4][2] = { {0, 0}, {0 ,1}, {1, 0}, {1, 1} };
double XOR_y[4] = { 0, 1, 1, 0 };

float train_set_x[9][2] = { {0.,0.},
 {0.,1.},
 {1.,0.},
 {1.,1.},
 {0.5,1.},
 {1.,0.5},
 {0.,0.5},
 {0.5,0.},
 {0.5,0.5} };
float train_set_y[9] = { 0,0,0,0,0,0,0,0,1 };

// 학습 과정 확인용
int t = 0;


class NODE {
	// NODE는 자신의 값과 delta를 저장하고 있다.
private:
	double value;	// 한 노드에 들어온 활성함수값, 또한 다음 노드를 위한 inpu값
	double delta;	// backpropagation을 위한 delta값
public:

	// 노드의 값과 delta값을 모두 -1로 초기화된다.
	NODE() {
		value = delta = -1;
	}

	void set_value(double val) { value = val; }
	void set_delta(double del) { delta = del; }
	double get_value() { return value; }
	double get_delta() { return delta; }
	// 활성함수는 시그모이드함수
	// 미분값은 다음과 같다.
	double get_derivative() {
		double ret;
		// sigmoid
		ret = (1 - value) * value;
		return ret;
	}
};

class LAYER {
	// LAYER는 NODE들을 가지고 있다.
	// 또한 weight 각 i~i+1  layer 사이의 weight matrix도 가지고 있따.
public:
	NODE* node;	// layer당 노드 배열
	int nodeEA;	// layer당 노드 개수
	// LAYER의 weight 배열은 2차원 배열이다
	// weight[a][b]	이것은 layer[i]의 a번째노드에서
	// layer[i+1]의 b번째노드로 향하는 weight이다.
	double** weight;

public:
	// Layer당 Weight 초기 랜덤 할당 함수이다.
	void LAYER_WeightSetting(int nodeEA) {

		// input노드가 3개이므로 hiddenlayer의 노드 개수들이
		// 3보다 작으면 인풋노드를 위해 최소한의 weight를 생성해주어야함.
		int n = this->nodeEA = nodeEA;
		if (n < 3)
			n = 3;
		
		// weight배열을 랜덤으로 할당한다. -2~2 사이로 한다
		srand(time(0));
		weight = new double* [n];
		for (int i = 0; i < n; i++) {
			weight[i] = new double[n];
			for (int j = 0; j < n; j++) {
				weight[i][j] = rand() / (double)(RAND_MAX / 4) - 2;
				//printf("%lf\t", weight[i][j]);
			}
		}
	}

	// 레이어의 노드 초기 생성 함수이다.
	void set_Node_EA(int ea) {
		// 현재 레이어의 실제 노드 개수를 정해준다
		nodeEA = ea;
		// 그리고 그만큼 노드를 생성한다
		node = new NODE[ea];
	}
};

class MLP {
	//MLP는 LAYER들을 가지고 있다
	// 입력층을 0번 Layer라 한다
	// 1~n-2 layer는 hiddenLayer이다.
	// n-1 Layer는 출력(레이어)노드이다.
	// 히든 레이어는 모두 다른 노드개수를 가질 수 있게 설정할 수 있다.
	// 편의상 학습시 모든 히든레이어가 같은 노드개수를 가지게 하였다.
private:
	LAYER* layer;	// layer배열
	int layerEA;	// 배열의 개수
	int hiddenLayerNodeEA;	// 히든레이어당 노드 개수
	double tol = 0.2;	// 오차허용범위
	double c = 2;		// 학습률

public:
	MLP() {
		// Mlp를 생성한다
		printf("새로운 MLP 생성\n");
		printf("입출력포함 LAYER수와 HiddenLayer 당 최대 노드 수를 입력하세요 : ");
		scanf("%d %d", &layerEA, &hiddenLayerNodeEA);

		// MLP에 LAYER들을 만든다
		layer = new LAYER[layerEA];

		// 각 LAYER들의 weight를 세팅해준다
		// 여기서는 모든 LAYER가 hiddenLayerNodeEA개의 노드를 가진다가정하고
		// weight를 세팅하였다.
		// 인풋 레이어=3, 아웃풋레이어는=1 의 노드개수를 가진다.
		// 아웃풋레이어에서는 출력이 다른 노드로 나가지 않으므로 -1까지만 세팅해주었다.
		// 또한 첫번째 가중치와 마지막 가중치는 사용하지 않는 부분이 있다
		// 첫레이어는 노드가 3개, 마지막은 1개이기 때문이다.
		/*	0	1	2	3	4	5	6	layerEA-1
			.	ㅁ	ㅁ	ㅁ	ㅁ	ㅁ	ㅁ	.
			.	ㅁ	ㅁ	ㅁ	ㅁ	ㅁ	ㅁ	.
			ㅁ	ㅁ	ㅁ	ㅁ	ㅁ	ㅁ	ㅁ	.
			ㅁ	ㅁ	ㅁ	ㅁ	ㅁ	ㅁ	ㅁ	ㅁ
			ㅁ	ㅁ	ㅁ	ㅁ	ㅁ	ㅁ	ㅁ	.
			.	ㅁ	ㅁ	ㅁ	ㅁ	ㅁ	ㅁ	.
			.	ㅁ	ㅁ	ㅁ	ㅁ	ㅁ	ㅁ	.
		*/
		for (int i = 0; i < layerEA - 1; i++)
			layer[i].LAYER_WeightSetting(hiddenLayerNodeEA);


		// 그리고 Hiddenlayer의 노드들도 생성해준다
		// 모두 같은 노드개수를 가진다 가정하고 생성해주었다
		for (int i = 1; i < layerEA - 1; i++)
			layer[i].set_Node_EA(hiddenLayerNodeEA);


		// 초기 레이어의 노드를 생성해준다. x0=-1, x1,x2노드를 생성해준다.
		layer[0].set_Node_EA(3);
		// output노드도  하나 생성해준다.
		layer[layerEA - 1].set_Node_EA(1);

	}

private:

	// layer당 웨이트를 txt파일에 출력한다.
	void print_weight(int sample) {
		int N = layerEA - 2;
		for (int i = 0; i <= N; i++) {
			FILE* file = make_txt(i, sample);
			int A = layer[i].nodeEA;
			int B = layer[i + 1].nodeEA;
			fprintf(file, "layer[%d]\n", i);

			for (int a = 0; a < A; a++) {
				for (int b = 0; b < B; b++) {
					//fprintf(file, "w[%d][%d] = %lf\t", a, b, layer[i].weight[a][b]);
					fprintf(file, "%lf ", layer[i].weight[a][b]);
				}
				fprintf(file, "\n");
			}

			/*
			for (int a = 0; a < A; a++) {
				for (int b = 0; b < B; b++) {
					fprintf(file, "%lf ", layer[i].weight[b][a]);
				}
				fprintf(file, "\n");
			}
			*/
			fclose(file);
		}
	}

	// weight를 저장할 txt파일을 만드는 함수
	FILE* make_txt(int n, int sample) {
		char str1[15];
		switch (sample)
		{
		case AND:
			strcpy(str1, "AND");
			break;
		case OR:
			strcpy(str1, "OR");
			break;
		case XOR:
			strcpy(str1, "XOR");
			break;
		case DONUT:
			strcpy(str1, "DONUT");
			break;
		}
		char str2[4];
		itoa(n, str2, 10);
		strcat(str1, str2);
		strcat(str1, ".txt");
		FILE* file = fopen(str1, "w+");
		return file;
	}

	// 활성함수, 시그모이드함수
	double activation_sigmoid(double net) {
		double ret;
		// sigmoid
		ret = 1 / (1 + exp(-net));
		return	ret;
	}

	// 인풋값받기
	void set_input(double x1, double x2) {
		layer[0].node[0].set_value(-1);
		layer[0].node[1].set_value(x1);
		layer[0].node[2].set_value(x2);
	}

	double get_Output() {
		// 0 Layer부터 n-2 Layer까지
		// 하나의 Layer가 다음 Layer를 갱신시킨다
		// A는 현재 Layer 노드 개수, B는 다음 Layer 노드 개수이다.
		// 변수 i는 0~layerEA-2까지 이동.
		// 1~n-1 순서대로LAyer를 갱신.
		int A, B;
		// 재귀하지 않고 for문으로 해결
		// i번 layer에서 i+1번 Layer를 갱신


		for (int i = 0; i < layerEA - 1; i++) {
			A = layer[i].nodeEA;
			B = layer[i + 1].nodeEA;

			for (int b = 0; b < B; b++) {
				double net = 0;
				for (int a = 0; a < A; a++) {
					net += (layer[i].node[a].get_value() * layer[i].weight[a][b]);
				}
				// i+1 레이어의 b번의 활성화함수에 들어갈 net을 구한후 
				// 활성화함수 값을 i+1 레이어의 b번째 노드에 넣는다.
				double a_output = activation_sigmoid(net);
				layer[i + 1].node[b].set_value(a_output);
			}
		}

		// 마지막 출력노드의 출력값을 리턴한다
		double ret = layer[layerEA - 1].node[0].get_value();
		printf("%lf\n", ret);
		return ret;
	}

	// 상위층의 델타값을 이용하여
	// 하위층 노드들의 델타를 모두 구해준다
	// 그 후 상위층과 하위층 사이의 웨이트를 모두 수정한다
	void learning_BackPropagation(double target, double Output) {

		// 출력 노드의 델타는 따로 구해준다
		// delta = -(t-O)*f'
		double tmp = -(target - Output) * layer[layerEA - 1].node[0].get_derivative();
		layer[layerEA - 1].node[0].set_delta(tmp);


		for (int i = layerEA - 2; i >= 0; i--) {
			int A = layer[i].nodeEA;		// i레이어 노드 개수,
			int B = layer[i + 1].nodeEA;	//i + 1 레이어 노드 개수

			// i레이어의 노드들의 델타를 i+1노드들을 이용해 구해줌
			for (int a = 0; a < A; a++) {
				double sum = 0;
				for (int b = 0; b < B; b++) {
					double upDelta = layer[i + 1].node[b].get_delta();
					double byWeight = layer[i].weight[a][b];
					sum += upDelta * byWeight;
				}
				double newDelta = layer[i].node[a].get_derivative() * sum;
				layer[i].node[a].set_delta(newDelta);
			}
		}

		// 상위층의 델타를 이용하여 하위층 weight 갱신
		for (int i = layerEA - 2; i >= 0; i--) {
			int A = layer[i].nodeEA;
			int B = layer[i + 1].nodeEA;
			for (int a = 0; a < A; a++) {
				for (int b = 0; b < B; b++) {
					double upDelta = layer[i + 1].node[b].get_delta();
					double downOutput = layer[i].node[a].get_value();
					double del_Weight = -c * upDelta * downOutput;
					layer[i].weight[a][b] += del_Weight;
				}
			}
		}
	}

public:

	// AND 게이트 학습
	void startLearningAND() {
		printf("AND 학습 시작 : \n");
		int sample_EA = 4;

		t = 0;	// 학습 과정 확인용
		while (true) {
			bool pass = true;

			// E = ( SIGMA (t-O)^2 ) / 2
			double E = 0;

			t++;	// 학습 과정 확인용

			for (int i = 0; i < sample_EA; i++) {
				double x1 = AND_x[i][0], x2 = AND_x[i][1];
				set_input(x1, x2);			// input을 입력한다.
				double target = AND_y[i];	// target값 저장
				double Output = get_Output();	//output값 저장

				E += (target - Output) * (target - Output);

				// 학습 과정 확인용
				if (t % 20 == 0) {
					printf("node%d, %lf %lf %lf\n", i, layer[1].node[0].get_value(), layer[1].node[1].get_value(), layer[1].node[2].get_value());
				}

				// 정답이 아니면 학습한다
				if (abs(target - Output) > tol) {
					pass = false;
					learning_BackPropagation(target, Output);
				}
			}
			E = E / 2;
			//printf("%lf ",E);
			//printf("\n");

			// 학습 과정 확인용
			if (t % 20 == 0) {
				printf("\tw  %lf %lf %lf\n", layer[1].weight[0][0], layer[1].weight[1][0], layer[1].weight[2][0]);
			}

			// 일정 횟수 이상 학습하면 종료한다
			if (t > 100000000) {
				printf("절반성공\n");
				break;
			}

			if (pass) {
				printf("성공\n");
				break;
			}
		}

		print_weight(AND);
	}

	// OR게이트 학습
	void startLearningOR() {
		printf("OR 학습 시작 : \n");
		int sample_EA = 4;
		while (true) {
			bool pass = true;

			// E = ( SIGMA (t-O)^2 ) / 2
			double E = 0;

			t = 0;

			for (int i = 0; i < sample_EA; i++) {
				double x1 = OR_x[i][0], x2 = OR_x[i][1];
				set_input(x1, x2);			// input을 입력한다.
				double target = OR_y[i];	// target값 저장
				double Output = get_Output();	//output값 저장

				E += (target - Output) * (target - Output);

				// 학습 과정 확인용
				if (t % 20 == 0) {
					printf("node%d, %lf %lf %lf\n", i, layer[1].node[0].get_value(), layer[1].node[1].get_value(), layer[1].node[2].get_value());
				}

				// 정답이 아니면 학습한다
				if (abs(target - Output) > tol) {
					pass = false;
					learning_BackPropagation(target, Output);
				}
			}
			E = E / 2;
			//printf("%lf ", E);
			//printf("\n");

			// 학습 과정 확인용
			if (t % 20 == 0) {
				printf("\tw  %lf %lf %lf\n", layer[1].weight[0][0], layer[1].weight[1][0], layer[1].weight[2][0]);
			}


			// 일정 횟수 이상 학습하면 종료한다
			if (t > 100000000) {
				printf("절반성공\n");
				break;
			}

			if (pass) {
				printf("성공\n");
				break;
			}
		}

		print_weight(OR);
	}

	// XOR 게이트 학습
	void startLearningXOR() {
		printf("XOR 학습 시작 : \n");
		int sample_EA = 4;
		while (true) {
			bool pass = true;

			// E = ( SIGMA (t-O)^2 ) / 2
			double E = 0;

			t = 0;

			for (int i = 0; i < sample_EA; i++) {
				double x1 = XOR_x[i][0], x2 = XOR_x[i][1];
				set_input(x1, x2);			// input을 입력한다.
				double target = XOR_y[i];	// target값 저장
				double Output = get_Output();	//output값 저장

				E += (target - Output) * (target - Output);

				// 학습 과정 확인용
				if (t % 100 == 0) {
					printf("node%d, %lf %lf %lf\n", i, layer[1].node[0].get_value(), layer[1].node[1].get_value(), layer[1].node[2].get_value());
				}


				// 정답이 아니면 학습한다

				if (abs(target - Output) > tol) {
					pass = false;
					learning_BackPropagation(target, Output);
				}
			}
			E = E / 2;
			//printf("%lf ", E);
			//printf("\n");

			// 학습 과정 확인용
			if (t % 100 == 0) {			
				printf("\tw  %lf %lf %lf\n", layer[1].weight[0][0], layer[1].weight[1][0], layer[1].weight[2][0]);
			}


			// 일정 횟수 이상 학습하면 종료한다
			if (t > 100000000) {
				printf("절반성공\n");
				break;
			}

			if (pass) {
				printf("성공\n");
				break;
			}
		}
		print_weight(XOR);
	}

	// DOUNT모양 학습
	void startLearningDONUT() {
		printf("DONUT 학습 시작 : \n");
		int sample_EA = 9;
		while (true) {
			bool pass = true;

			// E = ( SIGMA (t-O)^2 ) / 2
			double E = 0;

			t = 0;

			for (int i = 0; i < sample_EA; i++) {
				double x1 = train_set_x[i][0], x2 = train_set_x[i][1];
				set_input(x1, x2);			// input을 입력한다.
				double target = train_set_y[i];	// target값 저장
				double Output = get_Output();	//output값 저장

				E += (target - Output) * (target - Output);


				// 학습 과정 확인용
				if (t % 100 == 0) {
					printf("node%d, %lf %lf %lf\n", i, layer[1].node[0].get_value(), layer[1].node[1].get_value(), layer[1].node[2].get_value());
				}


				// 정답이 아니면 학습한다
				if (abs(target - Output) > tol) {
					pass = false;
					learning_BackPropagation(target, Output);
				}
			}
			E = E / 2;
			//printf("%lf ", E);
			//printf("\n");

			// 학습 과정 확인용
			if (t % 100 == 0) {
			
				printf("\tw  %lf %lf %lf\n", layer[1].weight[0][0], layer[1].weight[1][0], layer[1].weight[2][0]);
			}


			// 일정 횟수 이상 학습하면 종료한다
			if (t > 100000000) {
				printf("절반성공\n");
				break;
			}

			if (pass) {
				printf("성공\n");
				break;
			}
		}

		print_weight(DONUT);
	}

};


int main() {

	MLP mlp;
	mlp.startLearningAND();

	MLP mlp2;
	mlp2.startLearningOR();

	MLP mlp3;
	mlp3.startLearningXOR();

	MLP mlp4;
	mlp4.startLearningDONUT();

}
