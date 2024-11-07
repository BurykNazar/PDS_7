#include<iostream>
#include<iomanip>
#include<fstream>
#include<vector>
#include<string>
#include<Windows.h>

using namespace std;

unsigned int N, M;

bool readGraph(const string& fileStr, vector<vector<int>>& edges) {
	ifstream file(fileStr);
	if (!file.is_open()) {
		cerr << "������� ��� ��������� ����� �����."
			<< endl;
		return false;
	}
	file >> N >> M;
	edges.clear();
	edges.resize(M, vector<int>(2));
	for (int i = 0; i < M; i++) {
		file >> edges[i][0] >> edges[i][1];
		edges[i][0]--;
		edges[i][1]--;
	}
	file.close();
}

void calculateDegrees(const vector<vector<int>>& edges,
	vector<int>& inDegrees, vector<int>& outDegrees,
	vector<int>& Degrees) {
	inDegrees.assign(N, 0);
	outDegrees.assign(N, 0);
	Degrees.assign(N, 0);

	for (const auto& edge : edges) {
		int u = edge[0];
		int v = edge[1];
		outDegrees[u]++;
		inDegrees[v]++;
	}
	for (size_t i = 0; i < N; i++)
		Degrees[i] = inDegrees[i] + outDegrees[i];
}

void printDegrees(const vector<vector<int>>& edges,
	const vector<int>& inDegrees, const vector<int>& outDegrees,
	const vector<int>& Degrees, ostream& out) {
	out << "�����, ������ �� ������� ������ ������:\n";
	out << "| ������� | ������� ������ | �������� ������ | ��������� ������ |\n";
	out << "|---------|-----------------|------------------|-------------------|\n";

	for (int i = 0; i < N; i++) {
		out << "|   " << setw(2) << i + 1 << "    |";
		out << "     " << setw(4) << inDegrees[i] << "        |";
		out << "     " << setw(4) << outDegrees[i] << "         |";
		out << "     " << setw(6) << Degrees[i] << "        |\n";
	}
}

bool isHomogeneous(const vector<int>& inDegrees,
	const vector<int>& outDegrees) {
	for (size_t i = 1; i < inDegrees.size(); i++) {
		if (inDegrees[i] != inDegrees[0]) {
			return false; 
		}
	}

	for (size_t i = 1; i < outDegrees.size(); i++) {
		if (outDegrees[i] != outDegrees[0]) {
			return false;
		}
	}

	return true; 
}

vector<int> getIsolatedVertices(const vector<int>& inDegrees,
	const  vector<int>& outDegrees) {
	vector<int> isolatedVertices;
	for (size_t i = 0; i < N; i++)
		if (inDegrees[i] == 0 && outDegrees[i] == 0)
			isolatedVertices.push_back(i + 1);
	
	return isolatedVertices;
}

vector<int> getHangingVertices(const vector<int>& inDegrees,
	const vector<int>& outDegrees) {
	vector<int> hangingDegrees;
	for (size_t i = 0; i < N; i++)
		if ((inDegrees[i] == 0 && outDegrees[i] > 0) ||
			(inDegrees[i] > 0 && outDegrees[i] == 0))
			hangingDegrees.push_back(i + 1);
	return hangingDegrees;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	string filePath;
	cout << "������ ���� �� ����� �����: ";
	getline(cin, filePath);
	vector<vector<int>> edges;
	if (!readGraph(filePath, edges))
		return 1;

	cout << "���� �� " << N << " ������� � " << M << " �����." << endl;
	cout << "����� �����:" << endl;

	for (size_t i = 0; i < edges.size(); i++) {
		cout << edges[i][0] + 1 << " - " << edges[i][1] + 1 << endl;
	}

	vector<int> inDegree, outDegree, Degree;
	calculateDegrees(edges, inDegree, outDegree, Degree);
	printDegrees(edges, inDegree, outDegree, Degree, cout);

	bool homogeneus = isHomogeneous(inDegree, outDegree);
	homogeneus ? (cout << "���� � ���������" << endl)
		: (cout << "���� �� � ���������" << endl);

	vector<int> isolatedVertices = getIsolatedVertices(inDegree, outDegree);
	vector<int> hangingVertices = getHangingVertices(inDegree, outDegree);

	cout << "��������� �������: ";
	if (isolatedVertices.empty()) {
		cout << "���� ����������� ������." << endl;
	}
	else {
		for (size_t i = 0; i < isolatedVertices.size(); i++) {
			cout << isolatedVertices[i] << " ";
		}
		cout << endl;
	}

	cout << "������ �������: ";
	if (hangingVertices.empty()) {
		cout << "���� ������� ������." << endl;
	}
	else {
		for (size_t i = 0; i < hangingVertices.size(); i++) {
			cout << hangingVertices[i] << " ";
		}
		cout << endl;
	}
	string savePath;
	cout << "������ ���� ��� ���������� ������� ������: ";
	getline(cin, savePath);
	ofstream outFile(savePath);
	if (!outFile.is_open()) {
		cerr << "������� ��� ������� ����� ��� ���������� ������� ������."
			<< endl;
		return 2;
	}
	printDegrees(edges, inDegree, outDegree, Degree, outFile);
	outFile.close();
	cout << "������ ������ ������ ���������." << endl;
	return 0;
}