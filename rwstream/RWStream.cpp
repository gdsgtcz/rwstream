//
//  RWStream.cpp
//  RWStream
//
//  Created by 袁笠凯 on 15/9/7.
//  Copyright (c) 2015年 袁笠凯. All rights reserved.
//

#include "RWStream.h"

//缓冲区capacity必须开 2的幂次方

RWStream::RWStream(uint32_t capacity, endian ed)
:read_index_(0),
write_index_(0),
size_(0),
capacity_(capacity),
endian_(ed)
{
	buffer_ = new uint8_t[capacity];
}

RWStream::~RWStream()
{
	delete[] buffer_;
}

uint32_t RWStream::readAll(uint8_t *data)
{

	if (write_index_ > read_index_) {
		uint32_t len = write_index_ - read_index_;
		memcpy(data, buffer_ + read_index_, len);
		return len;
	}
	else{
		uint32_t len1 = capacity_ - read_index_;
		uint32_t len2 = write_index_;
		memcpy(data, buffer_ + read_index_, len1);
		memcpy(data + len1, buffer_, len2);
		return len1 + len2;
	}
}

uint32_t RWStream::read(uint8_t* data, uint32_t bytes)
{
	if (0 == bytes) {
		return 0;
	}
	uint32_t capacity = capacity_;
	if (bytes <= read_available_space()){
		if (write_index_ > read_index_ || bytes <= capacity - read_index_) {
			memcpy(data, buffer_ + read_index_, bytes);
			read_index_ += bytes;
			read_index_ &= capacity - 1;
			return bytes;
		}
		else{
			memcpy(data, buffer_ + read_index_, capacity - read_index_);
			memcpy(data + capacity - read_index_, buffer_, bytes - capacity + read_index_);
			read_index_ = (read_index_ + bytes) % capacity;
		}
		return bytes;
	}
	else{
		return 0;
	}
}

uint32_t RWStream::write(const uint8_t *data, uint32_t bytes)
{
	if (0 == bytes) {
		return 0;
	}

	uint32_t capacity = capacity_;
	if (bytes <= write_available_space()){
		if (read_index_ > write_index_ || bytes <= capacity - write_index_) {
			memcpy(buffer_ + write_index_, data, bytes);
			write_index_ += bytes;
			write_index_ &= capacity - 1;
			return bytes;
		}
		else{
			uint32_t length1 = capacity - write_index_;
			memcpy(buffer_ + write_index_, data, length1);
			memcpy(buffer_, data + length1, bytes - length1);
			write_index_ = (write_index_ + bytes) % capacity;
			return bytes;
		}
	}
	else{
		return 0;
	}
}

void RWStream::reset()
{
	read_index_ = 0;
	write_index_ = 0;
	memset(buffer_, 0, capacity_);
}

uint8_t* RWStream::init(uint32_t capacity)
{
	read_index_ = 0;
	write_index_ = 0;
	delete[] buffer_;
	buffer_ = nullptr;
	buffer_ = new uint8_t[capacity];
	return buffer_;
}

uint32_t RWStream::getPos()
{
	return read_index_;
}

void RWStream::setPos(int32_t pos)
{
	if (pos < 0)
	{
		read_index_ += pos;
		if (read_index_ < 0) {
			read_index_ += capacity_;
		}
		return;
	}
	if (write_index_ > read_index_)
	{
		uint32_t pos_index = (read_index_ + pos) % capacity_;
		if (pos_index > write_index_)
		{
			read_index_ = write_index_;
		}
		else
		{
			read_index_ = pos_index;
		}
	}
}

uint32_t RWStream::read_available_space()
{
	return write_index_ >= read_index_ ? write_index_ - read_index_ : write_index_ + capacity_ - read_index_;
}

uint32_t RWStream::write_available_space()
{
	return write_index_ >= read_index_ ? capacity_ - write_index_ + read_index_ : read_index_ - write_index_;
}

uint8_t RWStream::readUint8(){
	memset(uint8_buffer_, 0, 1);
	if (!read(uint8_buffer_, 1))
	{
		return -1;
	}
	return uint8_buffer_[0];
}

uint16_t RWStream::readUint16(){
	memset(uint16_buffer_, 0, 2);
	if (!read(uint16_buffer_, 2))
	{
		return -1;
	}
	return getUint16(uint16_buffer_);
}

uint32_t RWStream::readUint32(){
	memset(uint32_buffer_, 0, 4);
	if (!read(uint32_buffer_, 4))
	{
		return -1;
	}
	return getUint32(uint32_buffer_);
}

uint64_t RWStream::readUint64(){
	memset(uint64_buffer_, 0, 8);
	if (!read(uint64_buffer_, 8))
	{
		return -1;
	}
	return getUint64(uint64_buffer_);
}

uint32_t RWStream::writeUint8(uint8_t data){
	uint8_wbuffer_[0] = data;
	return write(uint8_wbuffer_, 1);
}

uint32_t RWStream::writeUint16(uint16_t data){
	return write(setUint16(data), 2);
}

uint32_t RWStream::writeUint32(uint32_t data){
	return write(setUint32(data), 4);
}

uint32_t RWStream::writeUint64(uint64_t data){
	return  write(setUint64(data), 8);
}

uint32_t RWStream::writeString32(std::string s){
	uint32_t len = (uint32_t)(s.size());
	writeUint32(len);
	return write(reinterpret_cast<const uint8_t*>(s.c_str()), len) + 4 ;
}

std::string RWStream::readString32()
{
	uint32_t length = readUint32();
	printf("String32 length :: %d\n", length);
	std::string s("", length);
	read(reinterpret_cast<uint8_t*>(const_cast<char *>(s.c_str())), length);
	return s;
}


