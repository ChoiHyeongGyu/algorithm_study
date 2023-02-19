#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

/*
1. �����б�
	- ��ŸƮ ��ũ�� ������ ������ ��ġ
	- dfs�� ���ݸ� �̾Ƽ� ��
*/

// �ʿ� ���ڵ�
int N; // ��� ��
int arr[17][17]; // 1���� ������ ��
int MIN = 21e8;
int visited[17]; // �� ǥ�� ���� dat (1: st��, 0: li��)
int tmp;


void reset() {
	memset(arr, 0, sizeof(arr));
	MIN = 21e8;
}

void input() {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
		}
	}
}

void dfs(int lv, int start) {

	// 2. ���� ���� -> N/2�� ������ ����
	if (lv == N / 2) {

		vector<int> st; // ��ŸƮ ������ �ε���
		vector<int> li; // ��ũ ������ �ε���
		int st_score = 0; // ��ŸƮ ���� ����
		int li_score = 0; // ��ũ ���� ����

		for (int i = 1; i <= N; i++) {
			// st�� li�� ������ �ε��� �־���
			if (visited[i] == 1)
				st.push_back(i);
			else
				li.push_back(i);
		}

		for (int i = 0; i < N / 2; i++) {
			for (int j = 0; j < N / 2; j++) {
				// st�� li�� ���� ������ ������
				st_score += arr[st[i]][st[j]];
				li_score += arr[li[i]][li[j]];
			}
		}

		tmp = abs(st_score - li_score); // �� ���� ������
		if (tmp < MIN) {
			MIN = tmp;
		}

		return;
	}

	// 1. ���� ��ͷ� ���
	// �����̴ϱ� �����͸� �̱�
	for (int i = start + 1; i <= N; i++) {

		// 3. ��� �� ó��
		visited[i] = 1; // st�� �̰� ���
		dfs(lv + 1, i);
		visited[i] = 0; // st�� ����
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

		// solve -> dfs Ž��
		dfs(0, 0);

		// output
		cout << "#" << tc << " " << MIN << endl;
	}

	return 0;
}