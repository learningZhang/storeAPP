#include "head.h"

typedef enum _MsgType
{
    EN_MSG_LOGIN=0,       //进行登陆
    EN_MSG_REGISTER,    //进行注册
    EN_MSG_OFFLINE,     //离线
    EN_MSG_ACK,          //回复信息---------
    QUERYBYNAME,        //通过姓名查询信息
    QUERYBYID,          //通过id查询信息
    ADDITEM,           //增加项目
    DELETEBYNAME,      //通过名字进行删除
    DELETEBYID,        //通过id进行删除
    SALEITEM           //数据库增加物品
}EnMsgType;

//异步接收读线程
void* ReadThread(void *arg)
{
    int clientfd = (int)arg;
    CMysql db;    
    while(true)
    {
        char recvbuf[1024]={0};
        int size = 0;
        Json::Reader reader;
        Json::Value root;
        Json::Value response;
		bool tag = false;
        
        size = recv(clientfd, recvbuf, 1024, 0);
        if(size <= 0)//关闭该线程
        {
            cout<<"errno:"<<errno<<endl;
            cout<<"client connect fail!"<<endl;
            close(clientfd);
            return NULL;
        }
        cout<<"recvbuf:"<<recvbuf<<endl;
             
        if(reader.parse(recvbuf, root))
        {
            int msgtype = root["msgtype"].asInt();

            switch(msgtype)
            {
                case EN_MSG_LOGIN:
                {
                    response["msgtype"] = EN_MSG_ACK;
					char name1[20];
                    const char * name = root["name"].asString().c_str();strcpy(name1,name);char pwd1[20];
                    const char * pwd = root["pwd"].asString().c_str();strcpy(pwd1, pwd);
                    
                    if(!db.queryPasswd(name1, pwd1))
                    {
                        response["ackcode"] = "error";
                    }
                    else
                    {
                        response["ackcode"] = "ok";
                    }
                  
                    if (-1 == send(clientfd, response.toStyledString().c_str(),
                        strlen(response.toStyledString().c_str())+1, 0))
                        {
	                        cout<<"error in send in login"<<endl;
                        }
                }
                break;
                
                case EN_MSG_REGISTER:
	            {

	            	cout<<"one client is register"<<endl;
					char name1[20];char passwd1[20];char call1[20];
			        const char* name = root["name"].asString().c_str();
					strcpy(name1, name);
                   	const char *passwd = root["pwd"].asString().c_str();
					strcpy(passwd1, passwd);
                   	const char * call = root["phone"].asString().c_str();
					strcpy(call1, call);
		        	response["msgtype"] = EN_MSG_ACK;
		         	cout<<name<<passwd<<call<<name1<<passwd1<call1;
                    if(db.insertIntoUser(name1, passwd1, call1) == false)
                    {
		                response["ackcode"] = "error"; 
                    }
                 	else
	                {
		               response["ackcode"] = "OK";
	                }
	                	                	                  		        		        	
		        	if(-1 == send(clientfd,response.toStyledString().c_str(),strlen(response.toStyledString().c_str())+1,0))
                    {
	                    cout<<"server send register message error"<<endl;
                    }   
	            }
                break;

		case EN_MSG_OFFLINE:
			{
				exit(1);
			}
		break;


	  	case SALEITEM: //数据库增加物品
	            {
				
                 	response["msgtype"] = SALEITEM;
			     	char buytime1[20];
		       		const char *buytime = root["buytime"].asString().c_str();
				    strcpy(buytime1, buytime);char degree1[20];
		            const char *degree = root["degree"].asString().c_str();
 					strcpy(degree1, degree); char myaddre1[20];
		            const char *myaddre = root["myaddre"].asString().c_str();
 					strcpy(myaddre1, myaddre); char goodsaddre1[30];
		            const char *goodsaddre = root["goodsaddre"].asString().c_str();
					strcpy(goodsaddre1, goodsaddre); char name1[20];
        		    const char *moneychar = root["moneychar"].asString().c_str();
		            const char *name = root["name"].asString().c_str();strcpy(name1, name);
	         		int money = atoi(root["moneychar"].asString().c_str());

		            const char *id = root["id"].asString().c_str();
										
					if (db.insertIntoMessage(id,name1,buytime1,degree1,myaddre1,goodsaddre1,money) == true)
					{
						response["ackcode"] = "ok";
					}
					else
					{
						response["ackcode"] = "error";
					}
					if(-1 == send(clientfd,response.toStyledString().c_str(),strlen(response.toStyledString().c_str())+1,0))
                    {
	                    cout<<"server send register message error"<<endl;
                    } 
	            }
	            break;
	            
		case DELETEBYID: //通过id进行删除
	            {
		            response["msgtype"] = DELETEBYID;
		            const char *id = root["id"].asString().c_str();
		
					if (db.delInMessageByID(id) == true)
					{
						response["ackcode"] = "ok";
					}
					else
					{
						response["ackcode"] = "error";
					}
					if(-1 == send(clientfd,response.toStyledString().c_str(),strlen(response.toStyledString().c_str())+1,0))
                    {
	                    cout<<"server send register message error"<<endl;
                    } 
	            }
	            break;
	            
				case DELETEBYNAME: //通过名字进行删除
	            {
		            response["msgtype"] = DELETEBYNAME;
		            const char *name = root["name"].asString().c_str();
		           	if (db.delInMessageByName(name) == true)
					{
						response["ackcode"] = "ok";
					}
					else
					{
						response["ackcode"] = "error";
					}
					if(-1 == send(clientfd,response.toStyledString().c_str(),strlen(response.toStyledString().c_str())+1,0))
                    {
	                    cout<<"server send register message error"<<endl;
                    } 
	            }
	            break;
	            case QUERYBYID: //通过id查询信息
	            {
		            response["msgtype"] = QUERYBYID;
		           	const char *id = root["id"].asString().c_str();
		            char *message = (char *)malloc(sizeof(char)*MESG_MAX);
					if (db.findMessageByID(id, message, MESG_MAX) == true)
					{
						response["ackcode"] = "ok";
						response["id"] = strtok(message, "-");
						response["name"] = strtok(NULL, "-");
						response["buytime"] = strtok(NULL, "-");
						response["degree"] = strtok(NULL, "-");
						response["myddre"] = strtok(NULL, "-");
						response["goodsaddre"] = strtok(NULL, "-");
						response["money"] = strtok(NULL, "-");					
					}
					else
					{
						response["error"];
					}
					free(message);
					if(-1 == send(clientfd,response.toStyledString().c_str(),strlen(response.toStyledString().c_str())+1,0))
                    {
	                    cout<<"server send register message error"<<endl;
                    } 
	            }
	            break;
	            
	            case QUERYBYNAME: ///通过姓名查询信息
	            {
		            response["msgtype"] = QUERYBYNAME;
		            const char *name = root["name"].asString().c_str();
				cout<<name<<endl;
		            char *message = (char *)malloc(sizeof(char)*MESG_MAX);
					
					if (db.findMessageByName(name, message, MESG_MAX) == true)
					{
						response["ackcode"] = "ok";
						response["id"] = strtok(message, "-");
						response["name"] = strtok(NULL, "-");
						response["buytime"] = strtok(NULL, "-");
						response["degree"] = strtok(NULL, "-");
						response["myddre"] = strtok(NULL, "-");
						response["goodsaddre"] = strtok(NULL, "-");
						response["money"] = strtok(NULL, "-");					
					}
					else
					{
						response["error"];
					}
					free(message);
					cout<<response.toStyledString().c_str()<<endl;
					if(-1 == send(clientfd,response.toStyledString().c_str(),strlen(response.toStyledString().c_str())+1,0))
                    {
	                    cout<<"server send register message error"<<endl;
                    } 
	            }
	            break;
            }
        }
        else
        {
	        cout<<"one client close!"<<endl;
            close(clientfd);
        }
    }
}

