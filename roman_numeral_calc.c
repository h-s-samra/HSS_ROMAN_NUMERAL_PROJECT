// --------------- roman_numeral_calc.c log ---------------
//
//		Date			Initials		Comments
//		----			--------		--------
//		02/09/2017		HSamra			Initial Commit
//										Started to add the string verification functionality (v1.0A.0001)
//										Made progress with string verification functionality (v1.0A.0045)
//										Need to add one more test to string verification functionality once string encoding functionality is complete
//										Started to add the string encoding functionality (i to str) (v1.0A.0045)
//										Finished adding the string encoding functionality (i to str) (v1.0A.0067)
//
// --------------------------------------------------------

#include <regex.h>
#include "common.h"

char rgx_str[] = {"^((m*)((cm?)|((cd?)|(d?)(c{0,3})))((xc?)|((xl?)|(l?)(x{0,3})))((ix?)|((iv?)|(v?)(i{0,3}))))$"};

regex_t regex;
byte rgxSts = 0;

int RMN_NMRL_CALC_init(void)
{
	// compile regex
	if(regcomp(&regex, rgx_str, REG_EXTENDED | REG_ICASE) != 0) // using extended regular expressions and ignoring case
	{
		printf("Error: Could not compile regex\r\n");
		return 0;
	}
	return 1;
}

int RMN_NMRL_CALC_verify_string(char *str)
{
	byte rgxSts = 0;
	
	rgxSts = regexec(&regex, str, 0, NULL, 0);
	
	if(!rgxSts)
	{
		return 1; // if match
	}
	else if(rgxSts == REG_NOMATCH)
	{
#ifndef TEST_MODE
		printf("Error: Regex no match\r\n");
#endif // TEST_MODE
		return 0; // if no match
	}
	else
	{
		// other errors
		char rgxErr[16];
		memset(rgxErr, 0x00, sizeof(rgxErr));
		regerror(rgxSts, &regex, rgxErr, sizeof(rgxErr));
		printf("Error: Regex (%s)\r\n", rgxErr);
	}
	return 0;	
}

void RMN_NMRL_CALC_encode_int(int n, char *str)
{
	while(n > 0)
	{
		if(n >= 1000)
		{
			strcat(str, "M");
			n -= 1000;
		}
		else if(n < 1000 && n >= 900)
		{
			strcat(str, "CM");
			n -= 900;
		}
		else if(n < 900 && n >= 500)
		{
			strcat(str, "D");
			n -= 500;
		}
		else if(n < 500 && n >= 400)
		{
			strcat(str, "CD");
			n -= 400;
		}			
		else if(n < 400 && n >= 100)
		{
			strcat(str, "C");
			n -= 100;
		}
		else if(n < 100 && n >= 90)
		{
			strcat(str, "XC");
			n -= 90;
		}
		else if(n < 90 && n >= 50)
		{
			strcat(str, "L");
			n -= 50;
		}
		else if(n < 50 && n >= 40)
		{
			strcat(str, "XL");
			n -= 40;
		}
		else if(n >= 10)
		{
			strcat(str, "X");
			n -= 10;
		}
		else if(n == 9)
		{
			strcat(str, "IX");
			n -= 9;
		}
		else if(n < 9 && n >= 5)
		{
			strcat(str, "V");
			n -= 5;
		}
		else if(n == 4)
		{
			strcat(str, "IV");
			n -= 4;
		}
		else if(n <= 3)
		{
			strcat(str, "I");
			n -= 1;
		}
		else
		{
			printf("\r\n<Error: RMN_NMRL_CALC_encode_int>\r\n");
			return;
		}
	}
}