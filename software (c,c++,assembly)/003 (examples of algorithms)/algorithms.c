#include <stdint.h>

// <stdint.h>
// only for Little Endian
void sort_unsigned_array(void* data,size_t size_of_data,size_t size_of_element)
{
	if(size_of_data<1 || size_of_element<1 || size_of_data%size_of_element!=0 || size_of_data<size_of_element) return;
	uint32_t size0 = (uint32_t)size_of_element/4 ? (uint32_t)size_of_element/4 : 1;
	int32_t result0[size0];
	int32_t result1[size0];
	size_t j = 0;
	size_t k = 0;
	int32_t bool0 = 0;
	for(size_t i = 0; i<size_of_data-size_of_element; i+=size_of_element)
	{
		for(j = 0; j<size_of_element; j++) *((uint8_t*)result1+j) = *((uint8_t*)data+i+j);
		for(k = i; k<size_of_data; k+=size_of_element)
		{
			for(j = 0; j<size_of_element; j++) *((uint8_t*)result0+j) = *((uint8_t*)data+k+j);
			for(j = size_of_element-1; j!=-1; j--)
			{
				if(*((uint8_t*)result0+j)!=*((uint8_t*)result1+j))
				{
					if(*((uint8_t*)result0+j)<*((uint8_t*)result1+j)) {bool0 = 1; break;}
					else break;
				}
			}
			if(bool0)
			{
				for(j = 0; j<size_of_element; j++)
				{
					*((uint8_t*)data+k+j) = *((uint8_t*)result1+j);
					*((uint8_t*)data+i+j) = *((uint8_t*)result0+j);
					*((uint8_t*)result1+j) = *((uint8_t*)data+i+j);
				}
			}
			j = 0;
			bool0 = 0;
		}	
	}
	return;
}

void uint32_to_string(unsigned int data_in,char* const data_out)
{
	char data_rev[10];
	for(int i = 0;; i++)
	{
		if(data_in < 10)
		{
			data_rev[i] = data_in+48;
			data_out[i+1] = '\0';
			for(int j = 0; j!=i+1; j++) data_out[j] = data_rev[i-j];
			return;
		}
		data_rev[i] = (data_in%10)+48;
		data_in = (data_in-(data_in%10))/10;
	}
}
