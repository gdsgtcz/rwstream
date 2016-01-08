//
//  AsioClient.h
//  hhl
//
//  Created by guodi on 15/9/29.
//
//

#ifndef __hhl__AsioClient__
#define __hhl__AsioClient__

#include <stdio.h>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <thread>
#include "SocketAsio.h"
#include "ReceiveMsgPool.h"

using boost::asio::ip::tcp;
using boost::asio::ip::address;
using namespace boost::asio;
using namespace std;

typedef std::deque<string> message_queue;

class session
{
public:
    session(boost::asio::io_service &io_service, tcp::resolver::iterator &iterator)
    : io_service_(io_service), socket_(io_service), _iterator(iterator)
    {
    }
    
    void start(int type) {
        if(_isConnect) return;
        this->type = type;
        //连接
//        socket_.async_connect(_iterator,
//                              boost::bind(&session::handle_connect,
//                              this,
//                              boost::asio::placeholders::error));
        boost::asio::async_connect(socket_,
                                   _iterator,
                                   boost::bind(&session::handle_connect,
                                   this,
                                   boost::asio::placeholders::error));
    }
    
    void asyncWrite(string str)
    {
        io_service_.post(boost::bind(&session::do_write, this, str)); //将消息主动投递给io_service
    }
    
    void syncWrite(string str)
    {
        boost::system::error_code err;
        //send
        socket_.write_some(buffer(str), err);
        if (err)
        {
            cout << "同步发送出错" << endl;
            std::cout << boost::system::system_error(err).what() << std::endl;
            do_close();
        }
        
    }
    
    void close()
    {
        io_service_.post(boost::bind(&session::do_close, this));
    }
    
    bool isConnect()
    {
        return _isConnect;
    }

private:
    void handle_connect(const boost::system::error_code &error)
    {
        if(!error)
        {
            _isConnect = true;
            //回调
            //SocketAsio::getInstance()->connectCallback(0);
            ReceiveMsgPool::getInstance()->addMsg("connectStatus", 0);
            
            //循环读监听
            if(this->type == 0)
            {
                threadAsyncRead();
            }
            else
            {
                threadSyncRead();
            }
        }
        else
        {
            std::cout << "客户端连接失败" << std::endl;
            SocketAsio::getInstance()->connectCallback(-1);
            do_close();
        }
    }
    
    void do_write(string msg)
    {
        bool write_in_progress = !svector.empty();//空的话变量为false
        svector.push_back(msg);//push写队列
        if(!write_in_progress) //循环条件 第一次进入循环，以后不进入循环
        {
            socket_.async_write_some(boost::asio::buffer(svector.front().data(),svector.front().length()),
                                     boost::bind(&session::handle_write,
                                     this,
                                     boost::asio::placeholders::error,
                                     boost::asio::placeholders::bytes_transferred));
        }
    }
    
