#ifndef __MY_HEAD__
#define __MY_HEAD__
#include <pcap.h>

// 所有包都派生自这个类, 解析包
class Head_Super{
public:
	// 指向更高层协议
	Head_Super* next;

	// 从 pkt_data 中抽取出这层协议PDU的信息
	virtual void analysis(u_char *pkt_data)=0;

	// 将这层协议的详细信息以一个字符串表现出来
	virtual CString my_print()=0;
};

class Head_Ethernet : public Head_Super{
public:
	u_char S_Mac[6];
	u_char D_Mac[6];
	u_char kind[2];   //0800:IP  0806:ARP
	void analysis(u_char *pkt_data);
	CString my_print();
};

class Head_802_3 : public Head_Super{
public:
	u_char S_Mac[6];
	u_char D_Mac[6];
	u_char kind[2];   //0800:IP  0806:ARP
	void analysis(u_char *pkt_data);
	CString my_print();
};

class Head_ARP : public Head_Super{
public:
	u_char op[2];  //require or answer
	u_char S_Mac[6];
	u_char S_IP[4];
	u_char D_Mac[6];
	u_char D_IP[4];
	void analysis(u_char *pkt_data);
	CString my_print();
};

class Head_IP : public Head_Super{
public:
	int version;	//不能取IP首部第一个字节，只能取前4位
	int len;		//取接下来的4位
	u_char sign[2];	//标识符
	u_char TTL;		//存活时间
	int protocol;
	u_char S_IP[4];
	u_char D_IP[4];
	void analysis(u_char *pkt_data);
	CString my_print();
};

class Head_ICMP : public Head_Super{
public:
	int kind;
	int code;
	void analysis(u_char *pkt_data);
	CString my_print();
};

class Head_UDP : public Head_Super{
public:
	u_char S_Port[2];
	u_char D_Port[2];
	void analysis(u_char *pkt_data);
	CString my_print();
};

class Head_IGMP : public Head_Super{
public:
	int version; // should be 3
	u_char type;
	u_char Multicast[4];
	void analysis(u_char *pkt_data);
	CString my_print();
};

class Head_TCP : public Head_Super{
public:
	u_char S_Port[2];
	u_char D_Port[2];
	u_char SYN[4];
	u_char ACK[4];
	u_char Size_Window[2];
	int len;
	void analysis(u_char *pkt_data);
	CString my_print();
};

class Head_IPv6 : public Head_Super{
public:
	int version;
	int protocol;
	int extern_len;
	int sign;						//用于标记是否有扩展首部
	u_char S_IPv6[16];
	u_char D_IPv6[16];
	void analysis(u_char *pkt_data);
	CString my_print();
};

class Head_OSPF : public Head_Super{
public:
	int version;
	int type;
	u_char Router_ID[4];
	u_char Area_ID[4];
	void analysis(u_char *pkt_data);
	CString my_print();
};

class Head_DNS : public Head_Super{
public:
	u_char ID[2];
	int Question;
	void analysis(u_char *pkt_data);
	CString my_print();
};

class Head_HTTP : public Head_Super{
public:
	void analysis(u_char *pkt_data);
	CString my_print();
};

class Head_FTP : public Head_Super{
public:
	void analysis(u_char *pkt_data);
	CString my_print();
};
#endif