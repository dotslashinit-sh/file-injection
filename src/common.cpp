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
	uInt dataRead = 0;
	uInt dataLeft = blockSize;

	/*Check if the amount of data read is lesser than the total size*/
	while(dataRead < blockSize)
	{
		/*If the amount of data left to be read is greater than the chunk size,*
		*read the data in chunk and write it to the block just after where     *
		*the previous data was written.										  */
		if(dataLeft > chunkSize)
		{
				read(block + dataRead, dataLeft);
				/*Update the amount of data read and the amount of data left to be read.*/
				dataRead += chunkSize;
				dataLeft = blockSize - dataRead;
		}
		/*If the amount of data left is lesser than the chunk size, read the data left*
		*and break the loop.														 */
		else if(dataLeft < chunkSize)
		{
			read(block + dataRead, dataLeft);
			dataRead += dataLeft;
		}
		std::cout << dataRead << " / " << blockSize << "\r";

	}
}

void File::writeInChunks(char * block, size_t chunkSize, size_t blockSize)
{
	uInt dataWritten = 0;
	uInt dataLeft = blockSize;
	while(dataWritten < blockSize)
	{
		if(dataLeft > chunkSize)
		{
			write(block + dataWritten, chunkSize);
			dataWritten += chunkSize;
			dataLeft = blockSize - dataWritten;
		}
		if(dataLeft < chunkSize)
		{
			write(block + dataWritten, dataLeft);
			dataWritten += dataLeft;
			dataLeft = blockSize - dataWritten;
			break;
		}
		std::cout << dataWritten << " / " << blockSize << "\r";

	}
}
