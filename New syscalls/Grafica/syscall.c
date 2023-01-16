#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
struct proc_info
{
	char proc_name[30];
	int father_pid;
	char father_name[30];
	char state[30];
};

struct space_info
{
    unsigned long code_start;
    unsigned long code_end;
    unsigned long data_start;
    unsigned long data_end;
    unsigned long heap_start;
    unsigned long heap_end;
    unsigned long stack_start;
    unsigned long stack_end;
};
struct proces
{
    int pid;
    int nice_val;
    char nume[30];
};
struct sistem {
	char nume[20];
	char versiune[10];
	char data_actualizare[70];
};
int main(int argc,char*argv[])
{
	FILE*f;
	int sys=-1;
	int pid=-1;
	if(argc>=2){
		sys=atoi(argv[1]);
	}
	if(sys==335||sys==336){
		if(argc>=3)
			pid=atoi(argv[2]);
		if(argc==4)
			f=fopen(argv[3],"w");
		else
			return -1;
	}
	else{
		if(argc==3)
			f=fopen(argv[2],"w");
		else
			return -1;
	}
	
	if (sys == 335)
	{
		struct proc_info* proc=(struct proc_info*)malloc(sizeof(struct proc_info));
		syscall(sys, pid, proc);
		fprintf(f,"Numele procesului este %s\n", proc->proc_name);
		fprintf(f,"Numele procesului parinte este %s\n", proc->father_name);
		fprintf(f,"Pidul procesului parinte este %d\n", proc->father_pid);
		fprintf(f,"Starea procesului este %s\n", proc->state);
	}
	else if (sys == 336)
	{
		struct space_info info;
		syscall(sys, pid,&info);
		fprintf(f,"Stack:\n");
		fprintf(f,"\tAdresa de inceput este: 0x%lu\n",info.stack_start);
		fprintf(f,"\tAdresa de final este: 0x%lu\n",info.stack_end);
		fprintf(f,"Heap:\n");
		fprintf(f,"\tAdresa de inceput este: 0x%lu\n",info.heap_start);
		fprintf(f,"\tAdresa de final este: 0x%lu\n",info.heap_end);
		fprintf(f,"Zona de date:\n");
		fprintf(f,"\tAdresa de inceput este: 0x%lu\n",info.data_start);
		fprintf(f,"\tAdresa de final este: 0x%lu\n",info.data_end);
		fprintf(f,"Zona de cod:\n");
		fprintf(f,"\tAdresa de inceput este: 0x%lu\n",info.code_start);
		fprintf(f,"\tAdresa de final este: 0x%lu\n",info.code_end);

	}
	else if (sys == 337)
	{
		struct proces*procs=(struct proces*)malloc(600*sizeof(struct proces));
		int nr_sys=syscall(sys,procs);
		fprintf(f,"Sunt %d procese active\n",nr_sys);
		for(int i=0;i<nr_sys;i++)
		{
			fprintf(f,"\t%d\t%d\t%s\n",procs[i].pid,procs[i].nice_val,procs[i].nume);
		}
		
	}
	else if (sys == 338)
	{
		int * useri=(int*)malloc(50*sizeof(int));
		int nr_users=syscall(sys,useri);
		char command[100];
		char user[50];
		fprintf(f,"Sunt %d useri in sistem:\n",nr_users);
		for(int i=0;i<nr_users;i++)
		{
			sprintf(command,"%s %d %s","id -nu",useri[i]," > user.txt");
			system(command);
			FILE*f=fopen("user.txt","r");
			fscanf(f,"%s",user);
			fclose(f);
			fprintf(f,"\tUID: %d\tNume: %s\n",useri[i],user); 
		}
		system("rm user.txt");
	}
	else if(sys==339)
	{
		struct sistem*sis=(struct sistem*)malloc(sizeof(struct sistem));
		syscall(sys,sis);
		fprintf(f,"Numele sistemului este %s\n",sis->nume);
		fprintf(f,"Versiunea sistemului este %s\n",sis->versiune);
		fprintf(f,"Data de actualizare este %s\n",sis->data_actualizare);
	}
	fclose(f);
}
