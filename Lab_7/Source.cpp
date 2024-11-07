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
		cerr << "Помилка при зчитуванні файла графа."
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
	out << "Вхідні, вихідні та загальні степені вершин:\n";
	out << "| Вершина | Вхідний степінь | Вихідний степінь | Загальний степінь |\n";
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
	cout << "Введіть шлях до файлу графа: ";
	getline(cin, filePath);
	vector<vector<int>> edges;
	if (!readGraph(filePath, edges))
		return 1;

	cout << "Граф має " << N << " вершини і " << M << " ребер." << endl;
	cout << "Ребра графа:" << endl;

	for (size_t i = 0; i < edges.size(); i++) {
		cout << edges[i][0] + 1 << " - " << edges[i][1] + 1 << endl;
	}

	vector<int> inDegree, outDegree, Degree;
	calculateDegrees(edges, inDegree, outDegree, Degree);
	printDegrees(edges, inDegree, outDegree, Degree, cout);

	bool homogeneus = isHomogeneous(inDegree, outDegree);
	homogeneus ? (cout << "Граф є однорідним" << endl)
		: (cout << "Граф не є однорідним" << endl);

	vector<int> isolatedVertices = getIsolatedVertices(inDegree, outDegree);
	vector<int> hangingVertices = getHangingVertices(inDegree, outDegree);

	cout << "Ізольовані вершини: ";
	if (isolatedVertices.empty()) {
		cout << "Немає ізольованих вершин." << endl;
	}
	else {
		for (size_t i = 0; i < isolatedVertices.size(); i++) {
			cout << isolatedVertices[i] << " ";
		}
		cout << endl;
	}

	cout << "Висячі вершини: ";
	if (hangingVertices.empty()) {
		cout << "Немає висячих вершин." << endl;
	}
	else {
		for (size_t i = 0; i < hangingVertices.size(); i++) {
			cout << hangingVertices[i] << " ";
		}
		cout << endl;
	}
	string savePath;
	cout << "Введіть шлях для збереження степенів вершин: ";
	getline(cin, savePath);
	ofstream outFile(savePath);
	if (!outFile.is_open()) {
		cerr << "Помилка при відкритті файла для збереження степенів вершин."
			<< endl;
		return 2;
	}
	printDegrees(edges, inDegree, outDegree, Degree, outFile);
	outFile.close();
	cout << "Степені вершин успішно збережена." << endl;
	return 0;
}