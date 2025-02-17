#include <stdio.h>
#include "platform.h"
#include "sw_top.h"

int main(){
	init_platform();

	TestCase = USE_SEQUENTIAL_KEYS;

	print("Hello Hashtable!\n\r");

	int i,j;
	for(i = 19; i < 21; i++){
		SysAlloc_init();
		xor_rng_init();
		int log2_size = i;
		table_init(log2_size);
		int *hdTable;
		putnum(log2_size);
		print(" ");

		for(j = 1; j<5; j++){
			if(j == 1){
				Xil_Out32(COUNTER_BASE + 4 * 1, START);
				hdTable = PM_1_INSERTION(log2_size);
				Xil_Out32(COUNTER_BASE + 4 * 1, STOP);
			}
			if(j == 2){
				Xil_Out32(COUNTER_BASE + 4 * 2, START);
				PM_2_CHECK_INSERTION(hdTable, log2_size);
				Xil_Out32(COUNTER_BASE + 4 * 2, STOP);
			}
			if(j == 3){
				Xil_Out32(COUNTER_BASE + 4 * 3, START);
				PM_3_UPDATE(hdTable, log2_size);
				Xil_Out32(COUNTER_BASE + 4 * 3, STOP);
			}
			if(j == 4){
				Xil_Out32(COUNTER_BASE + 4 * 4, START);
				PM_4_DELETION(hdTable);
				Xil_Out32(COUNTER_BASE + 4 * 4, STOP);
			}

			int read_value = Xil_In32(COUNTER_BASE + 4 * (j + 8));
			if(read_value != 0){
				putnum(read_value);
			}
			putnum(Xil_In32(COUNTER_BASE + 4 * j));
			print(" ");
			Xil_Out32(COUNTER_BASE + 4 * j, RESET);
		}
		print("\n");
	}
	print("\n all done\n");


	cleanup_platform();
	return 0;
}
