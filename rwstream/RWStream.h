//
//  RWStream.h
//  RWStream
//
//  Created by 袁笠凯 on 15/9/7.
//  Copyright (c) 2015年 袁笠凯. All rights reserved.
//

#ifndef __RWStream__RWStream__
#define __RWStream__RWStream__
#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <memory.h>
enum endian{
	big_endian = 0,
	little_endian
};

class RWStream {
public:
	RWStream(uint32_t capacity, endian ed);
	~RWStream();
	uint32_t size() const { return capacity_; }
	uint32_t readAll(uint8_t *data);
	//uint32_t writeBytes(uint32_t* data);

	uint32_t read(uint8_t *data, uint32_t bytes);
	uint32_t write(const uint8_t *data, uint32_t bytes);
	//uint32_t available_data();
	uint32_t read_available_space();
	uint32_t write_available_space();
	uint32_t getPos();
	void setPos(int32_t pos);

	uint32_t getWritePos()
	{
		return write_index_;
	}

	void reset();
	uint8_t* init(uint32_t capacity = 1024);

	uint8_t readUint8();
	uint16_t readUint16();
	uint32_t readUint32();
	uint64_t readUint64();

	uint32_t writeUint8(uint8_t data);
	uint32_t writeUint16(uint16_t data);
	uint32_t writeUint32(uint32_t data);
	uint32_t writeUint64(uint64_t data);


	uint32_t writeString32(std::string s);
	std::string readString32();

	void setEndian(endian ed)
	{
		endian_ = ed;
	}

	endian getEndian()
	{
		return endian_;
	}

public:
	uint32_t capacity_;
	uint8_t* buffer_;
	uint32_t read_index_;
	uint32_t write_index_;
	uint32_t size_;
	endian endian_;

	uint8_t uint8_buffer_[1];
	uint8_t uint16_buffer_[2];
	uint8_t uint32_buffer_[4];
	uint8_t uint64_buffer_[8];

	uint8_t uint8_wbuffer_[1];
	uint8_t uint16_wbuffer_[2];
	uint8_t uint32_wbuffer_[4];
	uint8_t uint64_wbuffer_[8];

	inline uint16_t getUint16(uint8_t* buffer){
		uint16_t b = 0;
		if (endian_ == little_endian) {
			b = (uint16_buffer_[1] << 8) | (uint16_buffer_[0]);
		}
		else{
			b = (uint16_buffer_[0] << 8) | (uint16_buffer_[1]);
		}

		return b;
	}
	inline uint32_t getUint32(uint8_t* buffer){

		uint32_t b = 0;
		if (endian_ == little_endian)
		{
			b = (uint32_buffer_[3] << 24) |
				(uint32_buffer_[2] << 16) |
				(uint32_buffer_[1] << 8) |
				(uint32_buffer_[0]);
		}
		else
		{
			b = (uint32_buffer_[0] << 24) |
				(uint32_buffer_[1] << 16) |
				(uint32_buffer_[2] << 8) |
				(uint32_buffer_[3]);
		}
		return b;
	}
	inline uint64_t getUint64(uint8_t* buffer){
		uint64_t b = 0;
		if (endian_ == little_endian) {
			b =
				(uint64_buffer_[7] << 24) | (uint64_buffer_[6] << 16) |
				(uint64_buffer_[5] << 8) | (uint64_buffer_[4]);
			b = b << 32;
			b =
				(uint64_buffer_[3] << 24) | (uint64_buffer_[2] << 16) |
				(uint64_buffer_[1] << 8) | (uint64_buffer_[0]) | b;
		}
		else {
			b =
				(uint64_buffer_[0] << 24) | (uint64_buffer_[1] << 16) |
				(uint64_buffer_[2] << 8) | (uint64_buffer_[3]);
			b = b << 32;
			b =
				(uint64_buffer_[4] << 24) | (uint64_buffer_[5] << 16) |
				(uint64_buffer_[6] << 8) | (uint64_buffer_[7]) | b;
		}
		return b;
	}

	inline uint8_t* setUint16(uint16_t data){
		if (endian_ == little_endian) {
			uint16_wbuffer_[0] = (data & 0xFF);
			uint16_wbuffer_[1] = ((data >> 8) & 0xFF);
		}
		else {
			uint16_wbuffer_[1] = (data & 0xFF);
			uint16_wbuffer_[0] = ((data >> 8) & 0xFF);
		}
		return uint16_wbuffer_;
	}

