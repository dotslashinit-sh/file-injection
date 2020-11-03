#ifndef COMMON_HPP_INCLUDE
#include <fstream>
#include <iostream>

typedef unsigned uInt;

class MemoryBlock
{
public:
	MemoryBlock() : blockSize(0), block(nullptr){}

	MemoryBlock(size_t i) : blockSize(i), block(nullptr)
	{
		block = new char[blockSize];
	}
	MemoryBlock(char * Block, size_t i) : blockSize(i), block(Block){}

	MemoryBlock(const MemoryBlock & mem);
	MemoryBlock(MemoryBlock && mem) noexcept;

	virtual ~MemoryBlock();

	MemoryBlock & operator=(const MemoryBlock & mem);
	MemoryBlock & operator=(MemoryBlock && mem) noexcept;

	/*Returns the size of the block.*/
	size_t size() const 
	{
		return blockSize;
	}

	/*Returns the 'i'th pointer from the starting point.*/
	char * point(size_t i = 0) const 
	{
		return block + i;
	}

	friend bool operator==(const MemoryBlock & lhs, const MemoryBlock & rhs);

	/*Create a memory block*/
	void construct(const size_t size);
private:
	size_t blockSize;
	char * block;
};

class File : public std::fstream
{
public:
	File() : size(0) {}
	File(char * fName);
	/*Constructor using a file stream.*/
	File(std::fstream & f) : size(0)
	{
		calculateSize();
	}

	/*The copy constructor nd the move constructors are deleted*
	* as they are deleted in the base class fstream.*/
	File(const File & f) = delete;
	File(File && f) = delete;
	virtual ~File()
	{
		close();
	}

	File & operator=(const File & f) = default;
	File & operator=(File && f) = default;

	/*Opens the file and then calculate its size.*/
	void open(const char * fName, char mode = std::ios::in | std::ios::out);

	/*Return the size of the file.*/
	size_t fileSize() const
	{
		return size;
	}

	/*Reads and writes the files in chunks of bytes*/
	void readInChunks(char * block, size_t chunkSize, size_t blockSizecmd);
	void writeInChunks(char * block, size_t chunkSize, size_t blockSize);

private:
	size_t size;

	 /*Calculates the size of the file*/
	void calculateSize();

	void readFile(char * block, size_t size);
	void writeFile(char * block, size_t size);

	friend class std::thread;
};

static bool operator==(const MemoryBlock & lhs, const MemoryBlock & rhs)
{
	return (lhs.block == rhs.block);
}

#endif