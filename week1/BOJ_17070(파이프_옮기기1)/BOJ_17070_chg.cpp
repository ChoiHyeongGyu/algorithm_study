#include <iostream>

using namespace std;

/*
1. �����б�
	- ����� ��
	- dfs�� ����Ž��
	- ��ȣ�ʸ��̶� ���?
*/

// �ʿ� ���ڵ�
int N; // ���� ũ��
int map[16][16]; // ���� ����
int path[11]; // ������ ���̾Ҵ��� ���
int ans = 0;

// ������ �� �κ��� y��ǥ x��ǥ ���
// now�� ���� �������� ���� (0: ����, 1: ����, 2: �밢��)
void dfs(int y, int x, int now) {

	// 3. �������� ���ο� ���� �ܾ��� �Ǻ�
	if (now == 0) {
		if (map[y][x] == 1 || map[y][x - 1] == 1)
			return;
	}
	if (now == 1) {
		if (map[y][x] == 1 || map[y-1][x] == 1)
			return;
	}
	if (now == 2) {
		if (map[y][x] == 1 || map[y][x - 1] == 1 || map[y - 1][x] == 1 || map[y - 1][x - 1] == 1)
			return;
	}

	// 2. ���� ���� -> �������� ��ǥ�� �����ϸ� return
	if (y == N - 1 && x == N - 1) {
		ans++;

		return;
	}

	// 1. ���� ��ͷ� ���
	// ���γ� ���γ� �밢���̳Ŀ� ���� �ٸ���
	// ���� �Ѿ�� ��� �Ǻ�
	if (now == 0) {
		if (x + 1 < N) {
			dfs(y, x + 1, 0);
			if (y + 1 < N) {
				dfs(y + 1, x + 1, 2);
			}
		}
	}
	if (now == 1) {
		if (y + 1 < N) {
			dfs(y + 1, x, 1);
			if (x + 1 < N) {
				dfs(y + 1, x + 1, 2);
			}
		}
	}
	if (now == 2) {
		if (x + 1 < N) {
			dfs(y, x + 1, 0);
			if (y + 1 < N) {
				dfs(y + 1, x + 1, 2);
			}
		}
		if (y + 1 < N)
			dfs(y + 1, x, 1);
	}
}


int main() {

	// �ʿ��ϴٸ� �ʱ�ȭ

	// input
	cin >> N;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i][j];
		}
	}

	// solve -> dfs�� ���� Ž��
	dfs(0, 1, 0);

	// output
	cout << ans;

	return 0;
}