	inline uint8_t* setUint32(uint32_t data){
		if (endian_ == little_endian) {
			uint32_wbuffer_[0] = (data & 0xFF);
			uint32_wbuffer_[1] = ((data >> 8) & 0xFF);
			uint32_wbuffer_[2] = ((data >> 16) & 0xFF);
			uint32_wbuffer_[3] = ((data >> 24) & 0xFF);
		}
		else {
			uint32_wbuffer_[3] = (data & 0xFF);
			uint32_wbuffer_[2] = ((data >> 8) & 0xFF);
			uint32_wbuffer_[1] = ((data >> 16) & 0xFF);
			uint32_wbuffer_[0] = ((data >> 24) & 0xFF);
		}
		return uint32_wbuffer_;
	}

	inline uint8_t* setUint64(uint64_t data){
		if (endian_ == little_endian) {
			uint64_wbuffer_[0] = (data & 0xFF);
			uint64_wbuffer_[1] = ((data >> 8) & 0xFF);
			uint64_wbuffer_[2] = ((data >> 16) & 0xFF);
			uint64_wbuffer_[3] = ((data >> 24) & 0xFF);
			data = data >> 32;
			uint64_wbuffer_[4] = (data & 0xFF);
			uint64_wbuffer_[5] = ((data >> 8) & 0xFF);
			uint64_wbuffer_[6] = ((data >> 16) & 0xFF);
			uint64_wbuffer_[7] = ((data >> 24) & 0xFF);
		}
		else {
			uint64_wbuffer_[7] = (data & 0xFF);
			uint64_wbuffer_[6] = ((data >> 8) & 0xFF);
			uint64_wbuffer_[5] = ((data >> 16) & 0xFF);
			uint64_wbuffer_[4] = ((data >> 24) & 0xFF);
			data = data >> 32;
			uint64_wbuffer_[3] = (data & 0xFF);
			uint64_wbuffer_[2] = ((data >> 8) & 0xFF);
			uint64_wbuffer_[1] = ((data >> 16) & 0xFF);
			uint64_wbuffer_[0] = ((data >> 24) & 0xFF);
		}
		return uint64_wbuffer_;
	}

	inline int writeUint(uint32_t value){
		int encoded = 0;
		do
		{
			uint8_t next_byte = value & 0x7F;
			value >>= 7;
			if (value)
				next_byte |= 0x80;
			writeUint8(next_byte);
			encoded++;
		} while (value);        //value负责判断是否需要增加位数
		return encoded;
	}

	inline int writeInt(int32_t value){
		uint32_t uvalue;
		uvalue = uint32_t(value < 0 ? ~(value << 1) : (value << 1));
		return writeUint(uvalue);
	}

	inline uint32_t readUint(){
		int i = 0;
		uint32_t decoded_value = 0;
		memset(uint32_buffer_, 0, 4);

		int shift_amount = 0;
		do
		{
			read((uint32_buffer_ + i), 1);
//			printf("uint32_buffer_ %d : %#.2x\n", i, uint32_buffer_[i]);
			//        read(uint32_buffer_+i, 1);
			decoded_value |= (uint32_t)(uint32_buffer_[i] & 0x7F) << shift_amount;
			shift_amount += 7;
		} while ((uint32_buffer_[i++] & 0x80) != 0); //判断后面是否最高位为1，为1则parse 下一个byte
		return decoded_value;
	}

	inline int32_t readInt(){
		uint32_t unsigned_value = readUint();
		return (int32_t)(unsigned_value & 1 ? ~(unsigned_value >> 1)
			: (unsigned_value >> 1));
	}

	uint32_t writeString(std::string s)
	{
		uint32_t strlen = (uint32_t)s.size();
		uint32_t encode_strlen = writeUint(strlen);
		return encode_strlen + write(reinterpret_cast<const uint8_t*>(s.c_str()), strlen);
	}

	std::string readString()
	{
		uint32_t length = readUint();
//		printf("string length %d\n", length);
		std::string s("", length);
		read(reinterpret_cast<uint8_t*>(const_cast<char *>(s.c_str())), length);
		return s;
	}
};

	
	


#endif /* defined(__RWStream__RWStream__) */
