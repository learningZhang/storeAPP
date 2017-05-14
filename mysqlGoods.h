//#ifndef _NIHAO_  
//define _NIHAO_ 1

#include <iostream>
using namespace std;
#include <mysql/mysql.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

class CMysql
{
	public:
		CMysql();
		bool insertIntoUser(const char *name, const char *passwd, const char *call);

		///插入商品
		bool insertIntoMessage(const char*id,const char*name,const char *buytime,const char*degree,const char*myaddre,const char*goodsaddre,int money);//+time	return false;

		//删除商品---根据id
		bool delInMessageByID(const char *id);

		//删除商品---根据商品名称
		bool delInMessageByName(const char *name);

		//根据姓名找到商品
		bool findMessageByName(const char* name, char *message, int length);
		//根据商品id找到商品
		bool findMessageByID(const char* id, char *message, int length);
	
		//从列表中获得该passwd,然后与passwd进行比较
		bool queryPasswd(const char *name, const char *passwd);

		bool deleteUser(const char *name, int tag);
	private:
		MYSQL *pcon;
	 	MYSQL_RES *pres;
		MYSQL_ROW row;
	 	const char *ip;
		const char *user;
		const char *passwd;
		unsigned short port;
};
