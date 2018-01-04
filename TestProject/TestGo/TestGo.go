package main

import "net"
import "fmt"

func checkError(err error,info string) (res bool) {  
      
    if(err != nil){  
        fmt.Println(info+"  " + err.Error())  
        return false  
    }  
    return true  
}  

func Handle(conn net.Conn){
	fmt.Println("accept");
	buf:=make([]byte,1024)
	for{
		length,err:=conn.Read(buf)
		if (!checkError(err,"Connection")){
			conn.Close();
			break
		}
		recviceStr:=string(buf[0:length])
		fmt.Println(recviceStr);
		conn.Write([]byte("bbbbbb"))
	}
	
}

func main(){
	fmt.Println("begin");
	service:=":9090"
	tcpAddr,_:=net.ResolveTCPAddr("tcp4",service);
	l,_:=net.ListenTCP("tcp",tcpAddr);

	for{
		conn,_:=l.Accept()
		go Handle(conn)
	}
}