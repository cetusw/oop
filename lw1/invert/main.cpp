#include <array>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

using Matrix = std::array<std::array<double, 3>, 3>; // array

void PrintHelp()
{
	auto helpFile = std::ifstream("../utils/help.txt");
	std::string line;
	while (std::getline(helpFile, line))
	{
		std::cout << line << std::endl;
	}
}

bool ReadMatrix3x3(Matrix& matrix3x3, std::istream& file)
{
	std::string line;
	int rows = 0;

	while (std::getline(file, line))
	{
		if (rows >= 3)
		{
			return false;
		}
		std::stringstream ss(line);
		double num;
		int cols = 0;

		while (ss >> num)
		{
			if (cols >= 3)
			{
				return false;
			}

			matrix3x3[rows][cols] = num;
			cols++;
		}

		if (cols != 3)
		{
			return false;
		}
		rows++;
	}

	return rows == 3;
}

void PrintMatrix3x3(const Matrix& matrix3x3)
{
	std::cout << std::fixed << std::setprecision(3);
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::cout << matrix3x3[i][j] << "\t";
		}
		std::cout << std::endl;
	}
}

double GetMatrix3x3Determinant(const Matrix& matrix3x3)
{
	return matrix3x3[0][0] * (matrix3x3[1][1] * matrix3x3[2][2] - matrix3x3[1][2] * matrix3x3[2][1])
		- matrix3x3[0][1] * (matrix3x3[1][0] * matrix3x3[2][2] - matrix3x3[1][2] * matrix3x3[2][0])
		+ matrix3x3[0][2] * (matrix3x3[1][0] * matrix3x3[2][1] - matrix3x3[1][1] * matrix3x3[2][0]);
}

Matrix GetMinorsMatrix3x3(const Matrix& matrix3x3)
{
	Matrix minorMatrix3x3;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			const int row1 = (i + 1) % 3;
			const int row2 = (i + 2) % 3;
			const int col1 = (j + 1) % 3;
			const int col2 = (j + 2) % 3;

			minorMatrix3x3[i][j] = matrix3x3[row1][col1] * matrix3x3[row2][col2]
				- matrix3x3[row1][col2] * matrix3x3[row2][col1];
		}
	}

	return minorMatrix3x3;
}

Matrix GetAlgebraicComplementMatrix3x3(Matrix matrix3x3)
{
	matrix3x3[0][1] = -matrix3x3[0][1];
	matrix3x3[1][0] = -matrix3x3[1][0];
	matrix3x3[1][2] = -matrix3x3[1][2];
	matrix3x3[2][1] = -matrix3x3[2][1];

	return matrix3x3;
}

Matrix GetTransposedMatrix3x3(const Matrix& matrix3x3)
{
	Matrix transposedMatrix3x3;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			transposedMatrix3x3[j][i] = matrix3x3[i][j];
		}
	}

	return transposedMatrix3x3;
}

Matrix MultiplyMatrix3x3ByNumber(const Matrix& matrix3x3, const double number) // передавать  1 / number
{
	Matrix inverseMatrix3x3;

	const double inverseDeterminant = 1 / number;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			inverseMatrix3x3[i][j] = inverseDeterminant * matrix3x3[i][j];
		}
	}

	return inverseMatrix3x3;
}

void FindInverseMatrix3x3(const Matrix& matrix3x3) // вернуть матрицу, а потом вывести
{
	const double matrix3x3Determinant = GetMatrix3x3Determinant(matrix3x3);
	if (matrix3x3Determinant == 0)
	{
		throw std::invalid_argument("Non-invertible");
	}
	const Matrix minorsMatrix3x3 = GetMinorsMatrix3x3(matrix3x3);
	const Matrix transposedMatrix3x3 = GetTransposedMatrix3x3(minorsMatrix3x3);
	const Matrix inverseMatrix3x3 = MultiplyMatrix3x3ByNumber(transposedMatrix3x3, matrix3x3Determinant);
	PrintMatrix3x3(inverseMatrix3x3);
}

int main(const int argc, char* argv[])
{
	if (argc > 2)
	{
		std::cout << "ERROR" << std::endl;
		return 1;
	}

	if (argc == 2 && std::strcmp(argv[1], "-h") == 0)
	{
		PrintHelp();
		return 0;
	}

	Matrix matrix3x3;
	if (argc == 2)
	{
		std::ifstream inputFile(argv[1]);
		if (!inputFile.is_open())
		{
			std::cout << "ERROR" << std::endl;
			return 1;
		}
		if (!ReadMatrix3x3(matrix3x3, inputFile))
		{
			std::cout << "Invalid matrix format" << std::endl;
			return 1;
		}
	}
	else
	{
		if (!ReadMatrix3x3(matrix3x3, std::cin))
		{
			std::cout << "Invalid matrix format" << std::endl;
			return 1;
		}
	}

	try
	{
		FindInverseMatrix3x3(matrix3x3); // сначала распарсить аргументы
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	return 0;
}
