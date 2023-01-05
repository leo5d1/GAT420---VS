#include <iostream> 
#include <vector>
#include <array>

using namespace std;

void DisplayCellsRow(const vector<bool>& cells);
vector<bool> ProcessCells(const vector<bool>& cells, const array<bool, 8>& rule);

int main()
{
	srand((unsigned int)time(nullptr));
	int cellsInRow = 50;
	int iterations = 40;

	vector<bool> cells(cellsInRow, false);
	//cells[cellsInRow / 2] = true;

	for (int i = 0; i < 5; i++)
	{
		cells[rand() % (cells.size() - 1)] = true;
	}

	system("Color 0A");

	// rules 
	array<bool, 8> rule30 = { 0, 0, 0, 1, 1, 1, 1, 0 };
	array<bool, 8> rule90 = { 0, 1, 0, 1, 1, 0, 1, 0 };
	array<bool, 8> rule110 = { 0, 1, 1, 0, 0, 1, 1, 0 };
	array<bool, 8> rule182 = { 1, 0, 1, 1, 0, 1, 1, 0 };

	// display each iteration 
	for (int i = 0; i < iterations; i++)
	{
		DisplayCellsRow(cells);
		cells = ProcessCells(cells, rule30);
	}
}

void DisplayCellsRow(const vector<bool>& cells)
{
	for (auto cell : cells)
	{
		if (!cell)
		{
			cout << "-";
		}
		else
		{
			cout << "X";
		}
		cout << " ";
	}
	cout << "" << endl;
}

vector<bool> ProcessCells(const vector<bool>& cells, const array<bool, 8>& rule)
{
	vector<bool> processed(cells.size());

	for (int i = 0; i < processed.size(); i++)
	{
		bool states[3];
		int left;
		if ((i - 1) < 0)
		{
			left = cells.size() - 1;
		}
		else
		{
			left = i - 1;
		}
		states[0] = cells[left];
		states[1] = cells[i];
		int right;
		if (i + 1 >= cells.size())
		{
			right = 0;
		}
		else
		{
			right = i + 1;
		}
		states[2] = cells[right];

		bool state = false;

		// current pattern 111 110 101 100 011 010 001 000 
		// rule			    0   1   2   3   4   5   6   7 
		if (states[0] && states[1] && states[2]) state = rule[0];
		else if (states[0] && states[1] && !states[2]) state = rule[1];
		else if (states[0] && !states[1] && states[2]) state = rule[2];
		else if (states[0] && !states[1] && !states[2]) state = rule[3];
		else if (!states[0] && states[1] && states[2]) state = rule[4];
		else if (!states[0] && states[1] && !states[2]) state = rule[5];
		else if (!states[0] && !states[1] && states[2]) state = rule[6];
		else if (!states[0] && !states[1] && !states[2]) state = rule[7];

		processed[i] = state;
	}

	return processed;
}