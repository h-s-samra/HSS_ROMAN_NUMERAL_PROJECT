// --------------- test_roman_numeral_calc.c log ---------------
//
//		Date			Initials		Comments
//		----			--------		--------
//		02/09/2017		HSamra			Initial Commit
//										Added tests for string verification usign Regex (v1.0A.0045)
//										One more test needs to be added as soon as string encoding functionality is complete
//										Added tests for string encoding functionality (i to str) (v1.0A.0067)
//										Added test for comparing file with written roman numerals to master file with roman numeral to verify correct encoding
//
// -------------------------------------------------------------

#include <assert.h>
#include "common.h"

#define FAIL 0
#define PASS 1

#ifdef TEST_MODE

const char testFile[] = "temp_test.txt";
const char chckFile[] = "roman_numeral_test.txt";	
char bfr[8];

void _bfr_init(char *bfr)
{
	memset(bfr, 0x00, sizeof(bfr));
}

// Start verification tests

void _regex_verify_str(char *str, byte result)
{
	printf("regex_verify_str(%s): ", str);
	
	assert(RMN_NMRL_CALC_verify_string(str) == result);
	
	printf("PASS\r\n");
}

void _regex_verify_str_int(int n, char *str)
{
	printf("regex_verify_str_int(%d -> %s): ", n, str);
	
	assert(RMN_NMRL_CALC_verify_string(str) == 1);
	
	printf("PASS\r\n");
}
	
void _regex_verify_file(void)
{
	FILE *f1 = fopen(testFile, "r");
	FILE *f2 = fopen(chckFile, "r");
	int fCheck1 = getc(f1); // testFile
	int fCheck2 = getc(f2); // chckFile
	
	printf("regex_verify_file(%d - %d): ", fCheck1, fCheck2);
	
	while((fCheck1 != EOF) && (fCheck2 != EOF) && (fCheck1 == fCheck2))
	{
		fCheck1 = getc(f1);
		fCheck2 = getc(f2);
	}
	printf("(%d --- %d)", fCheck1, fCheck2); // HSS_Debug
	
	assert(fCheck1 == fCheck2);
	
	printf("PASS\r\n");
}

