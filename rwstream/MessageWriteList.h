#include "MessageWrite.h"

class MessageWriteList :public MessageWrite
{
public:
	MessageWriteList(uint32_t len, endian ed) :MessageWrite(len,ed){
		m_listlen = 0;
		m_listnum = 0;
		m_datalen = 0;
		m_bodylen = 0;
		m_listbody = nullptr;
	}

	~MessageWriteList(){
		delete[] m_listbody;
	}

	void setListStruct(uint8_t row, uint8_t column)
	{
		m_listrow = row;
		m_listcolumn = column;
	}

	uint8_t* writeListBytes()
	{	
		uint8_t* body = writeListBody();
		uint8_t metalen = m_listcolumn + 1;

		m_listlen = m_bodylen + 3 + metalen;
		m_listbody = new uint8_t[m_listlen];
		if (getRWStream()->getEndian() == little_endian)
		{
			m_listbody[0] = m_listlen & 0xFF;
			m_listbody[1] = (m_listlen) >> 8 & 0xFF;
		}
		else
		{
			m_listbody[1] = m_listlen & 0xFF;
			m_listbody[0] = (m_listlen) >> 8 & 0xFF;
		}
		m_listbody[2] = m_listrow;
		metabuff[0] = m_listcolumn;
		memcpy(m_listbody + 3, metabuff, metalen);
		memcpy(m_listbody + 3 + metalen, body, m_bodylen);
		delete[] body;
		return m_listbody;
	}

	uint8_t* writeListBody()
	{
		uint32_t datalen = getRWStream()->getWritePos();
		m_bodylen = datalen;
		uint8_t* body = new uint8_t[datalen];
		m_datalen = getRWStream()->readAll(body);
		return body;
	}

	uint16_t m_listlen;
	uint8_t m_listnum;
	uint16_t m_datalen;
	uint16_t m_bodylen;
	uint8_t* m_listbody;

	uint8_t m_listrow;
	uint8_t m_listcolumn;
private:
};

