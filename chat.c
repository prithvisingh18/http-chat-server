#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

struct user{
  char * username;
  int no;
};
void makeset(int s[],int size)
{
  for(int i = 0;i < size ; i++)
  {
    s[i] = i;
  }
}

int find(int s[],int size ,int x)
{
  if(!(x >= 0 && x < size))
  {
    return -1;
  }
  if(s[x] == x)
  {
    return x;
  }
  else
  {
    return find(s,size,s[x]);
  }
}
void Union(int s[],int size,int root1 , int root2)
{
  if(find(s,size,root1) == find(s,size,root2))
  {return;}
  if(!((root1 >= 0 && root1 < size) && (root2 >= 0 && root2 < size)))
  {return;}
  s[root1] = root2;
}
void print_array(int s[],int size)
{
  for(int i = 0;i < size;i++)
  {
    printf("%d  ",s[i]);
  }
  printf("\n");
}
void init_server()
{
  //Send data to others, on the network
  //Get info about other chat
  int listener_d = socket(PF_INET, SOCK_STREAM, 0);
  struct sockaddr_in name;
  name.sin_family = PF_INET;
  name.sin_port = (in_port_t)htons(30000);
  name.sin_addr.s_addr = htonl(INADDR_ANY);

  if(listener_d == -1)
  {
    printf("Error : Cannot initialize server");
  }
    printf("Server Initialized \nBinding to a port ...");
    if(bind(listener_d , (struct sockaddr *) &name, sizeof(name)) == -1)
      printf("Cannot bind to socket");
    if(listen(listener_d, 10) == -1)
    {
        printf("Cannot Listen");
    }
    struct sockaddr_storage client_addr;
    unsigned int address_size = sizeof(client_addr);
    int connect_d = accept(listener_d, (struct sockaddr*) &client_addr, &address_size);
    if(connect_d == -1)printf("Cannot open secondary socket");
    char *msg = "Prithvi \n";
    if(send(connect_d, msg, strlen(msg),0) == -1)
      printf("Error Sending MSG");

  
}
int main()
{
	init_server();
	return 0;
}
