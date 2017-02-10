// --------------- main.c log ---------------
//
//		Date			Initials		Comments
//		----			--------		--------
//		02/09/2017		HSamra			Initial Commit
//										Added build version information to project (v1.0A.0000)
//										Added TEST_MODE macro to allow developer to enable/disable testing
//										Added string verification function in TEST_MODE area (v1.0A.0001)
//
// ------------------------------------------

#include "common.h"
#include "test_roman_numeral_calc.h"

const char filename[] = {"bld_num.txt"};
byte vrsn_mjr = 0x01;	// 1
byte vrsn_mnr = 0x00;	// 0
char vrsn_rls = 'A';	// A
char vrsn_bld[8];		// will be read from file

byte _read_buildNum(void)
{
	FILE *file = fopen(filename, "r");
	
	if(file == NULL)
	{
		printf("\r\nError: Failed to open %s\r\n", filename);
		return 0;
	}
	
	memset(vrsn_bld, 0x00, sizeof(vrsn_bld));
	
	if(!fgets(vrsn_bld, sizeof(vrsn_bld), file))
	{
		printf("\r\nError: Failed to read build number\r\n");
		return 0;
	}
	
	fclose(file);
	
	printf("\r\nRoman Numeral Calculator\r\n");
	printf("Version: v%d.%d%c.%s\r\n", vrsn_mjr, vrsn_mnr, vrsn_rls, vrsn_bld);
	
	return 1;
}

int main(void)
{
	// read build number
	if(!_read_buildNum())
	{
		return 0;
	}
	
	// initialize regex
	if(!RMN_init())
	{
		return 0;
	}
	
#ifdef TEST_MODE
	TEST_RMN_NMRL_CALC_verify();
#else
	
#endif // TEST_MODE
	
	return 0;
}