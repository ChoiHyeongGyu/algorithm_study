#include <iostream>
#include <vector>

using namespace std;

/*
1. �����б�
	- �� �ϲ��� ä���� ���� for������ ���ϰ�
	- dfs�� �� ���� �ִ밪 ���ϱ�
*/

// �ʿ� ���ڵ�
int max1, max2; // ���ϲ��ִ�, �����ִ�
int N, M, C; // ������ ũ��, ������ ����, ���� �ִ� ��
int hive[10][10]; // ����
vector<int> path;

void reset() {
	max2 = 0;
}

void input() {
	cin >> N >> M >> C;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> hive[i][j];
		}
	}
}

// ���� max ���ϴ� dfs
void dfs(int num, int sum, int y, int x) {

	// ���� ���� -> 1. ���� C������ return, 2. M�� ������ ����
	if (sum > C) {
		return;
	}
	if (num == M) {
		int tmp = 0;
		for (int i = 0; i < path.size(); i++) {
			tmp += path[i] * path[i];
		}
		if (tmp > max1)
			max1 = tmp;

		return;
	}

	// ���� ��ͷ� ���. �� ������ ������(1), ���� ��������(0)
	for (int select = 0; select < 2; select++) {
		// �Ȼ���
		if (select == 0) {
			dfs(num + 1, sum, y, x + 1);
		}
		// ����
		else {
			path.push_back(hive[y][x]);
			dfs(num + 1, sum + hive[y][x], y, x + 1);
			path.pop_back();
		}
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

		// solve -> 1. �� ���� ���ϰ�, �� �������� dfs�ִ밪
		for(int i = 0; i< N; i++)
			for (int j = 0; j <= N - M; j++) {
				int profit = 0;
				// �ϲ�1 ���ϱ�
				max1 = 0;
				dfs(0, 0, i, j);
				profit += max1;
				// �ϲ�2�� �ϲ�1���� ���ķ�
				max1 = 0;
				// �ϲ�1�� ������
				for (int l = j + M; l <= N - M; l++) {
					dfs(0, 0, i, l);
				}
				// �ٸ���
				for (int k = i + 1; k < N; k++) {
					for (int l = 0; l <= N - M; l++) {
						dfs(0, 0, k, l);
					}
				}
				profit += max1;

				if (profit > max2)
					max2 = profit;
			}

		// output
		cout << "#" << tc << " " << max2 << endl;
	}

	return 0;
}