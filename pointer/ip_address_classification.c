/*
An IPv4 has 4 octets having decimal value between 0 to 255 and depending on
the first octet’s value, IP Addresses divided into 5 classes:
Class A		  1 	to 	126
Class B		128 	to 	191
Class C		192	  to 	223
Class D		224	  to	239
Class E		240	  to 	254
In this program, we will read an IP Address and find its class.
*/

#include <stdio.h>
#include <string.h>

/*
Function : extractIpAddress
Arguments :
1) sourceString - String pointer that contains ip address
2) ipAddress - Target variable short type array pointer that will store ip
address octets
*/
void ExtractIpAddress(unsigned char *SourceString, short *ipAddress)
{
    unsigned short StringLength = 0;
    unsigned char  oct[4] = {0};
    unsigned char  buf_cnt = 0;
    unsigned char  oct_cnt = 0;
    unsigned char  i;
    unsigned char  buf[5];       // xxx.\0

    StringLength = strlen(SourceString);
    for(i=0; i<StringLength; i++)
    {
        if(SourceString[i] != '.')
        {
            buf[buf_cnt++] = SourceString[i];
        }
        if(SourceString[i] == '.' || i == StringLength-1){
            buf[buf_cnt] = '\0';  // add string termination at the end
            buf_cnt = 0;
            oct[oct_cnt++] = atoi(buf);  // Convert buf to integer
        }
    }
    ipAddress[0] = oct[0];
    ipAddress[1] = oct[1];
    ipAddress[2] = oct[2];
    ipAddress[3] = oct[3];
}

int main()
{
    unsigned char ip[20] = {0};
    short ipAddress[4];

    printf("Enter IP Address (xxx.xxx.xxx.xxx format): ");
    scanf("%s", ip);

    ExtractIpAddress(ip, ipAddress);

    printf("\nIp Address: %03d. %03d. %03d. %03d\n",ipAddress[0],ipAddress[1],ipAddress[2],ipAddress[3]);

    if(ipAddress[0] >= 0 && ipAddress[0] <= 127)
        printf("Class A Ip Address.\n");
    if(ipAddress[0] > 127 && ipAddress[0] < 191)
        printf("Class B Ip Address.\n");
    if(ipAddress[0] > 191 && ipAddress[0] < 224)
        printf("Class C Ip Address.\n");
    if(ipAddress[0] > 224 && ipAddress[0] <= 239)
        printf("Class D Ip Address.\n");
    if(ipAddress[0] > 239)
        printf("Class E Ip Address.\n");

    return 0;
}
