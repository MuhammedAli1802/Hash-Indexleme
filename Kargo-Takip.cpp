
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
	int takipNo;
	char gonderici[100];
	char alici[100];
	char kargoDurum[100];
}Kargo;

Kargo hash_tablo[10];
	
	int eklenensira,sayac;
	int tkpno;
	char gndrc[10],alc[10],drm[10];	
	int numal,y;

int Hashindex1(int a){
	return a % 10;
}

int Hashindex2(int a){
	return 7-(a % 7);
}

int DoubleHashing(int a,int x){
	return (Hashindex1(a) + x * Hashindex2(a)) % 10;
}

void Initialize_Table(){
	for(int i=0;i<10;i++){
		hash_tablo[i].takipNo = -1;
		strcpy(hash_tablo[i].gonderici,"bos");
		strcpy(hash_tablo[i].alici,"bos");
		strcpy(hash_tablo[i].kargoDurum,"bos");
	}
}

void Listele();
void Ekle(int no,char *gnd,char *al,char *td);
int arama(int a);
void silme();
void topluyazma();
void tumunulistele();

void okuma(){
	FILE *read;
	if((read=fopen("veri.txt","r"))==NULL){
		printf("Veri dosyasý okumak icin acilamadi !");
	}
	
	while( !feof(read)){
		fscanf(read,"%d %s %s %s",&tkpno,gndrc,alc,drm);
		Ekle(tkpno,gndrc,alc,drm); printf("%d : %d. indekse eklendi\n",tkpno,eklenensira);
	}
	printf("Veriler Basariyla Girildi\n\n");
	fclose(read);
}

void yazdirma(int no,char *gnd,char *al,char *td){
	FILE *write;
	if((write=fopen("veri.txt","a+"))==NULL){
		printf("Veri dosyasi yazmak icin acilamadi !");
	}
	
	fprintf(write,"\n%d %s %s %s",no,gnd,al,td);
	fclose(write);
}

void topluyazma(){
	FILE *write1;
	if((write1=fopen("veri.txt","w"))==NULL){
		printf("Veri dosyasý toplu yazmak icin acilamadi !");
	}
	
	for(int i=0;i<10;i++){
		if(hash_tablo[i].takipNo != -1){
			fprintf(write1,"%d %s %s %s\n",hash_tablo[i].takipNo,hash_tablo[i].gonderici,hash_tablo[i].alici,hash_tablo[i].kargoDurum);
		}
	}
	fclose(write1);
}

void BilgiAl(){
	system("cls");
	printf("Takip Numarasini Giriniz: "); scanf("%d",&tkpno);
	printf("Gonderici Giriniz: "); scanf("%s",&gndrc);
	printf("Alici Giriniz: "); scanf("%s",&alc);
	printf("Teslimat Durum Bilgisi Giriniz: "); scanf("%s",&drm);
}

void Anamenu(){
	int anamenusecim;
	printf("0 - Texten Veri Girisi Yap\n1 - Tum Kargolari Listele\n2 - Kargo Girisi\n3 - Kargo Takip\n4 - Kargoyu Teslim Et\n5 - Cikis\n6 - Hash Tablosu\n");
	scanf("%d",&anamenusecim);
	switch(anamenusecim){
		case 0: okuma(); Anamenu();
		case 1: tumunulistele(); Anamenu();
		case 2: BilgiAl(); Ekle(tkpno,gndrc,alc,drm); if(sayac!=10){ printf("%d : %d. indekse eklendi\n",tkpno,eklenensira); yazdirma(tkpno,gndrc,alc,drm); } Anamenu();
		case 3: printf("Takip Numarasini Giriniz: "); scanf("%d",&numal); printf("\n"); arama(numal); Anamenu();
		case 4: silme(); Anamenu();
		case 5: exit(0);
		case 6: Listele(); Anamenu();
	}
}

void Ekle(int no,char *gnd,char *al,char *td){
	int x = 1;
	sayac=0;
	int index1 = Hashindex1(no);
	int index2 = Hashindex2(no);
	int index3 = DoubleHashing(no,x);
	
	if(hash_tablo[index1].takipNo == -1){
		hash_tablo[index1].takipNo = no;
		strcpy(hash_tablo[index1].gonderici,gnd);
		strcpy(hash_tablo[index1].alici,al);
		strcpy(hash_tablo[index1].kargoDurum,td);
		eklenensira=index1;
	}
	else {
		while(hash_tablo[index3].takipNo != -1 && sayac!=10){
			x++;
			index3 = DoubleHashing(no,x);
			sayac++;
			if(sayac==10){
				printf("%d : Tablo Dolu\n",no);
			}
		}
		if(sayac!=10){
			hash_tablo[index3].takipNo = no;
			strcpy(hash_tablo[index3].gonderici,gnd);
			strcpy(hash_tablo[index3].alici,al);
			strcpy(hash_tablo[index3].kargoDurum,td);
			eklenensira=index3;
		}
	}
}

int arama(int a){
	int s = 0,i1,i2,i3;
	y = 1;
	int sonuc;
	i1 = Hashindex1(a);
	i2 = Hashindex2(a);
	i3 = DoubleHashing(a,y);
	
	if(hash_tablo[i1].takipNo == a ){
		sonuc = y;
		printf("%d adimda bulundu\n Gonderici: %s , Alici: %s , Gonderici Durumu: %s\n\n",sonuc,hash_tablo[i1].gonderici,hash_tablo[i1].alici,hash_tablo[i1].kargoDurum);
	}
	else {
		while(hash_tablo[i3].takipNo != a && s!=10){
			y++;
			i3 = DoubleHashing(a,y);
			s++;
		}
		if(s == 10){
			printf("BULUNAMADI\n\n");
		}
		else {
			sonuc = y+1;
			printf("%d adimda bulundu\n Gonderici: %s , Alici: %s , Gonderici Durumu: %s\n\n",sonuc,hash_tablo[i3].gonderici,hash_tablo[i3].alici,hash_tablo[i3].kargoDurum);
		}
	}
	return sonuc;
}

void Listele(){
	system("cls");
	for(int i=0;i<10;i++){
		printf("%d|  %d\t%s\t%s\t%s\t\n",i,hash_tablo[i].takipNo,hash_tablo[i].gonderici,hash_tablo[i].alici,hash_tablo[i].kargoDurum);
	}
	printf("\n");
}

void tumunulistele(){
	int toplam=0,z;
	FILE *read;
	if((read=fopen("veri.txt","r"))==NULL){
		printf("Veri dosyasý okumak icin acilamadi !");
	}
	
	while( !feof(read)){
		fscanf(read,"%d %s %s %s",&tkpno,gndrc,alc,drm);
		toplam += arama(tkpno);
	}
	fclose(read);
	printf("\n Butun kargolar toplam %d adimda bulundu. \n\n",toplam);
}

void silme(){
	system("cls");
	int a,sayac1 = 1;;
	printf("Takip Numarasi Giriniz: "); scanf("%d",&a);
	for(int i=0;i<10;i++){
		if(hash_tablo[i].takipNo == a){
			hash_tablo[i].takipNo = -1;
			strcpy(hash_tablo[i].gonderici,"bos");
			strcpy(hash_tablo[i].alici,"bos");
			strcpy(hash_tablo[i].kargoDurum,"bos");
			printf("Gonderi hash tablosundan basariyla silindi.\n\n");
			break;
		}
		sayac1++;
	}
	if(sayac1==11){
		printf("BULUNAMADI");
	}
	topluyazma();
}

int main(){
	Initialize_Table();
	Anamenu();
}
