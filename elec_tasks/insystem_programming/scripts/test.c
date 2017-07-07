#include <stdio.h>
#include "data.h"

// read all characters from a file, outputting only the letter 'b's
// it finds in the file


int main(void)
{
	
	int i;
	int i_count = 0;  
	for( i=0; i<line_count;i++){

	
	unsigned long address = data[i_count + 3] | (data[i_count + 4] << 8) | (data[i_count + 5] << 16) | (data[i_count + 6] << 24);
	// char address_char[4]= {data[i_count + 3], data[i_count + 4], data[i_count + 5],data[i_count + 6]};
	// printf("%lu\n",address);
	


	int j = 9;
	char flash_data[32];

	for(j=9;j<41;j++)
	{
		flash_data[j-9] = data[j+i_count];
	}  	
	i_count = i_count + 43;

	}
	

    return 0;
}
