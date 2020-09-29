#include "common.hpp"

using namespace std;

int main(int argc, char** argv)
{

	if(argc < 4)
	{
		cerr << "Usage: deinject <input_file> <deinject_point> <output_file>" << endl;
		return -1;
	}

	File input;
	File output;

	input.open(argv[1], std::ios::in | std::ios::binary);
	output.open(argv[3], std::ios::out | std::ios::binary);

	const uInt deinjectPoint = atoi(argv[2]);
	const uInt inputFileSize = input.fileSize();
	const uInt outputFileSize = inputFileSize - deinjectPoint;
	const uInt CHUNK_SIZE = 52428800;

	MemoryBlock block(inputFileSize);

	cout << "Camouflage file size: " << deinjectPoint << endl;

	input.readInChunks(block.point(), CHUNK_SIZE, inputFileSize);

	output.writeInChunks(block.point(deinjectPoint), CHUNK_SIZE, outputFileSize);




	return 0;
};
