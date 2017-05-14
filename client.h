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
    SALEITEM        
}EnMsgType;

typedef struct _node
{
	EnMsgType msgty;
	char id[20];
	char name[20];
	char buytime[20];
	char degree[20];
	char myaddre[30];
	char goodsaddre[30];
	char moneychar[10];
	_node(){memset(0,sizeof(_node), 0);}	
}Node;
char name[20];
char pwd[20];
char phone[20];
Node st;
bool operate(int fd);

bool doLogin(int fd)
{
    cout<<"name: ";
    cin.getline(name, 20);
    cout<<"pwd: ";
    cin.getline(pwd, 20);
    //组装json字符串
    Json::Value root;
    root["msgtype"] = EN_MSG_LOGIN;
    root["name"] = name;
    root["pwd"] = pwd;

    int size = send(fd, root.toStyledString().c_str(),
        strlen(root.toStyledString().c_str())+1, 0);
    if(size < 0)
    {
        cout<<"send login msg fail!"<<endl;
        exit(0);
    }
    
    //接收server返回的登录消息
    char recvbuf[1024]={0};
    size = recv(fd, recvbuf, 1024, 0);
    if(size < 0)
    {
        cout<<"recv server login ack fail!"<<endl;
        exit(0);
    }
    
    Json::Reader reader;
    if(reader.parse(recvbuf, root))
    {
        int msgtype = root["msgtype"].asInt();
        if(msgtype != EN_MSG_ACK)
        {
            cout<<"recv server login ack msg invalid!"<<endl;
            exit(0);
        }
        string ackcode = root["ackcode"].asString();
        cout<<root.toStyledString()<<endl;
        if(ackcode == "ok")
        {
            return true;
        }
        return false;
    }
    return false;
}

void doregister(int fd)
{
	cout<<"name: ";
	cin.getline(name,20);
	cout<<"pwd: ";
	cin.getline(pwd,20);
	cout<<"phone: ";
	cin.getline(phone,11);

	//组装json字符串
	Json::Value root;
    root["msgtype"] = EN_MSG_REGISTER;
    root["name"] = name;
    root["pwd"] = pwd;
    root["phone"] = phone;

    cout<<root.toStyledString()<<endl;
	
    //发送注册消息到server
    int size = send(fd, root.toStyledString().c_str(),
        strlen(root.toStyledString().c_str())+1, 0);
    if(size < 0)
    {
        cout<<"send register msg fail!"<<endl;
        exit(0);
    }

	//接受server返回的注册消息
	
    char recvbuf[1024]={0};
    size = recv(fd, recvbuf, 1024, 0);
    if(size < 0)
    {
        cout<<"recv server register ack fail!"<<endl;
        exit(0);
    }
    
    Json::Reader reader;
    if(reader.parse(recvbuf, root))
    {
        int msgtype = root["msgtype"].asInt();
        if(msgtype != EN_MSG_ACK)
        {
            cout<<"recv server register ack msg invalid!"<<endl;
            exit(0);
        }
        string ackcode = root["ackcode"].asString();
        cout<<root.toStyledString()<<endl;
        if(ackcode == "OK")
        {
            cout<<"register success!"<<endl;
            return ;
        }
        cout<<"register error! the user is already register!"<<endl;
    }
}


bool offline(int fd)
{
	st.msgty = EN_MSG_OFFLINE;
	operate(fd);
}
Node queryByName(int fd)
{	
	cout<<"name:";
	cin.getline(st.name, 20); 
    st.msgty = QUERYBYNAME;
    operate(fd);
}  
    		
void queryById(int fd)
{
	cout<<"ID:";
	cin.getline(st.id, 20); 
    st.msgty = QUERYBYID;
    operate(fd);	
}

void addItem(int fd)
{
	cout<<"over in 157"<<endl;
}

void deleteByName(int fd)
{
	cout<<"name:";
	cin.getline(st.name, 20); 
    st.msgty = DELETEBYNAME;
    operate(fd);	
}
    	
void deleteById(int fd)
{
	cout<<"ID:";
	cin.getline(st.id, 20); 
    st.msgty = DELETEBYID;
    operate(fd);
}
   
void saleItem(int fd)
{
	cout<<"name: ";
	cin.getline(st.name, 20);
	cout<<"id: ";
	cin.getline(st.id, 20);
	cout<<"buytime: ";
	cin.getline(st.buytime, 20);
	cout<<"degree: ";
	cin.getline(st.degree, 20);
	cout<<"myaddre: ";
	cin.getline(st.myaddre, 30);
	cout<<"goodsaddre: ";
	cin.getline(st.goodsaddre, 30);
	cout<<"moneychar：";
	cin.getline(st.moneychar, 20);
    st.msgty = SALEITEM;
    operate(fd);
}

bool operate(int fd)
{	
	Json::Value root;
	if (st.msgty == SALEITEM)
	{
	    root["msgtype"] = SALEITEM;
	    root["name"] = st.name;
	    root["id"] = st.id;	
	  	root["buytime"] = st.buytime;
		root["degree"]=st.degree;
		root["myaddre"]=st.myaddre;
		root["goodsaddre"]=st.goodsaddre;
		root["moneychar"]=st.moneychar;
	}
	else if (st.msgty == QUERYBYID)
	{
		root["msgtype"] = QUERYBYID;
	    root["id"] = st.id;
	}
	else if(st.msgty == DELETEBYID)
	{
		root["msgtype"] = DELETEBYID;
	    root["id"] = st.id;	
	}
	else if (st.msgty == DELETEBYNAME)
	{
		root["msgtype"] = DELETEBYNAME;
	    root["name"] = st.name;
	}
	else if (st.msgty == ADDITEM)
	{
		cout<<"over in 227 "<<endl;
	}
	else if (st.msgty == QUERYBYNAME)
	{
    	root["msgtype"] = QUERYBYNAME;
	    root["name"] = st.name;
	}
	else if(st.msgty == EN_MSG_OFFLINE)
	{
		root["msgtype"]	= EN_MSG_OFFLINE;
	}
	else 
	{
		cout<<"error"<<endl;
	}
    int size = send(fd, root.toStyledString().c_str(),
        strlen(root.toStyledString().c_str())+1, 0);
    if(size < 0)
    {
        cout<<"send login msg fail!"<<endl;
        exit(0);
    }
    
    //接收server返回的消息
    char recvbuf[1024]={0};
    size = recv(fd, recvbuf, 1024, 0);
    if(size < 0)
    {
        cout<<"recv server login ack fail!"<<endl;
        exit(0);
    }
    cout<<"recv:" <<recvbuf<<endl;
}
