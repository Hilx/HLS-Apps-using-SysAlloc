#include "top.h"

int CHashTable(data_t *SlaveAXI, data_t *Master2Mem, data_t *Master2SysAlloc){

	#pragma HLS INTERFACE s_axilite port=SlaveAXI bundle=SlavePort
	#pragma HLS INTERFACE s_axilite port=return   bundle=SlavePort
	#pragma HLS INTERFACE m_axi depth=1 port=Master2Mem offset=off
	#pragma HLS INTERFACE m_axi depth=1 port=Master2SysAlloc offset=off

	int NumberOfItems = 35;
	
	ptr_t hdTable;
	hdTable = CreateHashTable(Master2Mem, Master2SysAlloc, HASH_TABLE_SIZE);

	int i;
	for(i = 0; i<NumberOfItems; i++){
		InsertNodeHashTable(Master2Mem, Master2SysAlloc, hdTable, i);
	}

	DeleteNodeHashTable(Master2Mem, Master2SysAlloc, hdTable, 3);
	DeleteNodeHashTable(Master2Mem, Master2SysAlloc, hdTable, 34);
	DeleteNodeHashTable(Master2Mem, Master2SysAlloc, hdTable, 17);
	
	ptr_t searchResult = SearchHashTable(Master2Mem, hdTable, 22);

	return searchResult;
}
