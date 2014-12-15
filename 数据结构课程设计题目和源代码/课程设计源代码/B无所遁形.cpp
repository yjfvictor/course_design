#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <cstring>

using namespace std;

class PERSON
{
public:
	PERSON()
	{
		chosen=false;
	}
	~PERSON()
	{
	}
	string id;
	string ip;
	bool chosen;
};

typedef struct
{
	char sentence[50];
	char main_ID[12];
} OUTPUT;

int compare(const void *elem1, const void *elem2)
{
	return strcmp((*(const OUTPUT *)elem1).main_ID,(*(const OUTPUT *)elem2).main_ID);
}

int main(void)
{
	int i,j,k,n;
	while(scanf("%d",&n),n)
	{
		PERSON person[20];
		OUTPUT output[10];
		for(i=0;i<n;i++)
			cin >> person[i].id >> person[i].ip ;
		k=0;
		for(i=0;i<n;i++)
		{
			if(person[i].chosen)
				continue;
			for(j=i+1;j<n;j++)
			{
				if(person[j].chosen)
					continue;
				if(person[i].ip ==person[j].ip)
				{
					person[i].chosen=person[j].chosen=true;
					sprintf(output[k].sentence,"%s is the MaJia of %s",person[j].id.c_str(),person[i].id.c_str());
					sprintf(output[k++].main_ID,person[i].id.c_str());
				}
			}
		}
		qsort(output,n/2,sizeof(output[0]),compare);
		for(i=0;i<n/2;i++)
			puts(output[i].sentence);
		putchar('\n');
	}
	return 0;
}
