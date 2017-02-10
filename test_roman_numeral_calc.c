// --------------- test_roman_numeral_calc.c log ---------------
//
//		Date			Initials		Comments
//		----			--------		--------
//		02/09/2017		HSamra			Initial Commit
//										Added tests for string verification usign Regex (v1.0A.0045)
//										One more test needs to be added as soon as string encoding functionality is complete
//
// -------------------------------------------------------------

#include <assert.h>
#include "common.h"

#define FAIL 0
#define PASS 1

void _regex_verify_str(char *str, byte result)
{
	printf("regex_verify_str(%s): ", str);
	
	assert(RMN_NMRL_CALC_verify_string(str) == result);
	
	printf("PASS\r\n");
}

void TEST_RMN_NMRL_CALC_verify(void)
{
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
	
}