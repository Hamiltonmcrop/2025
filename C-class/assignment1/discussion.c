#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char  *helper(char *str, int left, int right)
{
	int len = right - left + 1;
	if (len == 0)
		return "";
	if (len == 1){
		char *rv = (char *)malloc(2);
		strncpy(rv, str + left,1);
		return rv;
}
//recursive step
//
char *first = helper(str, left,left + len/2-1);
char *second = helper(str,left+len/2,right);
char *rv = (char *)malloc(len+1);
strcpy(rv,second);
strcat(rv,first);
return rv;
}
char *unknown_operation(char *str){
	int len = strlen(str);
	return helper(str,0,len-1);
}
int main(void){
	char *out= unknown_operation("what does this function do?!!!");
	printf("%s\n",out);
	return 0;
}
