    bool initialization_server()
    {
        WSADATA wsa;
        if(WSAStartup(514,&wsa)!=0) //514 means to initialize the latest version of winsock library
                                //this is dynamically load library function
        {
            fprintf(stderr,"WinSock initialization failed: %d\n",WSAGetLastError());
            return 1;
        }
        SetConsoleCtrlHandler(HandlerRoutine,TRUE);
        printf("Initialised\n");
        if(this->read_from_server_config_ini()==1) return 1;
        printf("Server local address at: %s\nLocal port at: %s\n",this->server_ip,this->server_port);
        printf("Data download timeout: %zd seconds\n",this->data_download_timeout);


        struct addrinfo hints;
        ZeroMemory(&hints, sizeof(hints));
        hints.ai_family = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        hints.ai_flags = AI_PASSIVE;

        if(getaddrinfo((const char*)this->server_ip,(const char*)this->server_port,&hints,&this->result)!=0)
        {
            fprintf(stderr,"Error while converting address and port: %d",WSAGetLastError());
            return 1;
        }

        this->listen_socket0 = socket(this->result->ai_family,this->result->ai_socktype,this->result->ai_protocol);
        if((this->listen_socket0) == INVALID_SOCKET)
        {
            fprintf(stderr,"Could not create socket: %d",WSAGetLastError());
            return 1;
        }
        printf("Socket created\n");

        if(bind(this->listen_socket0,this->result->ai_addr,this->result->ai_addrlen)==SOCKET_ERROR)
        {
            fprintf(stderr,"Binding socket with ip and port failed with error: %d", WSAGetLastError());
            return 1;
        }
        printf("Binding success\n");
        if(this->is_anonymous=='0')
        {
            printf("Server created\n\n");
            printf("Allowed ip:\n");
            for(int i = 0; i<this->allowed_ip_counter; i++)
            {
                printf("%d.%d.%d.%d\n",*((uint8_t*)((uint32_t*)&this->allowed_ip[i])),
                       *((uint8_t*)((uint32_t*)&this->allowed_ip[i])+1),
                       *((uint8_t*)((uint32_t*)&this->allowed_ip[i])+2),
                       *((uint8_t*)((uint32_t*)&this->allowed_ip[i])+3));
            }
            printf("\n");
        }
        else printf("Server created\n\n");
        return 0;
    }