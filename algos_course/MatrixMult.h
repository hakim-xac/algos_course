#pragma once

#include "common.h"

namespace Course
{
	class MatrixMult {
	public:

		//-------------------------------

		explicit MatrixMult(std::string_view filename);

		//-------------------------------

		void printHeader() const;

		//-------------------------------

		void printLaboriousness() const;

		//-------------------------------

		void printBrackets() const;

		//-------------------------------

		void printBracketSequence() const;

		//-------------------------------

		void printMaxLaboriousness() const;

		//===============================
	private:

		//-------------------------------

		void result(size_t row, size_t col) const;

		//-------------------------------

		void load();

		//-------------------------------

		void calculate();

		//===============================
	private:
		std::string_view _filename;
		std::vector<size_t> _data;
		std::vector<size_t> _laboriousness;
		std::vector<size_t> _brackets;
	};
}