//libevent回调函数
void ProcListenfd(evutil_socket_t fd, short st, void *arg)
{
    sockaddr_in client;
    socklen_t len = sizeof(client);
    int clientfd = accept(fd, (sockaddr*)&client, &len);
  
    cout<<"new client connect server! client info:"
        <<inet_ntoa(client.sin_addr)<<" "<<ntohs(client.sin_port)<<endl;
        
    pthread_t tid;
    pthread_create(&tid, NULL, ReadThread, (void*)clientfd);
}

int main()
{
    int listenfd;
    
    //map添加人员信息
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == -1)
    {
        cout<<"listenfd create fail!"<<endl;
        return -1;
    }
    
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(10000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    if(-1 == bind(listenfd, (sockaddr*)&server, sizeof(server)))
    {
        cout<<"listenfd bind fail!"<<endl;
        return -1;
    }
    
    if(-1 == listen(listenfd, 20))
    {
        cout<<"listenfd listen fail!"<<endl;
        return -1;
    }
    
    //创建reactor   统一事件源  socket I/O，信号，定时器
    struct event_base* base = event_init();
    
    //创建event事件
    struct event *listen_event = event_new(base, listenfd,  EV_READ|EV_PERSIST, ProcListenfd, NULL);
    //把event事件添加到reactor中
    event_add( listen_event, NULL );
    
    cout<<"server started..."<<endl;
    //启动反应堆
    event_base_dispatch(base);
    //释放事件资源
    event_free(listen_event);
    //关闭reactor
    event_base_free(base);
    return 0;
}
