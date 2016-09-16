#include <...>
register char *_sp __asm__("rsp");
int main(){
	const int size=64*1024*1024;
	static char *sys, *mine(new char[size]+size-4096);
	sys=_sp;
	_sp=mine;
	
	mmain();
	
	_sp=sys;
}