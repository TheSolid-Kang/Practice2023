#include "CPractice.h"

int CPractice::Execute()
{
	Render();
	int result = Update();

	return result;
}
