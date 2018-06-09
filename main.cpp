#include"MCTS.h"

//a function for destroy node
void destroy_node(MCTSnode *root)
{
	for (unsigned int i = 0; i < root->children.size(); i++)
	{
		destroy_node(root->children[i]);
	}
	delete root;
}

//destroy the tree
void destroy_tree(MCTStree *T)
{
	destroy_node(T->root);
	delete T;
}

//change the root of the T according to the received data from the network
MCTStree* cmp_access(MCTStree *T, chess &src)
{
	//if the state is the same, do nothing
	if (T->root->get_state().equal(src))
		return T;
	std::vector<MCTSnode*> vec = T->root->get_children();
	//if no children, delete the tree and create a new
	if (vec.size() == 0)
	{
		destroy_tree(T);
		return new MCTStree(src, src.get_turn());
	}
	int index = -1;
	for (int i = 0; i < vec.size(); i++)
	{
		if (vec[i]->get_state().equal(src))
		{
			index = i;
			break;
		}
	}
	//cannot find the state, delete the tree and create a new
	if (index == -1)
	{
		/*for (int i = 0; i < vec.size(); i++)
		{
			destroy_node(vec[i]);
		}
		delete T->root;*/
		destroy_tree(T);
		return new MCTStree(src, src.get_turn());
	}
	//find the state, delete other node and access
	for (int i = 0; i < vec.size(); i++)
	{
		if(i != index)
			destroy_node(vec[i]);
	}
	delete T->root;
	T->root = vec[index];
	T->root->father = nullptr;
	return T;
}

char* create_session(int clientSocket)
{
    int ret, i, h;
    char str1[4096], str2[4096], *buf, *str;
    socklen_t len;
    fd_set   t_set1;
    struct timeval  tv;

	buf = (char *)malloc(BUFSIZE);
    str = (char *)malloc(128);
 
    memset(str1, 0, 4096);
    strcat(str1, "GET /create_session/7 HTTP/1.1\n");
    strcat(str1, "Host: 47.89.179.202:5000\n");
    strcat(str1, "Content-Type: text/html\n");
    strcat(str1, "Content-Length: ");
    strcat(str1, str);
    strcat(str1, "\n\n");
    printf("%s\n",str1);
 
    ret = write(clientSocket,str1,strlen(str1));
    if (ret < 0) {
        printf("发送失败!错误代码是%d,错误信息是'%s'\n",errno, strerror(errno));
        exit(0);
    }
    else {
        printf("消息发送成功，共发送了%d个字节!\n\n", ret);
    }
 
    FD_ZERO(&t_set1);
    FD_SET(clientSocket, &t_set1);
 
    while(1) {
        sleep(2);
        tv.tv_sec = 0;
        tv.tv_usec = 0;
        h = 0;
        printf("--------------->1");
        h = select(clientSocket +1, &t_set1, NULL, NULL, &tv);
        printf("--------------->2");
 
        //if (h == 0) continue;
        if (h < 0) {
            close(clientSocket);
            printf("在读取数据报文时SELECT检测到异常,该异常导致线程终止!\n");
            return -1;
        };
 
        if (h > 0) {
            memset(buf, 0, 4096);
            i = read(clientSocket, buf, 4095);
            if (i == 0) {
                close(clientSocket);
                printf("读取数据报文时发现远端关闭,该线程终止!\n");
                return -1;
            }
            printf("%s\n", buf);
        }
    }
    return buf;
}

void move(int clientSocket, char* x_pos, char* y_pos, char* player)
{
    int send_num;
    char recv_buf [4096];
    char str1[4096];
    char stm[4096];
    strcat(stm, x_pos);
    strcat(stm,"/");
    strcat(stm, y_pos);
    strcat(stm, "/");
    strcat(stm, player);
    while (1)
    {
        printf("begin send\n");
        memset(str1,0,4096);
        strcat(str1, "POST move/"); 
        strcat(str1, stm);
        strcat(str1, "HTTP/1.1\r\n");
        strcat(str1, "Host: 47.89.179.202:5000\r\n");
        strcat(str1, "Content-Length: \r\n");
        strcat(str1, "Content-Type: text/html\r\n");
        strcat(str1, "\r\n");
        printf("str1 = %s\n",str1);
        send_num = send(clientSocket, str1, strlen(str1), 0);
        if (send_num < 0)
        {
            perror("send error");
            exit(1);
        }
        else
        {
            printf("send successful\n");
            printf("begin recv:\n");
            int recv_num = recv(clientSocket, recv_buf, sizeof(recv_buf),0);
            if (recv_num < 0) {
                perror("recv");
                exit(1);
            } 
            else {
                printf("recv sucess:%s\n",recv_buf);
            }
         }
        break;
    }
}

