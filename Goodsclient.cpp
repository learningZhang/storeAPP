#include "client.h"

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        cout<<"input ./client port"<<endl;
        return -1;
    }

    int port=0;
    port = atoi(argv[1]);
    int clientfd;
    clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if(clientfd == -1)
    {
        cout<<"clientfd create fail!"<<endl;
        return -1;
    }
    
    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    if(-1 == connect(clientfd, (sockaddr*)&server, sizeof(server)))
    {
        cout<<"connect server fail!"<<endl;
        return -1;
    }

    int choice = 0;
    bool bloginsuccess = false;
    while(!bloginsuccess)
    {
        cout<<"============"<<endl;
        cout<<"0.login"<<endl;
        cout<<"1.register"<<endl;
        cout<<"2.exit"<<endl;
        cout<<"4.QUERYBYNAME"<<endl;
        cout<<"5.QUERYBYID"<<endl;
        cout<<"6.ADDITEM"<<endl;
        cout<<"7.DELETEBYNAME"<<endl;
        cout<<"8.DELETEBYID"<<endl;
        cout<<"9.SALEITEM"<<endl;
        cout<<"============"<<endl;
        cout<<"choice:";
        cin>>choice;
        cin.get();
        switch(choice)
        {
            case EN_MSG_LOGIN:
            {
	            if(doLogin(clientfd))
	            {
	                bloginsuccess = true;  
		cout<<"welcome o beijing"<<endl;
	            }
	            else
	            {
	                cout<<"login fail!name or pwd is wrong!"<<endl;
	            }  
			}

            continue;
            
            case EN_MSG_REGISTER:
            	doregister(clientfd);
            continue;
            
            case EN_MSG_OFFLINE:
		        cout<<"bye bye..."<<endl;
			offline(clientfd);
		        exit(0);
	           	break;
	           	          
            case QUERYBYNAME:        //通过姓名查询信息
	            queryByName(clientfd);break;
	              
    		case QUERYBYID:          //通过id查询信息
    			queryById(clientfd);break;
    			
    		case ADDITEM:         //增加项目
    			addItem(clientfd);break;
    			
    		case DELETEBYNAME:      //通过名字进行删除
    			deleteByName(clientfd);break;
    			
    		case DELETEBYID:       //通过id进行删除
				deleteById(clientfd);break;
				
    		case SALEITEM: //数据库增加物品
	    		saleItem(clientfd);break;
	    	break;
	    	
            default:
	            {
                	cout<<"invalid input!"<<endl;
            		continue;
        		}
        }
    }
    cout<<"welcome to beijing!"<<endl;
    return 0;
}
