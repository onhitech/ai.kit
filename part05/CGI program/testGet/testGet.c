//=======================================
// testGet.c
//	CGI Test, by GET method
//=======================================
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	printf("Content-type: text/html\n\n");

	printf("<html>\n\n");

	printf("<head>\n");
	printf("<title>CGI Test, by GET</title>\n");
	printf("</head>\n\n");

	printf("<body>\n");
	printf("<h1>CGI Test, by GET</h1>\n");
	printf("<hr><p>\n");

	printf("Your IP Address : %s<br>\n", getenv("REMOTE_ADDR"));
	printf("QUERY_STRING : %s<br>\n", getenv("QUERY_STRING"));

	printf("</body>\n\n");
	printf("</html>\n");

	return 0;
}

