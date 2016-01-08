//
// MessageRead
//
//  Created by ‘¨Û“ø≠ on 15/9/7.
//  Copyright (c) 2015ƒÍ ‘¨Û“ø≠. All rights reserved.
//


#include <stdint.h>
#include <memory.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "RWStream.h"
#include "ProtocolCheck.h"
//zlib
#include <zlib.h>

#ifndef LEN_AND_FLAG_H
#define LEN_AND_FLAG_H
const uint8_t flag1 = 0x59;
const uint8_t flag2 = 0x7a;
const uint8_t message_datatype = 0x00;

const int flag_len = 2;
const int type_len = 1;
const int method_len = 2;
const int body_len = 4;

const int meta_num_len = 1;
#endif //LEN_AND_FLAG_H

//#define PUSH_TABLE_BACK 1
#define  MAXBUFFERSIZE 1024*100

class MessageRead
{
public:
    int selfMethod = 0;
    bool isErr = false;
    bool doCheck = false;
public:
	RWStream* m_rw;
    RWStream* m_rw_new;
	MessageRead(uint32_t len, endian ed){
		m_rw = new RWStream(len, ed);
        m_rw_new = new RWStream(len, ed);
	}

	~MessageRead(){
		delete m_rw;
		m_rw = nullptr;
        delete m_rw_new;
        m_rw_new = nullptr;
	}

    //return num, -1 means err
	inline int parsepacket(string& retMsg, string& errMsg, lua_State* L, bool doCheck)
	{
        this->doCheck = doCheck;
        int num = 0;
        
        //lua_createtable(L, 2, 0);
        lua_newtable(L); //create a new table
        
        uint32_t version = 0;
		uint32_t pre_len = flag_len+2+type_len + body_len;
        cout << m_rw->read_available_space() << endl;
		while (m_rw->read_available_space() >= pre_len)
		{
			m_rw->readUint8();
			if (m_rw->uint8_buffer_[0] == flag1)
			{
				//printf("flag1 :%d\n", m_rw->uint8_buffer_[0]);
				m_rw->readUint8();		
				if (m_rw->uint8_buffer_[0] == flag2)
				{
					//printf("flag2 :%d\n", m_rw->uint8_buffer_[0]);
					uint8_t type = m_rw->readUint8();
					//printf("type :%d\n", type);
                    uint16_t method = m_rw->readUint16();
                    //printf("method :%d\n", method);
                    uint32_t datasize = m_rw->readUint32();
					//printf("datasize :%d\n", datasize);
					//printf("read_available_space :%d\n",m_rw->read_available_space());
					if (m_rw->read_available_space() < datasize)
					{
						std::cout << "received data is not enough" << std::endl;
						pre_len = 0 - pre_len;
						m_rw->setPos(pre_len);
						break;
					}
					if (m_rw->read_available_space() >= datasize)
					{
                        num++;//return counts
                        selfMethod = (int)method;

                        lua_pushnumber(L, num);
                        lua_newtable(L);
          
						uint8_t flag = m_rw->readUint8();
                        int metalen;
                        uint8_t* metabuff;
                        string parseRet;
                        
                        if (flag == 1) {
                            //TODO: uncompress
                            //get compress data and len
                            uint8_t compressData[datasize-1];
                            memset(compressData, 0, datasize-1);
                            m_rw->read(compressData, datasize-1);
                            uLong compressLen = datasize-1;
                            //uncompress data and len
                            uint8_t uncompressData[MAXBUFFERSIZE];
                            uLong uncompressLen = MAXBUFFERSIZE;
                            memset(uncompressData, 0, MAXBUFFERSIZE);

                            //time
                            double t1 = Common::getInstance()->getTime();
                            //uncompress
                            if(uncompress(uncompressData, &uncompressLen, compressData, compressLen) != Z_OK)
                            {
                                printf("uncompress failed!\n");
                                return -1;  
                            }
                            //time
                            double t2 = Common::getInstance()->getTime();
                            cout << "time1:" << t1 << "  time2:" << t2 << "  time:" << t2-t1 << endl;
                            cout<< "method:" << selfMethod << "  uncompress-->before bytes:" << compressLen << "  after bytes:" << uncompressLen << endl;
                            //new RWStream
                            m_rw_new->write(uncompressData, (uint32_t)uncompressLen);
                            
                            //get
                            metalen = m_rw_new->readUint8();
                            metabuff = new uint8_t[metalen];
                            parseMeta(metalen,metabuff, m_rw_new);
                            //parsebody
                            parseRet = parsebody(metabuff, metalen, m_rw_new, L);
                        }
                        else
                        {
                            metalen = m_rw->readUint8();
                            metabuff = new uint8_t[metalen];
                            parseMeta(metalen,metabuff, m_rw);
                            //parsebody
                            parseRet = parsebody(metabuff, metalen, m_rw, L);
                        }
						
                        if (isErr)
                        {
                            errMsg = parseRet;
                            return -1;
                        }

                        //method,ver
//                        lua_pushstring(L, "method");
//                        lua_pushnumber(L, method);
//                        //    lua_settable(lua_state, -3);
//                        lua_rawset(L, -3);
//                        lua_pushstring(L, "ver");
//                        lua_pushnumber(L, version);
//                        //    lua_settable(lua_state, -3);
//                        lua_rawset(L, -3);
                        
                        lua_pushnumber(L, method);
                        lua_setfield(L, -2, "method");
                        lua_pushnumber(L, version);
                        lua_setfield(L, -2, "ver");
                        lua_settable(L, -3); //end a table

						printf("parse PACKET\n");
						delete[] metabuff;
					}
				}
			}
		}
        retMsg = "";
		return num;
	}

