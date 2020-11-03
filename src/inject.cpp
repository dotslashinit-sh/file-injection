#include "common.hpp"

using namespace std;

int main(int argc, char ** argv)
{
	//Check if there are necessary arguments
	if(argc < 2)
	{
		cout << "Usage: inject <camouflage> <adrenalin> <output>" << endl;
		return 1; 
	}
	else if(argc < 4)
	{
		cout << "ERROR: Argument count too few!" << endl;
	}

	/*File handlers*/
	File camouflage;
	File adrenalin;
	File output;

	const uInt CHUNK_SIZE = 52428800;

	/*Open the file for input in binary mode*/
	camouflage.open(argv[1], std::ios::in | std::ios::binary);
	adrenalin.open(argv[2], std::ios::in | std::ios::binary);
	output.open(argv[3], std::ios::out | std::ios::binary);

	const uInt camSize = camouflage.fileSize();
	const uInt adrSize = adrenalin.fileSize();
	const uInt outSize = camSize + adrSize;//Output size is the sum of adrenlin size and camouflage size.

	/*Memory block*/
	MemoryBlock mblock(outSize);

	auto start = mblock.point();

	/*Read the data from the stream*/
	camouflage.readInChunks(start, CHUNK_SIZE, camSize);
	cout << "Camouflage file size: " << camSize << " " << adrSize << endl;
	adrenalin.readInChunks(start + camSize, CHUNK_SIZE, adrSize);

	output.writeInChunks(start, CHUNK_SIZE, outSize);

	return 0;
}
