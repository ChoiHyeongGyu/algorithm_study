#include <iostream>

using namespace std;

/*
1. �����б�
	- ����� ��
	- DFS, �ִ밪�̴ϱ� ���� Ž���ؾ��ҵ�?
	- ����Ʈī�� ������ ���
	- 5�� �����߿� 4���� ��� ���� �̸� �ٸ�
*/

// �ʿ� ���ڵ�
int N, M; // ����ũ�� ����ũ��
int arr[500][500];
int MAX = -21e8;
int visited[500][500];
int diry[] = { -1,0,1,0 };
int dirx[] = { 0,-1,0,1 };
// �̸�� ���� ���� �� �� �� ��
int ey[4][4] = { {0, 0, 1, 0}, {0, -1, 0, 1}, {0, -1, 0, 0}, {0, -1, 0, 1} };
int ex[4][4] = { {0, -1, 0, 1}, {0, 0, -1, 0}, {0, 0, -1, 1}, {0, 0, 1, 0} };
int sum;


// 4���� ��� üũ dfs
void dfs(int lv, int y, int x) {

	// 2. ���� ���� -> 4�� �������� ����
	if (lv == 3) {

		if (sum > MAX)
			MAX = sum; // �ִ밪 ��
		
		return;
	}

	// 1. ���� ��ͷ� ���
	// ny, nx�� �� �� �ִ� ���̸� ����, �ƴϸ� continue
	for (int i = 0; i < 4; i++) {

		int ny = y + diry[i];
		int nx = x + dirx[i];
		
		// �� �� �ֳ� Ȯ���ϰ� �� �� �ֳ� üũ�ϰ�
		if (ny >= N || ny < 0 || nx >= M || nx < 0)
			continue;

		if (visited[ny][nx] == 1)
			continue;

		// 3. ��� �� ó��
		visited[ny][nx] = 1;
		sum += arr[ny][nx];
		dfs(lv + 1, ny, nx); // ���� ��������
		visited[ny][nx] = 0;
		sum -= arr[ny][nx];
	}

}


// �� ��� üũ
void exc(int y, int x) {

	for (int i = 0; i < 4; i++) {

		sum = 0;
		for (int j = 0; j < 4; j++) {

			int ny = y + ey[i][j];
			int nx = x + ex[i][j];

			// �� �� �ֳ� üũ, ������ break
			if (ny >= N || ny < 0 || nx >= M || nx < 0)
				break;

			sum += arr[ny][nx];
		}
		if (sum > MAX)
			MAX = sum;
	}
}


int main() {

	// �ʿ��ϴٸ� �ʱ�ȭ

	// input
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> arr[i][j];
		}
	}

	// solve -> ��� ������ dfs Ž��
	// �� ����� ����
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {

			sum = 0; // �ʱ�ȭ

			visited[i][j] = 1; // ������ üũ
			sum += arr[i][j]; // ������ ���ϱ�
			dfs(0, i, j); // 4���� ��� dfs
			visited[i][j] = 0;
			sum -= arr[i][j]; 

			exc(i, j);
		}
	}

	// output
	cout << MAX;

	return 0;
}