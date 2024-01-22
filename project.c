#include<stdio.h>
#include<stdlib.h>
#include <windows.h>
#include <fcntl.h>
#include<time.h>


int grid[10][5];// columns // rows
int columns = 10;
int rows = 5;
int currentspot;

void creategrid()
{

	for(int i = 0; i < 10; i++)
	{

		int newr = rand() % rows ;
		printf("\n");
		for(int k = 0; k < rows; k++)
		{

			if(k == newr)
			{
				grid[i][k] = 1;
			}
			else
			{
				grid[i][k] = 0;
			}
			printf("[ ]");
		}
		

	}
	printf("\n");
	currentspot = 0;
}
int step()
{
	/*Serial port opening and alligning it's settings (this section continiues until line 73)*/
	const char *port ="\\\\.\\COM5";
    HANDLE hSerial;
    DCB dcbSerialParams={0};
    COMMTIMEOUTS timeouts = {0};

     hSerial = CreateFile(port,GENERIC_READ | GENERIC_WRITE,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);


    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(hSerial, &dcbSerialParams)) {
        fprintf(stderr, "Error setting serial port state\n");
        CloseHandle(hSerial);
        return 1;
    }

    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

     if (!SetCommTimeouts(hSerial, &timeouts)) {
        fprintf(stderr, "Error setting serial timeouts\n");
        CloseHandle(hSerial);
        return 1;
     }

	printf("please input value from 1 to 5 \n");

	DWORD bytesWritten;
        char dataone = '1';
        WriteFile(hSerial,&dataone,strlen(&dataone),&bytesWritten,NULL);

	DWORD bytesRead;
	char buffer[1];
	int inp;
	while (1){
		if (ReadFile(hSerial,buffer,sizeof(buffer),&bytesRead,NULL)){
			if(buffer[0] == '0'){
				inp = buffer[0] - '0';
				buffer[0] = '6';
				break;
			}else if(buffer[0] == '1'){
				inp = buffer[0] - '0';
				buffer[0] = '6';
				break;
			}else if(buffer[0] == '2'){
				inp = buffer[0] - '0';
				buffer[0] = '6';
				break;
			}else if(buffer[0] == '3'){
				inp = buffer[0] - '0';
				buffer[0] = '6';
				break;
			}else if(buffer[0] == '4'){
				inp = buffer[0] - '0';
				buffer[0] = '6';
				break;
			}

		}
	}
	

	if(grid[currentspot][inp] == 1)
	{
		for(int i = 0; i <= currentspot; i++)
		{
			printf("\n");

			for(int k = 0; k < rows; k++)
			{
				if(grid[i][k] == 0)
				{
					printf("[x]");
				}
				else
				{
					printf("[1]");
				}
			}
		}
		for(int i = currentspot + 1; i < columns; i++)
		{
			printf("\n");
			for(int k = 0; k < rows; k++)
			{
				printf("[ ]");
			}
		}
		currentspot++;
		printf("\nyou hit\n");
	}
	else
	{
		for(int i = 0; i < currentspot; i++)
		{
			printf("\n");
			for(int k = 0; k < rows; k++)
			{
				if(grid[i][k] == 0)
				{
					printf("[x]");
				}
				else
				{
					printf("[1]");
				}
			}
		}
		printf("\n");
		for(int k = 0; k < rows; k++)
			{
				if(k == inp)
				{
					printf("[x]");
				}
				else
				{
					printf("[ ]");
				}
			}
		for(int i = currentspot + 1; i < columns; i++)
		{
			printf("\n");
			for(int k = 0; k < rows; k++)
			{
				printf("[ ]");
			}
		}
		currentspot = 0;
		printf("\n**\n**\n**\n**\n**\n**\n");
		printf("\nyou missed start again \n");
		for(int i = 0; i < columns; i++)
		{
			printf("\n");
			for(int k = 0; k < rows; k++)
			{		
					printf("[ ]");
			}
		}
		printf("\n");

	}
	if(currentspot == columns)
	{
		CloseHandle(hSerial);
		return 1;
	}
	else
	{
		CloseHandle(hSerial);
		return 0;

	}
}

int main(){
	srand(1);
	creategrid();

	clock_t start, end;
    double time;
	start = clock();

	while(1)
	{
		if(step() == 1)
		{
			printf("congratz you won\n");
			break;
		}	
	}

	end = clock();
	time = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Time: %f seconds",time);
	return 0;
}