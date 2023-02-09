#include <iostream>
#include <vector>

using namespace std;

/*
1. �����б�
	- ����� �� (���߿����� ����)
	- �Է�(N)�� ũ�Ⱑ 4 ~ 20
	- ��Ͱڱ���
	- N/2�� ������ �������� �ٸ���
	- DFS�� Backtracking����
*/

// �ʿ� ���ڵ�
int N; // ��� ��
int arr[21][21]; // 1���� ������ ��
int MIN = 21e8;
int visited[21]; // �� ǥ�� ���� dat (1: st��, 0: li��)
int tmp;


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

		for (int i = 0; i < N/2; i++) {
			for (int j = 0; j < N/2; j++) {
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
	for (int i = start+1; i <= N; i++) {

		// 3. ��� �� ó��
		visited[i] = 1; // st�� �̰� ���
		dfs(lv + 1, i);
		visited[i] = 0; // st�� ����
	}

}


int main() {

	// �ʿ��ϴٸ� �ʱ�ȭ

	// input
	cin >> N;
	for (int i = 1; i <= N ; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> arr[i][j];
		}
	}

	// solve -> dfs Ž��
	 dfs(0, 0);

	// output
	 cout << MIN;

	return 0;
}