#include <iostream>

using namespace std;

/*
1. �����б�
	- ����� �� (�ִ�, �ּ�)
	- �ִ�ϱ� ����Ž��
	- �ּҴ� backtracking
	- BOJ 14888�� ����
*/

// �ʿ� ���ڵ�
int N; // ���� ����
int Num[12]; // ���� �迭
int Sign[4]; // �������� �迭
int MIN = 21e8;
int MAX = -21e8;
int path[12]; // ������ ���̾Ҵ��� ���
int tmp;

void reset() {
	MIN = 21e8;
	MAX = -21e8;
}

void input() {
	cin >> N;
	for (int i = 0; i < 4; i++) {
		cin >> Sign[i];
	}
	for (int i = 0; i < N; i++) {
		cin >> Num[i];
	}
}

void func(int lv) {

	// 2. ���� ���� -> ������ N-1�� ������ ����
	if (lv == N - 1) {
		tmp = Num[0];
		// path���� �ϳ��� �̾ƿͼ� �� ��ȣ�� �´� ����
		for (int i = 0; i < N - 1; i++) {
			if (path[i] == 0) {
				tmp += Num[i + 1];
			}
			if (path[i] == 1) {
				tmp -= Num[i + 1];
			}
			if (path[i] == 2) {
				tmp *= Num[i + 1];
			}
			if (path[i] == 3) {
				tmp /= Num[i + 1];
			}
		}

		// �ִ� �ּ� ��
		if (tmp > MAX)
			MAX = tmp;
		if (tmp < MIN)
			MIN = tmp;

		return;
	}

	// 1. ���� ��ͷ� ���
	// 0���� �����ڴ� �ѱ�� �������߿� �̱�
	for (int i = 0; i < 4; i++) {

		if (Sign[i] == 0)
			continue; // ���� ������ ���� �����ڴ� �н�

		// 3. ��� �� ó��
		path[lv] = i; // ���� ������ ���
		Sign[i]--; // ���� ������ 1����
		func(lv + 1);
		path[lv] = 0; // ��� ����
		Sign[i]++;
	}

}


int main() {

	int tc, testCase;
	cin >> testCase;

	for (tc = 1; tc <= testCase; tc++) {
		// �׽�Ʈ ���̽����� �ʱ�ȭ
		reset();

		// input
		input();

		// solve -> ����Ž��
		func(0);

		// output
		cout << "#" << tc << " " << MAX-MIN << endl;
	}

	return 0;
}