#include <stdint.h>
#include <memory.h>
#include "RWStream.h"
#include <zlib.h>
#include "Common.h"

#ifndef LEN_AND_FLAG_H
#define LEN_AND_FLAG_H
const uint8_t flag1 = 0x59;
const uint8_t flag2 = 0x7a;
const uint8_t message_datatype = 0x00;

const int flag_len = 2;
const int type_len = 1;
const int body_len = 4;
const int methon_len = 2;
const int version_len = 1;
const int meta_num_len = 1;
#endif //LEN_AND_FLAG_H

class RWStream;

class MessageWrite
{

public:
	MessageWrite(uint32_t len, endian ed){
		m_rw = new RWStream(len,ed);
		m_key = 0;
		m_num = 0;
		m_packetlen = 0;
		memset(metabuff, 0, 33);
		m_packetbuff = nullptr;
	}

	~MessageWrite(){
		delete m_rw;
		m_rw = nullptr;
		delete[] m_packetbuff;
	}

	void setMsgType(uint8_t msgType, uint8_t key = 0){
		if (key == 0){
			if (m_key < 33 && m_num < 33)
			{
				uint8_t metaType = m_key << 3 | msgType;
				metabuff[m_key+1] = metaType;		
				m_key++;
				m_num++;
			}
		}
		else{
			if (m_key < 33 && m_num < 33)
			{
				uint8_t metaType = (key << 3) | msgType;
				metabuff[key + 1] = metaType;
				m_num++;
			}
		}
	}

	uint32_t writeUInt(uint32_t value, uint8_t key = 0){
		setMsgType(0, key = 0);
		return m_rw->writeUint(value);
	}

	uint32_t writeInt(uint32_t value, uint8_t key = 0){
		setMsgType(2, key);
		return m_rw->writeInt(value);
	}

	uint32_t writeString(std::string str, uint8_t key = 0){
		setMsgType(1, key);
		return m_rw->writeString(str);
	}

	uint32_t writeString32(std::string str, uint8_t key = 0){
		setMsgType(4, key);
		return m_rw->writeString32(str);
	}

	uint32_t writeList(uint8_t* list, uint8_t key = 0){
		setMsgType(3, key);
		uint16_t listlen = 0;
		if (getRWStream()->getEndian() == little_endian){
			listlen = (list[1] << 8) | (list[0]);
		}
		else{
			listlen = (list[0] << 8) | (list[1]);
		}
		return m_rw->write(list, listlen);
	}

	RWStream* getRWStream(){
		return m_rw;
	}

	inline uint8_t* writePacket(uint8_t version, uint16_t messagecode, int compressSize)
	{
		uint32_t metalen = m_num + 1;
		m_packetlen = m_rw->getWritePos() + 10 + metalen;
		m_packetbuff = new uint8_t[m_packetlen];
		m_packetbuff[0] = flag1;
		m_packetbuff[1] = flag2;
		m_packetbuff[2] = message_datatype;
        m_packetbuff[3] = messagecode & 0xff;
        m_packetbuff[4] = messagecode >> 8 & 0xff;
        
        uint32_t datasize = m_packetlen - 9;
        metabuff[0] = m_num;
        
        uint8_t flag = 0;
        if (datasize>=compressSize) {
            flag = 1;
            //TODO: compress
            uint8_t* compressData = NULL;
            uLong compressLen;
            compressLen = compressBound(metalen+m_rw->write_index_);
            //malloc
            if((compressData = (uint8_t*)malloc(sizeof(uint8_t) * compressLen)) == NULL)
            {
                printf("no enough memory!\n");
                return NULL;
            }
            //get uncompress data and len
            uint8_t* addBuff = new uint8_t[metalen+m_rw->write_index_];
            memcpy(addBuff,metabuff, metalen);
            memcpy(addBuff+metalen, m_rw->buffer_, m_rw->write_index_);
            //time
            double t1 = Common::getInstance()->getTime();
            //compress
            if(compress(compressData, &compressLen, addBuff, metalen+m_rw->write_index_) != Z_OK)
            {
                printf("compress failed!\n");
                return NULL;
            }
            //time
            double t2 = Common::getInstance()->getTime();
            cout << "time1:" << t1 << "  time2:" << t2 << "  time:" << t2-t1 << endl;
            cout<< "compress-->before bytes:" << metalen+m_rw->write_index_ << "  datasize:" << datasize << "  after bytes:" << compressLen << endl;
            datasize = compressLen + 1;
            memcpy(m_packetbuff + 10, compressData, compressLen);
            //释放
            free(compressData);
            delete [] addBuff;
        }
        else
        {
            memcpy(m_packetbuff + 10, metabuff, metalen);
            memcpy(m_packetbuff + 10 + metalen, m_rw->buffer_, m_rw->write_index_);
        }
        
		if (getRWStream()->getEndian() == little_endian)
		{
			m_packetbuff[5] = datasize & 0xff;
			m_packetbuff[6] = datasize >> 8 & 0xff;
			m_packetbuff[7] = datasize >> 16 & 0xff;
			m_packetbuff[8] = datasize >> 24 & 0xff;
		}
		else
		{
			m_packetbuff[8] = datasize & 0xff;
			m_packetbuff[7] = datasize >> 8 & 0xff;
			m_packetbuff[6] = datasize >> 16 & 0xff;
			m_packetbuff[5] = datasize >> 24 & 0xff;
		}

		m_packetbuff[9] = flag;
		
		return m_packetbuff;
	}

	RWStream* m_rw;
	uint32_t m_key;
	uint8_t m_num;
	uint32_t m_packetlen;
	uint8_t metabuff[33];
	uint8_t* m_packetbuff;
};