	inline uint8_t* parseMeta(int len, uint8_t* metabuff, RWStream* tmp_rw)
	{
		for (int i = 0; i < len; i++)
		{
			*(metabuff+i) = tmp_rw->readUint8();
			uint8_t index = metabuff[i] >> 3;
			uint8_t type = metabuff[i] & 0x07;
			metabuff[i] = type;
		}
		return metabuff;
	}

	inline string parselist(RWStream* tmp_rw, lua_State* L)
	{
		//printf("%d list pos", tmp_rw->getPos());
		uint16_t list_body_len = tmp_rw->readUint16();
		uint8_t item_len = tmp_rw->readUint8();
		int metalen = tmp_rw->readUint8();
		//printf(" ----metalen----  %d \n", metalen);
		uint8_t* metabuff = new uint8_t[metalen];
		parseMeta(metalen,metabuff, tmp_rw);
        
        char t[50];
        char *tt = t;
        string headStr_tab;
		for (int i = 0; i < metalen; i++)
		{
            sprintf(tt, "%d", metabuff[i]);
            headStr_tab+=tt;
			//printf("list metatype: %d\n", metabuff[i]);
		}
//table data

        lua_newtable(L);

		for (int i = 0; i < (int)item_len; i++)
		{
			//printf("list parse :  \n");

            lua_pushnumber(L, i+1);
            lua_newtable(L);

            parselistbody(metabuff, metalen, tmp_rw, L);

//            lua_setfield(L, -2, "data");
            lua_settable(L, -3);

		}

        lua_setfield(L, -2, "data");

		delete[] metabuff;

        //head len
        lua_pushlstring(L, headStr_tab.c_str(), headStr_tab.size());
        lua_setfield(L, -2, "head");
        lua_pushnumber(L, (int)item_len);
        lua_setfield(L, -2, "len");

        return "";
	}
    
