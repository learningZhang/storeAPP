#include "mysqlGoods.h"

int main()
{
	CMysql db;
	char *name="shubao";
	char *id ="001";
	char *buytime="2001";
	char *degree ="5new";
	char *myaddre = "sust";
	char *goodsaddre = "china";
	int money=10;

	
		///插入商品
	//bool tag = db.insertIntoMessage(id,name,buytime,degree,myaddre,goodsaddre,money);
	//if (tag == false) cout<<"cuoe";	
	//删除商品---根据id
	//db.delInMessageByID(id);

		//删除商品---根据商品名称
	//db.delInMessageByName("1");

		//根据姓名找到商品
	bool tag = false;	
	char *message = (char *)malloc(1024);
	int length = 100;
	tag = db.findMessageByName(name, message, length);
	cout<<message;
	if (tag == true) cout<<"okkkkkk";

	memset(message, 0, 1024);
	tag = db.findMessageByID(id, message,length);
	if (tag == true) cout<<"two okkk";
	cout<<message;
	
	
/*	if (!db.insertIntoUser(name, passwd, email))
		cout<<"insert error"<<endl;
	
	if (!db.queryPasswd(name, passwd))
		cout<<"passwd query error"<<endl;

	if (!db.deleteUser(name))
		cout<<"delete error"<<endl;

	int fd =100;
	if (!db.insertIntoStates(name, fd))
		cout<<"insert into states error"<<endl;

	int x = 0;
	if((x=db.getStates(name)) == -1)
		cout<<"getStates error"<<endl;
	cout<<"fd is "<<x<<endl;
///
	if(!db.deleteElemBySocket(fd, 1))
	{
		cout<<"delete error"<<endl;
	}

	char *msg = "nizhoa";
	if (!db.insertIntoMessage("zhang", "wang", msg))//from to msg
	{
		cout<<"error in insert into Mesg"<<endl;
	}
*//*
	char *temp=NULL;
	if ((temp = db.findMesgByName("wanug")) == NULL)
	{
		cout<<"find error"<<endl;
	}
	else
	{
		cout<<temp<<endl;free(temp);
	}

//	if(!db.delInMessage("wang"))
//	{
//		cout<<"error in delMessage"<<endl;
//	}
*/	
	cout<<"ending"<<endl;
}
