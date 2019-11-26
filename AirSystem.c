#include <stdio.h>																			//standard function header
#include <string.h>																			//string function header
#include <stdlib.h>																			//system fuction header

typedef struct flight flight;																//redefinition apartment for flight list makes structs nesting successfully
typedef struct client client;																//redefinition apartment for client list makes structs nesting successfully
flight *HF = 0,*PF = 0,*NF = 0,*RF = 0;														//HF--Head of Flight list,PF--free Point of Flight,NF--init New Flight,RF--Recall Flight
client *HC = 0,*PC = 0,*NC = 0,*RC = 0;														//HC--Head of Client list,PC--free Point of Clienr,NC--init New Client,RC--Recall Client
FILE *F,*C;																					//initialize file address pointer F--flight,C--client
struct flight 																				//structure flight list
{
	char flightname[10];																	//characters of flightname
	short deprature,destination,price,seats,books;											//deprature/destination/seats/bookedtickets of flight
	long date;		 																		//the date of flight
	client *head;																			//the head of client in this flight list
	flight *next;																			//connect point to next flight in all library
};
struct client																				//structure client list
{
	char flightname[10],clientname[8];														//characters flightname and clientname
	long id;																				//identify of  client
	short tickets;																			//tickets client book
	client* next;																			//connect point to next client in this
};
void Touch()																				//function to make sure depends flies' alive
{
	F = fopen("flight","ab+"); 					 											//get int touch while flies alive or make one
	fclose(F);																				//save and dismiss file
	C = fopen("client","ab+");																//get int touch while flies alive or make one
	fclose(C);																				//save and dismiss file
}
char* Library(short place)																	//words library function,trainslate place number to characters
{
	switch(place)																			//place number judging
	{
		case 1 : return "BeiJing";break; 													//return the address of string "Beijing"
		case 2 : return "ShangHai";break;													//return the address of string "ShangHai"
		case 3 : return "Canton";break;														//return the address of string "Canton"
		case 4 : return "ShengZhen";break;													//return the address of string "ShenZhen"
		case 5 : return "WuHan";break;														//return the address of string "WuHan"
		case 6 : return "Hongkong";break;													//return the address of string "HongKong"
		default : return "Unknown";break;													//format other low frequent place number
	}
}
void LoadFlight()																			//laoding flights list
{
 	F = fopen("flight","rb");																//open file and send head address to pointer
	PF = HF;																				//move PF to HF
	NF = (flight*) malloc(sizeof(flight));													//creat a new room in format structure flight from RAM and send address to pointer NF
	fread(NF,sizeof(flight),1,F);															//read btyes data from address in LF to address in NF,LF move to next address
	while(!feof(F))																			//judging file flight ending or not,break loop when ending
	{
		if(HF==0){HF = NF;PF = NF;}															//make NF to be head of flight list and move PF to NF
		PF->next = NF;PF = PF->next;														//connect NF to flight list and move PF to NF
		NF = (flight*) malloc(sizeof(flight));												//creat a new room in format structure flight from RAM and send address to pointer NF
		fread(NF,sizeof(flight),1,F);														//read btyes data from address in LF to address in NF,LF move to next address
		PF->next = 0;PF->head = 0;PF->books = 0;											
	}
	free(NF);																				//free the RAM for NF
	fclose(F);																				//save data and close flie flight
}
int Contract()																				//function to contract client list to flight list
{
	int i;PF = HF;																			//initialize variable i,move PF to HF
	if(HF == 0)return 1;																	//
	for(i=0;i<sizeof(NC->flightname);)														//
	{
		if(NC->flightname[i]==PF->flightname[i])i++;										//
		else if (PF->next){PF = PF->next;i = 0;}											//
			else return 1;																	//
	}
	NC->next = 0;																			//
	if(PF->head==0)PF->head = NC;															//
	else {PC = PF->head;while(PC->next)PC = PC->next;PC->next = NC;}						//
	PF->books += NC->tickets;																//
	return 0;																				//
}
void LoadClient()																			//Loading Clients Info 
{
	C = fopen("client","rb+");																//
	PF = HF;																				//
	NC = (client*) malloc(sizeof(client));													//creat a new room in format structure client from RAM and send address to pointer NC
	fread(NC,sizeof(client),1,C);															//
	while(!feof(C))																			//
	{
		Contract();																			//
		NC = (client*) malloc(sizeof(client));												//creat a new room in format structure client from RAM and send address to pointer NC
		fread(NC,sizeof(client),1,C);														//
	}
	free(NC);																				//free the NC from RAM
	fclose(C);																				//
}
void DownFlight()																			//
{
	F = fopen("flight","wb");																//
	PF = HF;																				//
	while(PF)																				//
	{
		fwrite(PF,sizeof(flight),1,F);														//
		PF = PF->next;																		//
	}
	fclose(F);																				//
}
void DownClient()																			//
{
	C = fopen("client","wb");																//
	PF = HF;																				//
	while(PF)																				//
	{
		PC = PF->head;																		//
		while(PC)																			//
		{
			fwrite(PC,sizeof(client),1,C);													//
			PC = PC->next;																	//
		}
		PF = PF->next;																		//
	}
	fclose(C);																				//
}
void Anykey()																				//
{
	printf("\nType Anykeys To Continue:");getchar();getchar();								//
}
void ShowFlight()																			//
{
	int i;																					//init variable i
	for(i=0;i<sizeof(PF->flightname);i++)putchar(PF->flightname[i]);						//
	printf("\t%s\t\t%s\t%ld\t%hd\t%hd\t%hd\t\n",Library(PF->deprature),Library(PF->destination),PF->date,PF->price,PF->seats,PF->books);//
}
void ShowClient()																			//
{
	int i;																					//init variable i
	for(i=0;i<sizeof(PC->flightname);i++)putchar(PC->flightname[i]);putchar('\t');			//
	for(i=0;i<sizeof(PC->clientname);i++)putchar(PC->clientname[i]);						//
	printf("\t%ld\t%hd\t\n",PC->id,PC->tickets);											//
}
void AllFlights()																			//
{
	printf("FlightName\tdeprature\tdestination\tDate\tPrice\tSeats\tBooks\n");				//
	if((PF = HF) == 0){printf("\tError:No Flight!\n");return;}								//
	while(PF)																				//
	{
		ShowFlight();																		//
		PF = PF->next;																		//
	}
} 
void AllClients()																			//
{
	int i;																					//init variable i
	if((PF = HF) == 0){printf("\tError:No Flight!\n");return;}								//
	printf("FlightName\tClientName\tIdentify\tTickets\n");									//
	while(PF)																				//
	{
		PC = PF->head;																		//
		if(PC==0)																			//
		{
			for(i=0;i<sizeof(PF->flightname);i++)											//
			putchar(PF->flightname[i]);														//
			printf("\tNo Client In This Flight!");											//
		}
		while(PC)																			//
		{
			ShowClient();																	//
			PC = PC->next;																	//
		}
		PF = PF->next;																		//
		putchar('\n');																		//
	}
} 
void AddFlight()																			//
{
	int i;PF = HF;																			//init variable i
	NF = (flight*) malloc(sizeof(flight));													//
	printf("Please Enter FlightName:\n");scanf("%s",NF->flightname);						//
	for(i=strlen(NF->flightname);i<sizeof(NF->flightname);i++)NF->flightname[i] = ' ';		//
	printf("Please Enter FlightDate/Seats/Price:\n");scanf("%ld%hd%hd",&NF->date,&NF->seats,&NF->price);//
	printf("Please Enter FlightDeprature/FlightDestination:\n1--BeiJing.2--ShangHai.3--Canton.4--ShenZhen.5--WuHan.6--HongKong\n");//
	scanf("%hd%hd",&NF->deprature,&NF->destination); 										//
	NF->next = 0;NF->head = 0;NF->books = 0;												//
	if(HF == 0)	{HF=NF;HF->books = 0;return;}												//
	while(PF->next)PF = PF->next;															//
	PF->next = NF;PF = PF->next;															//
}
void AddClient()																			//
{
	int i;																					//
	NC = (client*) malloc(sizeof(client));													//creat a new room in format structure client from RAM and send address to pointer NC
	printf("Please Enter FlightName:\n");scanf("%s",&NC->flightname);						//
	for(i=strlen(NC->flightname);i<sizeof(NC->flightname);i++)NC->flightname[i] = ' ';		//
	printf("Please Enter ClientName\n"); scanf("%s",&NC->clientname);						//
	for(i=strlen(NC->clientname);i<sizeof(NC->clientname);i++)NC->clientname[i] = ' ';		//
	printf("Please Enter ID:\n");															//
	scanf("%ld",&NC->id);																	//
	printf("Please Enter Number Of Tickets:\n");											//
	scanf("%ld",&NC->tickets);																//
	printf("FlightName\tClientName\tIdentify\tTickets\n");									//
	i = Contract();																			//
	if(i == 1)printf("\tError:No Such Flight\n");											//
	printf("\tAdding Successfully!\n");														//
}
int SearchFlight()																			//
{
	int i;char flightname[sizeof(NF->flightname)];RF = PF = HF;								//
	printf("Please Enter FlightName:\n");scanf("%s",flightname);							//
	for(i=strlen(flightname);i<sizeof(flightname);i++)flightname[i] = ' ';					//
	printf("FlightName\tdeprature\tdestination\tDate\tPrice\tSeats\tBooks\n");				//
	if(HF == 0){printf("\tNo Such Flight!\n");return 1;}									//
	for(i=0;i<sizeof(flightname);)															//
	{
		if(flightname[i] == PF->flightname[i])i++;											//
		else if (PF->next){i = 0;RF = PF;PF = PF->next;}									//
			else {printf("\tNo Such Flight!\n");return 1;}									//
	}
	ShowFlight();																			//
}
short SearchClient()																		//
{
	int i;long Identify=0;PF = HF;															//init variable i
	printf("Please Enter Client ID\n");scanf("%ld",&Identify);								//
	printf("FlightName\tClientName\tIdentify\tTickets\n");									//
	while(PF)																				//
	{
		RC = PF->head;PC = PF->head;														//
		while(PC)																			//
		{
			if(Identify==PC->id){ShowClient();return 0;}									//
			RC = PC;PC = PC->next;															//
		}
		PF = PF->next;																		//
	}
	printf("\tError:No Such Client!\n");return 1;											//
}
void DeleteFlight()																			//
{
	int i;																					//init variable i
	i = SearchFlight();																		//
	if(i == 1)return;																		//
	printf("\nConfirm To Delete?(1/0):");scanf("%d",&i);									//
	if(i == 1)																				//
	{
		if((HF->next)&&(HF!=PF))RF->next = PF->next;										//
		else HF = HF->next; 
		free(PF);
	}
	else printf("Operate Canceled!");
}
void DeleteClient()
{
	int i;																					//init variable i
	i = SearchClient();
	if(i == 1)return;
	printf("\nConfirm To Delete?(1/0):");scanf("%d",&i);
	if(i == 1)
	{
		PF->books -= PC->tickets;
		if(PF->head == PC)PF->head = PC->next;
		else RC->next = PC->next;
		free(PC);
	}
	else printf("Operate Canceled!");
}
int Sudo()
{
	int i;																									//init variable i
	printf("Please Enter Passwords:");scanf("%d",&i);
	if(i == 325)
	{
		printf("Pass!\n");
		return 0;
	}
	else printf("Wrong Keys!\n");
	return 1;
}
void FlightOperate()
{
	int i;																				//initialize variable i
	do
	{
		for(i=0;i<40;i++)putchar('*');
		printf("\n\tFlight Operate interface\n");
		for(i=0;i<40;i++)putchar('-');
		printf("\n\t1.Show All Flights\n\t2.Query Flight\n\t3.Add Flight\n\t4.Delete Flight\n\t0.Return\n");
		for(i=0;i<40;i++)putchar('-');
		printf("\nPlease Input Operations Number:");scanf("%d",&i); 
		switch(i)
		{
			case 1 : AllFlights();break;
			case 2 : SearchFlight();break;
			case 3 : (Sudo())?:AddFlight();break;
			case 4 : (Sudo())?:DeleteFlight();break;
		}
		Anykey();
	}
	while(i);
}
void ClientOperate()
{
	int i;																										//initialize variable i
	do
	{
		for(i=0;i<40;i++)putchar('*');
		printf("\n\n\tClient Operate interface\n");
		for(i=0;i<40;i++)putchar('-');
		printf("\n\t1.Show All Clients\n\t2.Query Client\n\t3.Booking Tickets\n\t4.Return Tickets\n\t0.Return\n");
		for(i=0;i<40;i++)putchar('-');
		printf("\nPlease Input Operations Number:");scanf("%d",&i);
		switch(i)
		{
			case 0 : break;
			case 1 : AllClients();break;
			case 2 : SearchClient();break;
			case 3 : AddClient();break;
			case 4 : DeleteClient();break;
		}
		Anykey();
	}
	while(i);
}
int main()
{
	int i;																							//init variable i
	for(i=0;i<sizeof(double);i++)putchar('*');
	printf("System Of Flights Booking");
	for(i=0;i<sizeof(double);i++)putchar('*');
	printf("\n\nProgram Initializing£¬Please Wating...\nSource Flies Path...");Touch();
	printf("Done\nLoading Flightslist...");LoadFlight();
	printf("Analysised\nLoading Clientslist...");LoadClient();
	printf("Analysised\n\nEntering System\n");
	for(i=0;i<40;i++)putchar('*');
	printf("\n\tWelcome To Our System\t\n");
	do
	{
		for(i=0;i<40;i++)putchar('*');
		printf("\n\tHomePage\n");
		for(i=0;i<40;i++)putchar('-');
		printf("\n\t1.Flight Operate\n\t2.Client Operate\n\t0.Save And Exit Program\t\n");
		for(i=0;i<40;i++)putchar('-');
		printf("\n\nPlease Input Operations Number:");scanf("%d",&i); 
		switch(i)
		{
			case 0 : break;																								//key to end loop
			case 1 : putchar('\n');FlightOperate();break;																//key to operate flight
			case 2 : putchar('\n');ClientOperate();break;																//ket to operate client
		}
	}
	while(i);																											//judging end loop flag
	printf("\nUpdate Flightslist To Depends Flies...");DownFlight();													//
	printf("Done\nUpdate Clientslist To Depends Flies...");DownClient();												//
	printf("Done\n\nThanks For Using,Goodbye£¡");																		//
} 