    inline string parselistbody(uint8_t* metabuff, int metalen, RWStream* tmp_rw, lua_State* L){
        
        for (int i = 0; i < metalen; i++)
        {
            uint8_t type = metabuff[i];
            
            switch (type)
            {
                case 0:
                {
                    uint32_t reti = tmp_rw->readUint();
                    //sprintf(addStr, "%d,\n", tmp_rw->readUint());
                    
                    lua_pushnumber(L, i+1);
                    lua_pushnumber(L, reti);
                    lua_settable(L, -3);
                    
                    break;
                }
                case 1:
                {
                    std::string s;
                    s = tmp_rw->readString();

                    lua_pushnumber(L, i+1);
                    lua_pushlstring(L, s.c_str(), s.size());
                    lua_settable(L, -3);

                    break;
                }
                case 2:
                {
                    int reti = tmp_rw->readInt();
                    
                    lua_pushnumber(L, i+1);
                    lua_pushnumber(L, reti);
                    lua_settable(L, -3);
                    
                    break;
                }
                case 3:
                {
                    //printf("type :: list");
                    //parselist();
                    break;
                }
                case 4:
                {
                    string s = tmp_rw->readString32();
                    
                    lua_pushnumber(L, i+1);
                    lua_pushlstring(L, s.c_str(), s.size());
                    lua_settable(L, -3);
  
                    break;
                }
                default:
                    return "err";
            }
        }
        return "";
    }

	inline string parsebody(uint8_t* metabuff, int metalen, RWStream* tmp_rw, lua_State* L){
        ProtocolCheck* _check = ProtocolCheck::getInstance();
        
//        lua_pushstring(L, "body");
//        lua_newtable(L);
        
        lua_newtable(L);
        
		for (int i = 0; i < metalen; i++)
		{
			uint8_t type = metabuff[i];
            
            if(this->doCheck)
            {
                //check the type
                if (!_check->check(selfMethod, i+1, type)) {
                    isErr = true;
                    string retStr = "Err: type is wrong:";
                    retStr+=_check->getInfo(selfMethod, i+1);
                    cout<<retStr<<endl;
                    return retStr;
                }
            }
        
			switch (type)
			{
                case 0:
                {
                    int ret = tmp_rw->readUint();
                    
//                    lua_pushstring(L, (_check->getInfo(selfMethod, i+1)).c_str());
//                    lua_pushnumber(L, m_rw->readUint());
//                    lua_rawset(L, -3);
                    
                    lua_pushnumber(L, ret);
                    lua_setfield(L, -2, (_check->getInfo(selfMethod, i+1)).c_str());
                    
                    break;
                }
                case 1:
                {
                    std::string s;
                    s = tmp_rw->readString();

//                    lua_pushstring(L, (_check->getInfo(selfMethod, i+1)).c_str());
//                    lua_pushstring(L, s.c_str());
//                    lua_rawset(L, -3);
                    
                    lua_pushlstring(L, s.c_str(), s.size());
                    lua_setfield(L, -2, (_check->getInfo(selfMethod, i+1)).c_str());
                    
                    break;
                }
                case 2:
                {
                    int ret = tmp_rw->readInt();
                    
//                    lua_pushstring(L, (_check->getInfo(selfMethod, i+1)).c_str());
//                    lua_pushnumber(L, m_rw->readUint());
//                    lua_rawset(L, -3);
                    
                    lua_pushnumber(L, ret);
                    lua_setfield(L, -2, (_check->getInfo(selfMethod, i+1)).c_str());
                    
                    break;
                }
                case 3:
                {
                    //printf("type :: list");
                    
                    lua_newtable(L);
                    
                    string s = parselist(tmp_rw, L);
                    
                    lua_setfield(L, -2, _check->getInfo(selfMethod, i+1).c_str());
                
                    break;
                }
                case 4:
                {
                    std::string s;
                    s = tmp_rw->readString32();
                    
//                    lua_pushstring(L, (_check->getInfo(selfMethod, i+1)).c_str());
//                    lua_pushstring(L, s.c_str());
//                    lua_rawset(L, -3);
                    
                    lua_pushlstring(L, s.c_str(), s.size());
                    lua_setfield(L, -2, (_check->getInfo(selfMethod, i+1)).c_str());
                    
                    break;
                }
                default:
                    return "";
			}
		}
        
//        lua_rawset(L, -3);
        lua_setfield(L, -2, "body");
        
        return "";
	}
    
    
};//class