    void handle_write(const boost::system::error_code& error, size_t bytes_transferred)
    {
        if(!error)
        {
            svector.pop_front();
            if(!svector.empty())
            {
                //回调自己循环
                socket_.async_write_some(boost::asio::buffer(svector.front().data(),svector.front().length()),
                                         boost::bind(&session::handle_write,
                                         this,
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
            }
        }
        else
        {
            cout<< "异步发送失败" << endl;
            do_close();
        }
    }
    
    //异步读线程监听
    void threadAsyncRead()
    {
        socket_.async_read_some(boost::asio::buffer(rbuf, 1024),
                                boost::bind(&session::handle_read,
                                this,
                                boost::asio::placeholders::error,
                                boost::asio::placeholders::bytes_transferred));
        
    }
    
    //同步读线程监听
    void threadSyncRead()
    {
        boost::system::error_code err;
        while (_isConnect)
        {
            //receive
            size_t len = socket_.read_some(buffer(rbuf, 1024), err);
            if (err)
            {
                cout << "接收出错" << endl;
                std::cout << boost::system::system_error(err).what() << std::endl;
            }
            
            //处理服务器返回数据
            //printf("return size :%zu\n", len);
            string retStr(rbuf, rbuf+len);
//            SocketAsio::getInstance()->receive(retStr, len);
            ReceiveMsgPool::getInstance()->addMsg(retStr, len);
        }
    }
    
    void handle_read(const boost::system::error_code& error, size_t bytes_transferred)
    {
        if(!error)
        {
            //处理服务器返回数据
//            printf("async receive return size :%zu\n", bytes_transferred);
//            int i = 0;
//            for(i=0; i<bytes_transferred; i++)
//            {
//                printf("%x ",rbuf[i]);
//            }
//            printf("\n");
            string rStr(rbuf, rbuf+bytes_transferred);
//            SocketAsio::getInstance()->receive(rStr, bytes_transferred);
            ReceiveMsgPool::getInstance()->addMsg(rStr, bytes_transferred);
            
            if(_isConnect)
            {
                //循环
                socket_.async_read_some(boost::asio::buffer(rbuf, 1024),
                                        boost::bind(&session::handle_read,
                                                    this,
                                                    boost::asio::placeholders::error,
                                                    boost::asio::placeholders::bytes_transferred));
            }
        }
        else
        {
            std::cout << "客户端读失败" << std::endl;
            if (error.value() != boost::system::errc::operation_canceled) {
                std::cerr << boost::system::system_error(error).what() << std::endl;
            }
            do_close();
        }
    }
    
    void do_close()
    {
        _isConnect = false;
        socket_.close();
        //断开回调
        //SocketAsio::getInstance()->disconnectCallback();
        ReceiveMsgPool::getInstance()->addMsg("connectStatus", -1);
    }
    
private:
    boost::asio::io_service &io_service_;
    tcp::socket socket_;
    //tcp::endpoint &endpoint_;
    tcp::resolver::iterator &_iterator;
    std::string buf;
    boost::asio::streambuf sbuf;
    unsigned char rbuf[2048];  // 消息接收缓存
    bool _isConnect = false;
    int type; //type 0:异步，1:同步
    message_queue svector;
};


class AsioClient
{
public:
    AsioClient(){}
    ~AsioClient(){}
    
    void connect(string address, int port, int type)
    {
        this->address = address;
        this->port = port;
        this->type = type;
        //printf("-------->%s",address.c_str());
//        boost::asio::io_service io_service;
//        tcp::endpoint endpoint(address::from_string(address), port);
//        
//        client = new session(io_service, endpoint);
//        client->start(type);
//        io_service.run();

//        std::thread t([&io_service](){ io_service.run(); });
//        t.join();

//        boost::thread td(boost::bind(&boost::asio::io_service::run, &io_service));
//        td.join();

        //开线程
//        std::thread t1(boost::bind(&boost::asio::io_service::run, &io_service));
//        t1.detach();   //非阻塞
        
        std::thread t(&AsioClient::threadWork, this);
        t.detach();

    }
    
    //子线程
    void threadWork()
    {
        boost::asio::io_service io_service;
        //tcp::endpoint endpoint(address::from_string(address), port);
        //域名解析
        tcp::resolver resolver(io_service);
        char buffer[20];
        sprintf(buffer, "%d", port);
        tcp::resolver::query query(tcp::v4(), address, buffer);
        tcp::resolver::iterator iterator = resolver.resolve(query);
        
        client = new session(io_service, iterator);
        client->start(type);
        io_service.run();
    }
    
    void asyncSend(string sendStr)
    {
        client->asyncWrite(sendStr);
    }
    
    void syncSend(string sendStr)
    {
        client->syncWrite(sendStr);
    }
    
    void close()
    {
        client->close();
    }
    
    bool isConnect()
    {
        return client->isConnect();
    }

private:
    //client
    session * client;
    string address;
    int port;
    int type;
};


#endif /* defined(__hhl__AsioClient__) */
