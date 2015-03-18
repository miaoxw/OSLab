#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdio.h>
#include <windows.h>

int isEmpty(char *,int) __attribute__((cdecl));

FILE *fin;
int *FAT;
struct attr
{
	int bytesPerSector;
	int sectorPerCluster;
	int reservedSectorCount;
	int FATCount;
	int rootEntryCount;
	int totalSector;
	int FATSize;
}attributes;
int rootEntryOffset;
int dataOffset;
HANDLE hstdout;

struct attr getAttributes(FILE *file)
{
	struct attr ret;
	unsigned char buffer[512];
	fread(buffer,1,512,file);
	ret.bytesPerSector=((unsigned int)buffer[12]<<8)+(unsigned int)buffer[11];
	ret.sectorPerCluster=(unsigned int)buffer[13];
	ret.reservedSectorCount=(unsigned int)buffer[14];
	ret.FATCount=(unsigned int)buffer[16];
	ret.rootEntryCount=((unsigned int)buffer[18]<<8)+(unsigned int)buffer[17];
	ret.totalSector=((unsigned int)buffer[20]<<8)+(unsigned int)buffer[19];
	ret.FATSize=((unsigned int)buffer[23]<<8)+(unsigned int)buffer[22];
	return ret;
}

int* getFAT(FILE *file)
{
	int FATBytesCount=attributes.bytesPerSector*attributes.FATSize;
	fseek(file,attributes.bytesPerSector*attributes.reservedSectorCount,0);
	int *ret=(int*)malloc(FATBytesCount*2/3*sizeof(int));
	unsigned char buffer[FATBytesCount];
	fread(buffer,1,FATBytesCount,file);
	
	int i;
	for(i=0;i*3<FATBytesCount;i++)
	{
		unsigned char ch1=buffer[3*i];
		unsigned char ch2=buffer[3*i+1];
		unsigned char ch3=buffer[3*i+2];
		ret[2*i]=((ch2&0xF)<<8)+ch1;
		ret[2*i+1]=(ch3<<4)+((ch2&0xF0)>>4);
	}
	
	rootEntryOffset=0x2600;
	dataOffset=rootEntryOffset+attributes.rootEntryCount*32;
	return ret;
}

void retriveData(FILE *file,int firstClust,const char *path)
{
	int count=0;
	//当前目录下项目数量 
	char newPath[256];
	memset(newPath,0,sizeof(newPath));
	strcpy(newPath,path);
	strcat(newPath,"\\");
	
	int clust=firstClust;
	fpos_t currentPos;
	do
	{
		fseek(file,dataOffset+(clust-2)*512,0);
		fgetpos(file,&currentPos);
		unsigned char buffer[32];
		int i;
		for(i=1;i<=8;i++)
		{
			fsetpos(file,&currentPos);
			memset(buffer,0,sizeof(buffer));
			fread(buffer,1,32,file);
			fgetpos(file,&currentPos);
			
			if(isEmpty(buffer,32))
				continue;
			
			//获取文件名 
			char filename[16];
			memset(filename,0,sizeof(filename));
			int j;
			for(j=0;j<8;j++)
				if(buffer[j]!=' ')
					filename[j]=buffer[j];
				else
					break;
			//获取扩展名
			char  extend[4];
			memset(extend,0,sizeof(extend));
			for(j=8;j<11;j++)
				if(buffer[j]!=' ')
					extend[j-8]=buffer[j];
				else
					break;
			//扩展名存在时拼接 
			if(strcmp(extend,"")!=0)
			{
				strcat(filename,".");
				strcat(filename,extend);
			}
			
			int childClust;
			switch(buffer[0xB])
			{
				case 0x10://是目录 
					if(strcmp(filename,".")!=0&&strcmp(filename,"..")!=0)
					//DOS下的当前目录和上级目录忽略 
					{
						count++;
						childClust=(buffer[0x1B]<<8)+buffer[0x1A];
						char newerPath[256];
						strcpy(newerPath,newPath);
						strcat(newerPath,filename);
						retriveData(file,childClust,newerPath);
						//printf("into %s...\n",newPath);
						//system("pause");
					}
					break;
				case 0xF://长文件名，直接忽略
				case 0x8://卷标，直接忽略 
					break;
				case 0x0://以下均为8.3文件名下的合理情况 
				case 0x1:
				case 0x2:
				case 0x3:
				case 0x4:
				case 0x5:
				case 0x6:
				case 0x7:
				case 0x9:
				default:
					//printFile(filename,strlen(filename));
					count++;
					SetConsoleTextAttribute(hstdout,12);
					printf("%s",newPath);
					SetConsoleTextAttribute(hstdout,7);
					printf("%s\n",filename);
					break;
			}
		}
		clust=FAT[clust];
	}
	while(clust<0xFF7);//坏簇也直接结束 
	if(count==0)
	{
		SetConsoleTextAttribute(hstdout,12);
		printf("%s\n",newPath);
	}
}

void retriveRoot(FILE *file)
{
	int i;
	for(i=rootEntryOffset;i<dataOffset;i+=32)
	{
		unsigned char buffer[32];
		fseek(file,i,0);
		fread(buffer,1,32,file);
		
		//没有数据时结束 
		if(isEmpty(buffer,32))
			continue;
		
		//获取文件名 
		char filename[16];
		memset(filename,0,sizeof(filename));
		int j;
		for(j=0;j<8;j++)
			if(buffer[j]!=' ')
				filename[j]=buffer[j];
			else
				break;
		//获取扩展名
		char  extend[4];
		memset(extend,0,sizeof(extend));
		for(j=8;j<11;j++)
			if(buffer[j]!=' ')
				extend[j-8]=buffer[j];
			else
				break;
		//扩展名存在时拼接 
		if(strcmp(extend,"")!=0)
		{
			strcat(filename,".");
			strcat(filename,extend);
		}
		
		int firstClust;
		switch(buffer[0xB])
		{
			case 0x10://是目录 
				firstClust=(buffer[0x1B]<<8)+buffer[0x1A];
				//printf("into %s...\n",filename);
				//system("pause");
				retriveData(file,firstClust,filename);
				break;
			case 0x0://以下均为8.3文件名下的合理情况 
			case 0x1:
			case 0x2:
			case 0x3:
			case 0x4:
			case 0x5:
			case 0x6:
			case 0x7:
			default:
				//printFile(filename,strlen(filename));
				SetConsoleTextAttribute(hstdout,7);
				printf("%s\n",filename);
				break;
			case 0xF://长文件名，直接忽略
			case 0x8://卷标，直接忽略 
				break; 
				
		}
	}
}

int main()
{
	hstdout=GetStdHandle(STD_OUTPUT_HANDLE);
	fin=fopen("a.img","rb");
	attributes=getAttributes(fin);
	FAT=getFAT(fin);	
	retriveRoot(fin);
	SetConsoleTextAttribute(hstdout,7);
	system("pause");
	fclose(fin);
	return 0;
}

