#include <iostream>
#include <algorithm>

using namespace std;

/*
1. �����б�
	- ����� ��
	- DFS, �ּҰ��̴ϱ� backtracking���� ����� �� ���̱�
	- �� �������� Ž��
	- 12�� �Ǹ� ����
*/

// �ʿ� ���ڵ�
int MIN;
int price[4]; // 1�ϱ�, �Ѵޱ�, ���ޱ�, 1���
int plan[12]; // 12���� �̿��ȹ
int sum;

void reset() {
	sum = 0;
}

void input() {
	for (int i = 0; i < 4; i++) {
		cin >> price[i];
	}
	for (int i = 0; i < 12; i++) {
		cin >> plan[i];
	}
	MIN = price[3]; // MAX�� ����ȸ������ �ְ� ����
}

// 0�� 1���� ��
void dfs(int month) {

	// ���� ���� -> 12������ Ž���ϸ� ����
	if (month >= 12) {
		if (sum < MIN)
			MIN = sum; // �ּҰ� ��
		return;
	}

	// ���� ��ͷ� ���. 1�ϱ� 1�ޱ� 3�ޱ����� ������ ���
	// 1�ϱ�
	sum += price[0] * plan[month];
	dfs(month + 1);
	sum -= price[0] * plan[month];
	// 1�ޱ�
	sum += price[1];
	dfs(month + 1);
	sum -= price[1];
	// 3�ޱ�
	sum += price[2];
	dfs(month + 3);
	sum -= price[2];


	/*
	// �ٵ� �̰� �� �� �ʿ���� ���ؼ� �����ϸ� �ɵ�
	// 3�޸��� ���ϰ� 1�� ��
	// �̹���� ����, ���ϴµ� ���ܰ� 3��� ���ܹ���
	int tmp1 = 0, tmp2 = 0, tmpp = 0, tmp3 = 0;
	for (int i = month; i < month + 3; i++) {
		if (i >= 12) continue;
		tmp1 = price[0] * plan[i];
		tmp2 = price[1];
		tmpp += min(tmp1, tmp2);
	}
	tmp3 = price[2];

	// 3�ޱ��� ���� �� ���
	if (tmp3 < tmpp) {
		sum += tmp3;
		dfs(month + 3);
		sum -= tmp3;
	}

	else {
		tmp1 = price[0] * plan[month];
		tmp2 = price[1];
		// 1�ϱ��� ���� �� ���
		if (tmp1 <= tmp2) {
			sum += tmp1;
			dfs(month + 1);
			sum -= tmp1;
		}
		// 1�ޱ��� ���� �� ���
		else {
			sum += tmp2;
			dfs(month + 1);
			sum -= tmp2;
		}
	}
	*/
}

int main() {

	int tc, testCase;
	cin >> testCase;

	for (tc = 1; tc <= testCase; tc++) {
		// �׽�Ʈ ���̽����� �ʱ�ȭ
		reset();

		// input
		input();

		// solve -> DFS�� Ž��
		dfs(0);

		// output
		cout << "#" << tc << " " << MIN << endl;
	}

	return 0;
}