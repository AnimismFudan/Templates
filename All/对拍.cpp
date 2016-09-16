#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

int main()
{
	while(true)
	{
		system("./mkd");
		system("./E");
		system("./E_");

		if(system("diff E.out E_.out"))
		{
			printf("WA!\n");
			break;
		}
		else printf("YES!\n");
	}
	return 0;
}
