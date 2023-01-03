//=======================================
// ledPost.c CGI
//	LED control, by POST method
//=======================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <wiringPi.h>		////

#define P_LED	1		//// BCM_GPIO #18

typedef struct {
	char name[32];
	char val[32];
} entry;

void getToken(char *word, char *qStr, char deli);

int main(void) {
	char buf[1024];
	char *qStr;
	entry item;

	if(wiringPiSetup() == -1)		//// wiringPi pin #
		return 1;

	pinMode(P_LED, OUTPUT);			////

	printf("Content-type: text/html\n\n");

	printf("<html>\n\n");
	printf("<head>\n");
	printf("<title>LED CGI by POST...</title>\n");
	printf("</head>\n\n");
	printf("<body>\n");
	printf("<h1>LED CGI by POST...</h1>\n");
	printf("<hr><p>\n");

	printf("Your IP Address : %s<br>\n", getenv("REMOTE_ADDR"));

	memset(buf, 0x00, 1024);
	while(read(0, buf, 1024) > 0) {
		printf("POST STRING : %s<p>\n", buf);
//		memset(buf, 0x00, 1024);
	}

	qStr = buf;

	getToken(item.name, qStr, '=');
	getToken(item.val, qStr, '&');
	printf("Extracted token : %s = %s<br>", item.name, item.val);

	//// LED control....
	if(item.val[0] == '0') {
		digitalWrite(P_LED, LOW);
		printf("==> Led OFF.....<br>");
	}
	else if(item.val[0] == '1') {
		digitalWrite(P_LED, HIGH);
		printf("==> Led ON.....<br>");
	}
	else
		printf("==> Wrong data.....<br>");

	printf("</body>\n\n");
	printf("</html>\n");

	return 0;
}

// get token
void getToken(char *word, char *str, char deli) {
	int i, new_i;

	// extract token
	for(i=0; ((str[i]) && (str[i] != deli)); i++)
		word[i] = str[i];
	word[i] = '\0';

	if(str[i]) 	// skip delimiter character
		i++;

	// make a string of remaining str
	new_i = 0;
	while(str[new_i++] = str[i++])
		;
}

