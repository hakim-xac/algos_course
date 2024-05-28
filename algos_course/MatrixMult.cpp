#include "MatrixMult.h"


namespace Course
{
	//-------------------------------

	MatrixMult::MatrixMult(std::string_view filename)
		: _filename{ filename }
		, _data{}
		, _laboriousness{}
		, _brackets{}
	{
		load();
		calculate();
	}

	//-------------------------------

	void MatrixMult::printHeader() const
	{
		std::cout << std::setw(35) << std::setfill('=') << "\n" << std::setfill(' ');
		std::cout << std::setw(10) << "Student:" << std::setw(25) << "Khakimov A.S.\n";
		std::cout << std::setw(10) << "Variant:" << std::setw(25) << "# 1\n";
		std::cout << std::setw(36) << std::setfill('=') << "\n\n" << std::setfill(' ');
	}

	//-------------------------------

	void MatrixMult::printLaboriousness() const
	{
		size_t col_size{ _data.size() };

		std::cout << "Матрица минимальных трудоемкостей:\n";

		for (size_t index{}; auto && elem : _laboriousness)
		{
			std::cout << std::setw(4) << elem << ((index++ + 1) % col_size == 0 ? "\n" : " ");
		}
		std::cout << "\n";
	}

	//-------------------------------

	void MatrixMult::printBrackets() const
	{
		size_t col_size{ _data.size() };

		std::cout << "Матрица для расстановки скобок:\n";

		for (size_t index{}; auto && elem : _brackets)
		{
			std::cout << std::setw(4) << elem << ((index++ + 1) % col_size == 0 ? "\n" : " ");
		}
		std::cout << "\n";
	}

	//-------------------------------

	void MatrixMult::printBracketSequence() const
	{
		std::cout << "Результат скобочной последовательности:\n";
		result(1, _data.size() - 1);
		std::cout << "\n";
	}

	//-------------------------------

	void MatrixMult::printMaxLaboriousness() const
	{
		std::cout << "Полученная трудоемкость равна: " << _laboriousness[_data.size() * 2 - 1] << "\n";
	}

	//-------------------------------

	void MatrixMult::result(size_t row, size_t col) const
	{
		size_t col_index{ _data.size() };
		if (row == col)
		{
			std::cout << " M" << row;
			return;
		}

		std::cout << "(";
		result(row, _brackets[row * col_index + col]);
		std::cout << " * ";
		result(_brackets[row * col_index + col] + 1, col);
		std::cout << " )";
	}

	//-------------------------------

	void MatrixMult::load()
	{
		std::ifstream fs{ _filename.data() };
		if (fs.is_open() == false) [[unlikely]]
		{
			std::cerr << "Error: can not open file " << std::quoted(_filename) << "\n";
			return;
		}

		for (size_t tmp{}; fs >> tmp;)
			_data.emplace_back(tmp);
	}

	//-------------------------------

	void MatrixMult::calculate()
	{
		assert(_data.empty() == false);

		size_t col_size{ _data.size() };

		_laboriousness.resize(col_size * col_size);
		_brackets.resize(col_size * col_size);

		for (size_t l{ 2 }; l < _data.size(); ++l)
		{
			for (size_t i{ 1 }; i <= _data.size() - l; ++i)
			{
				size_t j{ i + l - 1 };

				_laboriousness[i * col_size + j] = std::numeric_limits<int32_t>::max();

				for (size_t k{ i }; k <= j - 1; ++k)
				{
					size_t a{ _laboriousness[i * col_size + k] + _laboriousness[col_size * (k + 1) + j] };

					size_t q{ a + _data[i - 1] * _data[k] * _data[j] };

					std::cout << "---------------------\n";
					std::cout << "( " << i << " ; " << j << " ) + ";
					std::cout << _data[i - 1] << " * " << _data[k] << " * " << _data[j];
					std::cout << " = " << q << "\n";

					if (q < _laboriousness[i * col_size + j]) [[likely]]
					{
						std::cout << "+\n========\n";
						_laboriousness[i * col_size + j] = q;
						_brackets[i * col_size + j] = k;
					}
				}
			}
		}
	}

	//-------------------------------

}