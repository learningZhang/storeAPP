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

		///������Ʒ
		bool insertIntoMessage(const char*id,const char*name,const char *buytime,const char*degree,const char*myaddre,const char*goodsaddre,int money);//+time	return false;

		//ɾ����Ʒ---����id
		bool delInMessageByID(const char *id);

		//ɾ����Ʒ---������Ʒ����
		bool delInMessageByName(const char *name);

		//���������ҵ���Ʒ
		bool findMessageByName(const char* name, char *message, int length);
		//������Ʒid�ҵ���Ʒ
		bool findMessageByID(const char* id, char *message, int length);
	
		//���б��л�ø�passwd,Ȼ����passwd���бȽ�
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
