#include "MatrixMult.h"

int main()
{
	std::setlocale(LC_ALL, "");

	Course::MatrixMult mm { "in.txt" };

	mm.printHeader();
	mm.printLaboriousness();
	mm.printBrackets();

	mm.printBracketSequence();
	mm.printMaxLaboriousness();

	[[maybe_unused]] int c{ getchar() };

	return 0;
}
