#include "mysqlGoods.h"

//商品编号，商品名称，购买使用时间，新旧程度，地址，出厂地址，预算

//设计的是商场中的商品
//create database Goods;
//create table goods(id char(20), name char(20), buytime char(20), degree char(10),myaddre char(30), goodsaddre, money int);

CMysql::CMysql()
{
	ip = "127.0.0.1";
	port = 3306;
	user = "root";
	passwd = "xuanyu";
	pcon = mysql_init((MYSQL*)0);
	if (mysql_real_connect(pcon, ip, user, passwd, NULL, port, NULL, 0) == NULL)
	{
		cout<<"connect error"<<endl;
		exit(-1);
	}
    
	if(mysql_select_db(pcon, "Goods"))
	{
		cout<<"select database error!"<<endl;
		exit(-1);
	}
}

//插入用户，用于登录
bool CMysql::insertIntoUser(const char *name, const char *passwd, const char *calling)
{
	char sql[100];
	sprintf(sql, "insert into user values('%s', '%s', '%s')", name, passwd, calling);
	if (mysql_real_query(pcon, sql, strlen(sql)))
	{
		return true;
	}
	return false;
}

//goods(id char(20), name char(20), buytime char(20), degree char(10),myaddre char(30), goodsaddre, money int);
///插入商品
//_
bool CMysql::insertIntoMessage(const char*id,const char*name,const char *buytime,const char*degree,const char*myaddre,const char*goodsaddre,int money)//+time
{
	char sql[1024];
	sprintf(sql, "insert into goods values('%s', '%s', '%s', '%s', '%s', '%s', %d)", id,name,buytime,degree,myaddre,goodsaddre,money);
	if (!mysql_real_query(pcon, sql, strlen(sql)))
	{
		return true;
	}
	return false;
}

//删除商品---根据id
bool CMysql::delInMessageByID(const char *id)
{
	char sql[100];
	sprintf(sql, "delete from goods where id='%s'", id);
	if(!mysql_real_query(pcon, sql, strlen(sql)))
	{
		return true;
	}
	return false;
}

//删除商品---根据商品名称
bool CMysql::delInMessageByName(const char *name)
{
 
	char sql[100];
	sprintf(sql, "delete from goods where name='%s'", name);
	if(!mysql_real_query(pcon, sql, strlen(sql)))
	{
		return true;
	}
	return false;
}

//goods(id char(20), name char(20), buytime char(20), degree char(10),myaddre char(30), goodsaddre, money int);

//根据姓名找到商品
bool CMysql::findMessageByName(const char* name, char *message, int length)
{
	char sql[100];
	sprintf(sql, "select* from goods where name='%s'", name);
	if (mysql_real_query(pcon, sql, strlen(sql)))
	{//if success will return 0,if fail no 0
		cout<<mysql_error(pcon)<<endl;		
		return false;
	}

	if ((pres=mysql_store_result(pcon)) != NULL)
	{
		if ((row=mysql_fetch_row(pres)) != NULL)
		{
			int lenth =strlen(row[0]);
			if (length > lenth)
			{
				strcpy(message, row[0]); 
				strcat(message, "-");//通过分割号来分开
				strcat(message, row[1]);
				strcat(message, "-");//通过分割号来分开
				strcat(message, row[2]);
				strcat(message, "-");//通过分割号来分开
				strcat(message, row[3]);
				strcat(message, "-");//通过分割号来分开
				strcat(message, row[4]);
				strcat(message, "-");//通过分割号来分开
				strcat(message, row[5]);
				strcat(message, "-");//通过分割号来分开
				strcat(message, row[6]);
			}
			else
			{
				return false;
			}
			return true;
		}
		if (mysql_error(pcon) != NULL)
		{
			cout<<mysql_error(pcon)<<endl;
		}
	}
	mysql_free_result(pres);
	return false;	
}

//根据商品id找到商品
bool CMysql::findMessageByID(const char* id, char *message, int length)
{
	char sql[100];
	sprintf(sql, "select* from goods  where id='%s'", id);
	if (mysql_real_query(pcon, sql, strlen(sql)))
	{
		cout<<mysql_error(pcon)<<endl;		
		return false;
	}
	if ((pres=mysql_store_result(pcon)) != NULL)
	{
		if ((row=mysql_fetch_row(pres)) != NULL)
		{
			int lenth =strlen(row[0]);
			if (length > lenth)
			{
				strcpy(message, row[0]); 
				strcat(message, "-");//通过分割号来分开
				strcat(message, row[1]);
				strcat(message, "-");//通过分割号来分开
				strcat(message, row[2]);
				strcat(message, "-");//通过分割号来分开
				strcat(message, row[3]);
				strcat(message, "-");//通过分割号来分开
				strcat(message, row[4]);
				strcat(message, "-");//通过分割号来分开
				strcat(message, row[5]);
				strcat(message, "-");//通过分割号来分开
				strcat(message, row[6]);
			}
			else
			{
				return false;
			}
			return true;
		}
		if (mysql_error(pcon) != NULL)
		{
			cout<<mysql_error(pcon)<<endl;
		}
	}
	mysql_free_result(pres);
	return false;	
}

//从列表中获得该passwd,然后与passwd进行比较
bool CMysql::queryPasswd(const char *name, const char *passwd)
{
	char sql[100];
	sprintf(sql, "select name, passwd from user where name='%s'", name);
	if (mysql_real_query(pcon, sql, strlen(sql)))
	{
		cout<<mysql_error(pcon)<<endl;
		return -2;
	}
	
	if ((pres = mysql_store_result(pcon)) != NULL)//将结果保存于pres中
	{
		if ((row = mysql_fetch_row(pres)) != NULL)//array or false
		{
			if( strcmp(row[1],passwd) == 0 )
			{
				mysql_free_result(pres);
				return true;
			}
		}
		if (mysql_error(pcon) != NULL)
		{
			cout<<mysql_error(pcon)<<endl;	
		}
	}
	mysql_free_result(pres);
	return false;
}

bool CMysql::deleteUser(const char *name, int tag)
{
	char sql[100];
	if (tag == 1)
	{
		sprintf(sql, "delete from state where user = %d", name);
	}
	else
	{
		sprintf(sql, "delete from state");
	}
	
	int res = mysql_real_query(pcon, sql, strlen(sql));//成功返回0
	if (!res)
	{
		return true;
	}
	return false;
}