void TEST_RMN_NMRL_CALC_verify(void)
{
	FILE *file1;
	FILE *file2;					 
	int i = 0;
	
	// test edge conditions for each possible character (i, v, x, l, c, d, m)
	_regex_verify_str("i", PASS);
	_regex_verify_str("iii", PASS);
	_regex_verify_str("iiii", FAIL); // expect fail
	
	_regex_verify_str("v", PASS);
	_regex_verify_str("vv", FAIL); // expect fail
	
	_regex_verify_str("x", PASS);
	_regex_verify_str("xxx", PASS);
	_regex_verify_str("xxxx", FAIL); // expect fail
	
	_regex_verify_str("l", PASS);
	_regex_verify_str("ll", FAIL); // expect fail
	
	_regex_verify_str("c", PASS);
	_regex_verify_str("ccc", PASS);
	_regex_verify_str("cccc", FAIL); // expect fail
	
	_regex_verify_str("d", PASS);
	_regex_verify_str("dd", FAIL); // expect fail
	
	_regex_verify_str("m", PASS);
	_regex_verify_str("mmmm", PASS); // expect pass because there can be many 'm'
	
	// test edge conditions for first stage of character combinations (vi, xv, lx, cl, dc, md)
	_regex_verify_str("vi", PASS);
	_regex_verify_str("viii", PASS);
	_regex_verify_str("viiii", FAIL); // expect fail
	_regex_verify_str("vvi", FAIL); // expect fail
	
	_regex_verify_str("xv", PASS);
	_regex_verify_str("xxxv", PASS);
	_regex_verify_str("xvv", FAIL); // expect fail
	_regex_verify_str("xxxxv", FAIL); // expect fail
	
	_regex_verify_str("lx", PASS);
	_regex_verify_str("lxxx", PASS);
	_regex_verify_str("lxxxx", FAIL); // expect fail
	_regex_verify_str("llx", FAIL); // expect fail
	
	_regex_verify_str("cl", PASS);
	_regex_verify_str("cccl", PASS);
	_regex_verify_str("cll", FAIL); // expect fail
	_regex_verify_str("ccccl", FAIL); // expect fail
	
	_regex_verify_str("dc", PASS);
	_regex_verify_str("dccc", PASS);
	_regex_verify_str("dcccc", FAIL); // expect fail
	_regex_verify_str("ddc", FAIL); // expect fail
	
	_regex_verify_str("md", PASS);
	_regex_verify_str("mmmmd", PASS);
	_regex_verify_str("mdd", FAIL); // expect fail
	
	// test edge conditions for subtractive forms and combinations (iv, ix, xl, xc, cd, cm)
	_regex_verify_str("iv", PASS);
	_regex_verify_str("ivi", FAIL); // expect fail);
	_regex_verify_str("ivv", FAIL); // expect fail);
	_regex_verify_str("viv", FAIL); // expect fail);
	
	_regex_verify_str("ix", PASS);
	_regex_verify_str("xix", PASS);
	_regex_verify_str("ixi", FAIL); // expect fail
	_regex_verify_str("ixiv", FAIL); // expect fail
	_regex_verify_str("ixv", FAIL); // expect fail
	
	_regex_verify_str("xl", PASS);
	_regex_verify_str("xli", PASS);
	_regex_verify_str("xlix", PASS);
	_regex_verify_str("cxl", PASS);
	_regex_verify_str("xlx", FAIL); // expect fail
	_regex_verify_str("xll", FAIL); // expect fail
	
	_regex_verify_str("xc", PASS);
	_regex_verify_str("cxc", PASS);
	_regex_verify_str("xcix", PASS);
	_regex_verify_str("xcvi", PASS);
	_regex_verify_str("xciv", PASS);
	_regex_verify_str("xcx", FAIL); // expect fail
	_regex_verify_str("xcxl", FAIL); // expect fail
	_regex_verify_str("xcl", FAIL); // expect fail
	
	_regex_verify_str("cd", PASS);
	_regex_verify_str("cdxl", PASS);
	_regex_verify_str("cdxc", PASS);
	_regex_verify_str("cdi", PASS);
	_regex_verify_str("cdv", PASS);
	_regex_verify_str("cdx", PASS);
	_regex_verify_str("cdc", FAIL); // expect fail
	_regex_verify_str("dcd", FAIL); // expect fail
	
	_regex_verify_str("cm", PASS);
	_regex_verify_str("cmi", PASS);
	_regex_verify_str("cmxc", PASS);
	_regex_verify_str("cmxl", PASS);
	_regex_verify_str("mcm", PASS);
	_regex_verify_str("cmlxvi", PASS);
	_regex_verify_str("cmc", FAIL); // expect fail
	_regex_verify_str("cmd", FAIL); // expect fail
	_regex_verify_str("cmcd", FAIL); // expect fail
	
	// test generated roman numeral strings that are written to a file with a master file to verify
	file1 = fopen(testFile, "a");
	file2 = fopen(chckFile, "r");
							 
	if(file1 == NULL)
	{
		printf("\r\nError: Failed to create %s", testFile);
	}
	else if(file2 == NULL)
	{
		printf("\r\nError: Failed to create %s", chckFile);
	}
	
	for(i = 1; i <= 1000; i++)
	{
		char bfr[16];
		char bfr2[16];
		
		_bfr_init(bfr);
		_bfr_init(bfr2);
			
		RMN_NMRL_CALC_encode_int(i, bfr);
		
		_regex_verify_str_int(i, bfr);
		
		sprintf(bfr2, "%d=%s\n", i, bfr);
		fputs(bfr2, file1);
	}

	fclose(file1);
	fclose(file2);
	
	_regex_verify_file();
							 
	if(remove(testFile) == 0)
	{
		printf("\r\n%s deleted\r\n", testFile);
	}
}

// End verification tests

// Start encoding tests

void _encode_int_to_str(int n, char *str)
{
	_bfr_init(bfr);
	
	printf("encode_int_to_str(%d->%s): ", n, str);
	
	RMN_NMRL_CALC_encode_int(n, bfr);
	
	assert(strcmp(bfr, str) == 0); // verify we get what we expected
	
	assert(RMN_NMRL_CALC_verify_string(bfr) == 1); // verify our string verification works
	
	printf("PASS\r\n");
}

void TEST_RMN_NMRL_CALC_encode(void)
{
	_encode_int_to_str(1, "I");
	_encode_int_to_str(3, "III");

	_encode_int_to_str(4, "IV");
	_encode_int_to_str(5, "V");
	_encode_int_to_str(8, "VIII");
	
	_encode_int_to_str(9, "IX");
	_encode_int_to_str(10, "X");
	_encode_int_to_str(39, "XXXIX");

	_encode_int_to_str(40, "XL");
	_encode_int_to_str(49, "XLIX");
	
	_encode_int_to_str(50, "L");
	_encode_int_to_str(89, "LXXXIX");
	
	_encode_int_to_str(90, "XC");
	_encode_int_to_str(99, "XCIX");
	
	_encode_int_to_str(100, "C");
	_encode_int_to_str(399, "CCCXCIX");
	
	_encode_int_to_str(400, "CD");
	_encode_int_to_str(499, "CDXCIX");
	
	_encode_int_to_str(500, "D");
	_encode_int_to_str(899, "DCCCXCIX");
	
	_encode_int_to_str(900, "CM");
	_encode_int_to_str(999, "CMXCIX");
	
	_encode_int_to_str(1000, "M");
	_encode_int_to_str(1999, "MCMXCIX");
}

// End encoding tests

#endif // TEST_MODE