char* last_pos(int clientSocket)
{
    int ret, i, h;
    char str1[4096], str2[4096], *buf, *str;
    socklen_t len;
    fd_set   t_set1;
    struct timeval  tv;
    buf = (char *)malloc(BUFSIZE);
    str = (char *)malloc(128);
 
    memset(str1, 0, 4096);
    strcat(str1, "GET /board_string/7 HTTP/1.1\n");
    strcat(str1, "Host: 47.89.179.202:5000\n");
    strcat(str1, "Content-Type: text/html\n");
    strcat(str1, "Content-Length: ");
    strcat(str1, str);
    strcat(str1, "\n\n");
    printf("%s\n",str1);
 
    ret = write(clientSocket,str1,strlen(str1));
    if (ret < 0) {
        printf("发送失败!错误代码是%d,错误信息是'%s'\n",errno, strerror(errno));
        exit(0);
    }
    else {
        printf("消息发送成功,共发送了%d字节!\n\n", ret);
    }
 
    FD_ZERO(&t_set1);
    FD_SET(clientSocket, &t_set1);
 
    while(1) {
        sleep(2);
        tv.tv_sec = 0;
        tv.tv_usec = 0;
        h = 0;
        printf("--------------->1");
        h = select(clientSocket +1, &t_set1, NULL, NULL, &tv);
        printf("--------------->2");
 
        //if (h == 0) continue;
        if (h < 0) {
            close(clientSocket);
            printf("在读取数据报文时SELECT检测到异常,该异常导致线程终止!\n");
            return -1;
        };
 
        if (h > 0) {
            memset(buf, 0, 4096);
            i= read(clientSocket, buf, 4095);
            if (i == 0) {
                close(clientSocket);
                printf("读取数据报文时发现远端关闭,该线程终止!\n");
                return -1;
            }
            printf("%s\n", buf);
        }
    } 
	return buf;
}

int main()
{
	//客户端只需要一个套接字文件描述符，用于服务器通信
    int clientSocket;
    //描述服务器的socket
    struct sockaddr_in serverAddr;
    int ret, i, h;
    char str1[4096], str2[4096], buf[BUFSIZE], *str;
    socklen_t len;
    fd_set   t_set1;
    struct timeval  tv;
    if((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
        return 1;
    }
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(SERVER_PORT);
    //指定服务器端的ip,本地测试:127.0.0.1
    //inet_addr()函数,将点分十进制IP转换成网络字节序IP
    serverAddr.sin_addr.s_addr = inet_addr("47.89.179.202");
    if(connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        perror("connect");
        return 1;
    }
    printf("connect with destination host...\n");
	str = create_session(clientSocket);
	printf("%s",str);

	class chess c;
	MCTStree* Tree = new MCTStree(c, c.get_turn());
	MCTStree* Human;
	std::cout << "game start!\n";
	struct position pos,pos1;
	char turn = c.get_turn();
	while (!c.is_gameover())
	{
		if (turn == c.get_turn())
		{
			if((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    		{
        		perror("socket");
        		return 1;
    		}
    		serverAddr.sin_family = AF_INET;
    		serverAddr.sin_port = htons(SERVER_PORT);
    		//指定服务器端的ip,本地测试:127.0.0.1
    		//inet_addr()函数,将点分十进制IP转换成网络字节序IP
    		serverAddr.sin_addr.s_addr = inet_addr("47.89.179.202");
    		if(connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    		{
        		perror("connect");
        		return 1;
    		}
    		printf("connect with destination host...\n");

			//change root because of the enemy put
			Tree = cmp_access(Tree, c);
			std::cout << "this is ai turn: " << (int)c.get_turn() << std::endl;
			c.print();
			if (Tree->MCTSsearch(10, pos))
			{
				std::cout <<"ai pos: "<< (int)pos.row << ", " << (int)pos.col << std::endl;
				c.put(pos);
				move(clientSocket,pos.row, pos.col,c.get_turn());
				if (c.get_num() != c.get_white() + c.get_black())
				{
					std::cout << "not consistency!\n";
					system("pause");
				}
			}
			else
			{
				std::cout << "PASS" << std::endl;
        		struct position emptypos;
				c.put(emptypos);
			}
			std::cout << "AI done.\n\n";
			//change root because of my put
			Tree = cmp_access(Tree, c);
			//destroy_tree(Tree);
		}
		else
		{
			if((clientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    		{
        		perror("socket");
        		return 1;
    		}
    		serverAddr.sin_family = AF_INET;
    		serverAddr.sin_port = htons(SERVER_PORT);
    		//指定服务器端的ip,本地测试:127.0.0.1
    		//inet_addr()函数,将点分十进制IP转换成网络字节序IP
    		serverAddr.sin_addr.s_addr = inet_addr("47.89.179.202");
    		if(connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    		{
        		perror("connect");
        		return 1;
    		}
    		printf("connect with destination host...\n");
			str = last_pos(clientSocket);
			//Web Connection

			//str = last_pos(clientSocket);
			//struct position pos;
			//pos.row = str[0] - '0';
			//pos.row = str[2] - '0';
			//c.put(pos)


			/*
			printf("this is human turn: %d\n",(int)c.get_turn());
			c.print();
			std::vector<struct position> posvec = c.findall();
			if (posvec.size() == 0)
			{
				std::cout << "PASS" << std::endl;
				c.put(position());
				continue;
			}
			//random
			
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dis(0, posvec.size() - 1);
			int index = dis(gen);
			struct position humanpos = posvec[index];
			
			//local maximum
			//struct position humanpos = c.find_max(posvec);
			//printf("human pos: %d, %d\n", (int)humanpos.row, (int)humanpos.col);
			c.put(humanpos);
			std::cout << "human pos: " << (int)humanpos.row << ", " << (int)humanpos.col << std::endl;
			printf("human done!\n\n");
			*/
			Human = new MCTStree(c, c.get_turn());
			std::cout << "this is human turn: " << (int)c.get_turn() << std::endl;
			c.print();
      int row, col;
      struct position pos;
      scanf("%d%d", &row, &col);
      pos.row = row;
      pos.col = col;
      c.put(pos);
      
		}
		//Tree = new MCTStree(c, c.get_turn());
	}
	std::cout << "black is " << (int)c.get_black() << ". white is " << (int)c.get_white() << std::endl;
}
