#include "common.hpp"

MemoryBlock::MemoryBlock(const MemoryBlock & mem) : blockSize(mem.blockSize), block(nullptr)
{

		for(size_t i = 0; i < blockSize; i++)
			block[i] = mem.block[i];
}

MemoryBlock::MemoryBlock(MemoryBlock && mem) noexcept : blockSize(mem.blockSize), block(nullptr)
{

	mem.~MemoryBlock();
}

MemoryBlock::~MemoryBlock()
{

	delete[] block;
}

MemoryBlock & MemoryBlock::operator=(const MemoryBlock & mem)
{
	if(this != &mem)
	{
		blockSize = mem.blockSize;
		delete [] block;
		block = new char[blockSize];
		for(size_t i = 0; i < blockSize; i++)
			block[i] = mem.block[i];

		return *this;
	}
	else
		throw std::runtime_error("ERROR: Called operator=(const MemoryBlock &) on the same object!");
}

MemoryBlock & MemoryBlock::operator=(MemoryBlock && mem) noexcept
{
	blockSize = mem.blockSize; //Copy the block size
	delete [] block; /*Delete the calling object's block...*/
	block = new char[blockSize];/*...and create a new block*/
	for(size_t i = 0; i < blockSize; i++)
		block[i] = mem.block[i];//Copy the data from the other block

	return *this;
}

void MemoryBlock::construct(const size_t size)
{
	if(block != nullptr)
		delete[] block;
	block = new char[size];
}

File::File(char * fName) : size(0)
{
	open(fName);
	calculateSize();
}

void File::open(const char * fName, char mode)
{
	std::fstream::open(fName, mode);
	calculateSize();
}

void File::calculateSize()
{
	size_t curPos = tellg(); //Save the current position of the stream.
	seekg(0, std::ios::end);
	size = tellg();	//Get the file size.
	seekg(curPos);
}

void File::readFile(char * block, size_t size)
{
	read(block, size);
}

void File::writeFile(char * block, size_t size)
{
	read(block, size);
}

void File::readInChunks(char * block, size_t chunkSize, size_t blockSize)
{
	int dataread = 0, dataleft = blockSize;

	while(dataleft > 0)
	{
		std::cout << dataleft << std::endl;
		if(dataleft < chunkSize)
		{
			read(block + dataread, dataleft);
			break;
		}

		read(block + dataread, chunkSize);
		dataread += chunkSize;
		dataleft -= chunkSize;
	}
	
	return;
}

void File::writeInChunks(char * block, size_t chunkSize, size_t blockSize)
{
	int datawritten = 0, dataleft = blockSize;

	while(dataleft > 0)
	{
		std::cout << dataleft << std::endl;
		if(dataleft < chunkSize)
		{
			write(block + datawritten, dataleft);
			break;
		}

		write(block + datawritten, chunkSize);
		datawritten += chunkSize;
		dataleft -= chunkSize;
	}

	return;
}
