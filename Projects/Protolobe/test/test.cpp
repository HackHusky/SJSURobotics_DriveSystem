#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "fff.h"
#include "Structure.h"
#include "Structure.c"
#include "Source.h"
DEFINE_FFF_GLOBALS;

int sum(int a, int b)
{
	return a + b;
}

void create_wifi_task(void)
{

}

void vTaskDelay(int a)
{

}

char sendFinal[256];
char SYSTEM_DEBUG_MSG[50]={"NONE"};

void send_data_wifi(int item_size)
{
	char buffer[10];
	char final[256];
	strcpy(final,"{");
	for(int i=0; i<item_size;i++){
	    if (i == 0)
	    {
	        sprintf(final, "{%s:%d,", send_data_label[i], send_data.data[i]);
	    }
	    else if(i!=item_size-1 && i != 0)
	    {
	        sprintf(final+strlen(final), "%s:%d,", send_data_label[i], send_data.data[i]);
	    }
	    else
	    {
	        sprintf(final+strlen(final), "%s:%d,%s:%s}", send_data_label[i], send_data.data[i],"debug",SYSTEM_DEBUG_MSG);
	    }
	}
	strncpy(sendFinal,final, sizeof(final));
}

TEST_CASE( "Testing Unittest", "[test]" )
{
	SECTION( "Summation test 0" )
	{
		  CHECK( sum(2,2) == 4 );
		REQUIRE( sum(5,5) != 15 );
	}
	SECTION( "Testing Send Data", "[send]" )
	{
		using Catch::Matchers::Equals;
		memset(sendFinal, 0, sizeof(sendFinal));
		send_data.data[send_data_name_1] = 100;
		send_data.data[send_data_name_2] = 200;
		send_data_wifi(2);
		CHECK_THAT( sendFinal, Equals("{send_data_name_1:100,send_data_name_2:200,debug:NONE}") );
		REQUIRE( sendFinal != "{send_data_name_1:10,send_data_name_2:20,debug:NONE}" );
	}
}

