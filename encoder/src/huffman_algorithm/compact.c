#include "encoder.h"


/**
 * It takes the encoded data and transform it into bytes. Checking if the last byte is not full. If it is not full, it will add the last byte to the compacted data. */
void	compact()
{
	int i = 0;
	int j = 7;
	int cp = 0;
	unsigned char byte = 0;
	unsigned char mask;

	printf("Compacting...\n");
	while(g_data.c_encode[i] != '\0')
	{
		mask = 1;
		if(g_data.c_encode[i] == '1')
		{
			mask = mask << j;
			byte = byte | mask;
		}
		j--;
		if (j < 0)
		{
			g_data.sh_mem->compact_data[cp] = byte;
			cp++;
			byte = 0;
			j = 7;
		}
		i++;
	}
	if(j != 7)
		g_data.sh_mem->compact_data[cp] = byte;
	g_data.sh_mem->compacted_bytes = cp + 1;
}
