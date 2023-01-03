//=======================================
// testPost.c
//	CGI Test, by POST method
//=======================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
	char buf[1024];

	printf("Content-type: text/html\n\n");

	printf("<html>\n\n");

	printf("<head>\n");
	printf("<title>CGI Test, by POST</title>\n");
	printf("</head>\n\n");

	printf("<body>\n");
	printf("<h1>CGI Test, by POST</h1>\n");
	printf("<hr><p>\n");

	printf("Your IP Address : %s<br>\n", getenv("REMOTE_ADDR"));

	memset(buf, 0x00, 1024);
	while(read(0, buf, 1024) > 0) {
		printf("POST STRING : %s<p>\n", buf);
	}

	printf("</body>\n\n");

	printf("</html>\n");

	return 0;
}

