#include <iostream>
#include <stdio.h>

int main() {

	signed char x, z;
	short int y, v;

	x = 1;
	y = -2;
	z = 5;
	
	//x = -62;
	//y = 32499;
	//z = -126;

	//scanf("%p", &z);

	__asm__ (
			".intel_syntax noprefix;"
			"xor eax, eax;"
			"xor ebx, ebx;"
			"xor ecx, ecx;"
			""
			"mov al, %3;" //z
			"cbw;" //al->ax
			"cwde;" //ax->eax
			"sub eax, 4;" //z - 4
			""
			"mov ecx, eax;" //save eax
			"mov ax, %2;" //y
			"cwde;" //ax->eax
			"mov ebx, eax;"
			"mov eax, ecx;" //restore
			""
			"imul eax, ebx;"   // eax = eax * ebx
			""
			"mov ebx, eax;" //save eax to ebx
			""
			"mov al, %1;" //x
			"cbw;" //ax => x
			"cwde;" //ax -> eax
			""
			"add eax, ebx;" //...+x => eax
			"mov ebx, eax;" //save to ebx -> UP
			""
			"mov al, %1;" //get x
			"cbw;" //to ax
			"cwde;" //ax->eax
			""
			"imul eax, 7;" //x * 7
			"sub eax, 6;" //...-6 ->ax -> DOWN
			""
			"mov ecx, eax;"
			"mov eax, ebx;" // eax-> UP
			"mov ebx, ecx;" //ebx ->DOWN
			"cdq;" //EAX -> EDX:EAX
			""
			"idiv ebx;"
			"sub eax, 1;"
			"mov %0, ax;"
			""
			".att_syntax;"
			: "=r" (v) /* Output -- %0 */
			: "r"  (x), "r" (y), "r" (z)
			: "eax", "ebx", "ecx", "edx"
			);

	std::cout << v;

	return 0;
}
