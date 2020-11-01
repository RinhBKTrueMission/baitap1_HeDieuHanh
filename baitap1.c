#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>



typedef struct SinhVien
{
	char HoTen[30];
	float GPA;
	int TOEIC;
	int TCDC;
	int HocPhi;
}SV;
char email[]="pageone103@gmail.com";
pthread_t tid[2];
int counter;
int m;
pthread_mutex_t lock;

 SV std = {"Tran The Rinh",3.0,800,93,15000000}; 
 SV std2;
 
char cmd[200];  

int UpdateSV()
{
	
	printf("Chon thong tin can update:\n");
	printf("1.GPA\n");
	printf("2.TCDC\n");
	printf("3.TOEIC\n");
	printf("4.HocPhi\n");
	int i;
	scanf("%d",&i);
	
	if(i==1){
	printf("%s\n","Nhap GPA : ");
	scanf("%f",&std.GPA); 
	}
	if(i==2)
	{
	printf("%s\n","Nhap so tin chi dat duoc :" );
	scanf("%d",&std.TCDC);
	}
	if(i==3)
	{
	printf("%s\n","Nhap diem TOEIC :");
	scanf("%d",&std.TOEIC);
	}

    if(i==4)
    {
    printf("%s\n","Nhap hoc phi :" );
	scanf("%d",&std.HocPhi);
    }

	return i;
}
void DisplaySV()
{
	printf("\nHo va ten:%s\n",std.HoTen); 
    printf("Diem GPA : %1.2f\n",std.GPA);
    printf("DIem TOEIC : %d\n",std.TOEIC );
    printf("Tin chi dat duoc : %d\n",std.TCDC );
    printf("Hoc phi : %d\n",std.HocPhi);

}

void *doSomeThing(void *arg)
{
	pthread_mutex_lock(&lock);

	unsigned long i = 0;
	counter += 1;

	printf("Job %d started\n", counter);

	m = UpdateSV();

	printf("Job %d finished \n", counter);

	DisplaySV();
	
 //    char id_thread[50];
 //    sprintf(id_thread, "ID THREAD:%ld\n",pthread_self());
	// sendmail(email,id_thread);
    char body[100] = "Thong bao da cap nhat thong tin sv voi THREAD ID";
    char updateGPA[]="GPA da duoc thay doi , GPA : ";
    char updateTCDC[]="Da co su thay doi Tin chi dat duoc,TCDC: ";
    char updateTOEIC[]="Da co su thay doi diem TOEIC, TOEIC: ";
    char updateHocPhi[]="Da co su thay doi ve hoc phi,HocPhi: ";


	 if (std.GPA != std2.GPA) {
    	sprintf(cmd, "echo \"%s %ld %s %1.2f\"| mail -s %s %s", body, pthread_self(),updateGPA,std.GPA, "\"THONG BAO THONG TIN SINH VIEN DA DUOC CAP NHAT!!!\"", email);

    }
    if(std.TCDC != std2.TCDC) {
    	sprintf(cmd, "echo \"%s %ld %s %d\"| mail -s %s %s", body, pthread_self(), updateTCDC,std.TCDC, "\"THONG BAO THONG TIN SINH VIEN DA DUOC CAP NHAT!!!\"", email);
    }
     if(std.TOEIC != std2.TOEIC) {
    	sprintf(cmd, "echo \"%s %ld %s %d\"| mail -s %s %s", body,pthread_self(), updateTOEIC,std.TOEIC, "\"THONG BAO THONG TIN SINH VIEN DA DUOC CAP NHAT!!!\"", email);
    }
     if(std.HocPhi!= std2.HocPhi) {
    	sprintf(cmd, "echo \"%s %ld %s %d\"| mail -s %s %s", body, pthread_self(), updateHocPhi,std.HocPhi, "\"THONG BAO THONG TIN SINH VIEN DA DUOC CAP NHAT!!!\"", email);
    }
    

     std2.GPA=std.GPA;
     std2.HocPhi=std.HocPhi;
     std2.TOEIC=std.TOEIC;
     std2.TCDC=std.TCDC;
    system(cmd); 



	

	pthread_mutex_unlock(&lock);

    return NULL;
}
// void sendmail(char mail[], char id[] )
// {
	
//     char body[100] = "Thong bao da cap nhat thong tin sv voi THREAD ID";
//     char updateGPA[]="GPA da duoc thay doi , GPA : ";
//     char updateTCDC[]="Da co su thay doi Tin chi dat duoc,TCDC: ";
//     char updateTOEIC[]="Da co su thay doi diem TOEIC, TOEIC: ";
//     char updateHocPhi[]="Da co su thay doi ve hoc phi,HocPhi: ";


// 	 if (std.GPA != std2.GPA) {
//     	sprintf(cmd, "echo \"%s %s %s %f\"| mail -s %s %s", body, id,updateGPA,std.GPA, "\"THONG BAO THONG TIN SINH VIEN DA DUOC CAP NHAT!!!\"", mail);

//     }
//     if(std.TCDC != std2.TCDC) {
//     	sprintf(cmd, "echo \"%s %s %s %d\"| mail -s %s %s", body, id, updateTCDC,std.TCDC, "\"THONG BAO THONG TIN SINH VIEN DA DUOC CAP NHAT!!!\"", mail);
//     }
//      if(std.TOEIC != std2.TOEIC) {
//     	sprintf(cmd, "echo \"%s %s %s %d\"| mail -s %s %s", body, id, updateTOEIC,std.TOEIC, "\"THONG BAO THONG TIN SINH VIEN DA DUOC CAP NHAT!!!\"", mail);
//     }
//      if(std.HocPhi!= std2.HocPhi) {
//     	sprintf(cmd, "echo \"%s %s %s %d\"| mail -s %s %s", body, id, updateHocPhi,std.HocPhi, "\"THONG BAO THONG TIN SINH VIEN DA DUOC CAP NHAT!!!\"", mail);
//     }
    


//     system(cmd); 
   

// }



int main(void)
{
 
    int i = 0;
    int err;
     std2.GPA=std.GPA;
     std2.HocPhi=std.HocPhi;
     std2.TOEIC=std.TOEIC;
     std2.TCDC=std.TCDC;

    while(i < 2)
    {
    	   		
     err = pthread_create(&(tid[i]), NULL, &doSomeThing, NULL);

        if (err != 0){
            printf("\ncan't create thread :[%s]", strerror(err));
        }
       

        i++;
    }
       
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);

   

    return 0;

}