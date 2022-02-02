#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include "WAVData.h"

using namespace std;

void * operator new(size_t size)
{
    std::cout << "Allocated:  " << size << '\n';
    void * p = malloc(size);
    return p;
}
 
void operator delete(void * p)
{
    std::cout << "Freed: " << sizeof(p) << '\n';
    free(p);
}


int main()
{
	std::ofstream audioFile;
	
	wav::WAVData wa;
	wa.ParseFile("bing.wav");

	std::cout << wa.GetNumberOfSamples();

	int32_t* waSamples = wa.GetSamples();
	std::string idk = "";

	int on = 0, off = 0;

	for(int i=0; i<wa.GetNumberOfSamples();i += 1000){
		
		if(*(waSamples + i) != 0)
		{
			if(off > 35)
				idk += "  ";
			else if(off > 25)
				idk += " "; 
			on++;
			off = 0;
		}
				
		else
		{
			if(on > 0 && on < 10)
				idk += ".";
			else if(on > 10)
				idk += "-";

			off++;
			on = 0;
		}
			
	}

	std::cout << idk;
	
	audioFile.close();
	delete waSamples;
	wa.ClearData();
	
	return 0;
}