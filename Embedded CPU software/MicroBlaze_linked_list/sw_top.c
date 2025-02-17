#include <stdio.h>
#include "platform.h"
#include "sw_top.h"
#include "xio.h"

int main()
{
	init_platform();

	print("Hello World\n\r");



	int *hdList;
	int i,j;
	for(i =0; i < 21; i++){
		SysAlloc_init();

		int log2ListSize = i;
		int *hdList = NULL;

		putnum(log2ListSize);
		print(" ");

		XIo_Out32(COUNTER_BASE + 4 * 1, START);
		hdList = RandListGen(log2ListSize, hdList);
		XIo_Out32(COUNTER_BASE + 4 * 1, STOP);

		XIo_Out32(COUNTER_BASE + 4 * 2, START);
		hdList = ReverseList(hdList);
		XIo_Out32(COUNTER_BASE + 4 * 2, STOP);

		XIo_Out32(COUNTER_BASE + 4 * 3, START);
		hdList = DeleteList(hdList);
		XIo_Out32(COUNTER_BASE + 4 * 3, STOP);



		for(j = 1; j <4; j++){
			// read counter result back
			int high_value = XIo_In32(COUNTER_BASE + 4 * (j + 8));
			if(high_value != 0){
				putnum(high_value);
			}
			putnum(XIo_In32(COUNTER_BASE + 4 * j));
			print(" ");

			// reset counter
			XIo_Out32(COUNTER_BASE + 4 * j,RESET);
		}
		print("\n");
	}

	print("\n all done\n");

	cleanup_platform();
	return 0;
}
