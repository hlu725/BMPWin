#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
/*λͼͷ�ļ����ݽṹ*/
typedef struct tagBITMAPFILEHEADER { 
  unsigned char  bfType[2];			//λͼ�ļ����ͣ�����Ϊ'B' 'M'
  unsigned long  bfSize;			//λͼ�ļ���С�����ֽ�Ϊ��λ��
  unsigned short bfReserved1;		//λͼ�ļ������֣�����Ϊ0
  unsigned short bfReserved2;		//λͼ�ļ������֣�����Ϊ0
  unsigned long  bfOffBits;			//λͼ���ݵ���ʼλ�ã������λͼ�ļ�ͷ��ƫ��������λ�ֽڣ�
}BITMAPFILEHEADER ;		//��14Byte
/*λͼ��Ϣ���ݽṹ*/
typedef struct tagBITMAPINFOHEADER{ 
  unsigned long  biSize;			//���ṹ��ռ���ֽ���
  long           biWidth;			//λͼ��ȣ�������Ϊ��λ
  long           biHeight;    		//λͼ�߶ȣ�������Ϊ��λ
  unsigned short biPlanes;			//Ŀ���豸���𣬱���Ϊ1
  unsigned short biBitCount;		//ÿ�����������λ����1��˫ɫ����4��16ɫ����8��256ɫ����24�����ɫ��
  unsigned long  biCompression;		//λͼ��ѹ�����ͣ�������0��ʾ��ѹ������1(BI_RLE8ѹ������)��2(BI_RLE4ѹ������)֮һ
  unsigned long  biSizeImage;		//λͼ��С���ֽ�Ϊ��λ
  long           biXPixPerMeter;	//ͼ��ˮƽ�ֱ��ʣ�ÿ��������
  long           biYPixPerMeter;	//ͼ��ֱ�ֱ��ʣ�ÿ��������
  unsigned long  biClrUsed;			//λͼʵ��ʹ�õ���ɫ���е���ɫ��
  unsigned long  biClrImporant;		//λͼ��ʾ��������Ҫ����ɫ��
}BITMAPINFOHEADER;		//��40Byte

int main(void)
{
  FILE *fp;
  int i,j;
  unsigned char c, d;
  
  BITMAPFILEHEADER *bitmapFileHeader;
  BITMAPINFOHEADER *bitmapInfoHeader;
  
  if((fp=fopen("f://outputfile.bmp", "wb")) == NULL){ 
    fprintf(stderr, "file cannot open\n");
    exit(1);
  }
  
  /* �ṹ��ָ���ʼ�� */
  bitmapFileHeader=(BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));
  bitmapInfoHeader=(BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));
   printf("%d\n",sizeof( bitmapFileHeader->bfType[2]));
  /*����λͼͷ�ļ����ݽṹ*/
  bitmapFileHeader->bfType[0] = 'B';
  bitmapFileHeader->bfType[1] = 'M';
  bitmapFileHeader->bfReserved1 = 0x0000; 
  bitmapFileHeader->bfReserved2 = 0x0000;
  //λͼ��ʼλ��
  bitmapFileHeader->bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

  /*����λͼ��Ϣ���ݽṹ*/
  bitmapInfoHeader->biSize = sizeof(BITMAPINFOHEADER); 
  bitmapInfoHeader->biWidth = (long)128;	
  bitmapInfoHeader->biHeight = (long)128;	
  bitmapInfoHeader->biPlanes = 0x0001;
  bitmapInfoHeader->biBitCount = 0x0018;		//24λͼ
  bitmapInfoHeader->biCompression = 0x0000;		//��ѹ��
  /*ÿ������RGB24λ���ɣ���3�ֽ�*/
  bitmapInfoHeader->biSizeImage = bitmapInfoHeader->biWidth*bitmapInfoHeader->biHeight * 3; 
  bitmapInfoHeader->biXPixPerMeter = 3780;		/*96dpi*/
  bitmapInfoHeader->biYPixPerMeter = 3780;		/*96dpi*/
  bitmapInfoHeader->biClrUsed = 0;			
  bitmapInfoHeader->biClrImporant = 0;		
  
  /*λͼ�ļ���С*/
  bitmapFileHeader->bfSize = bitmapFileHeader->bfOffBits + bitmapInfoHeader->biSizeImage;
  
  /*λͼͷ�ļ��ṹд���ļ�*/
  fwrite((unsigned char *)bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
  /*λͼ��Ϣ�ṹд���ļ�*/
  fwrite((unsigned char *)bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
  
  /*RGB��ɫд���ļ�*/
  for(j=0;j<bitmapInfoHeader->biHeight;j++){
    for(i=0;i<bitmapInfoHeader->biWidth;i++){
      c=(((i&0x08)==0)^((j&0x08)==0))*255; 
      fputc(c, fp);             /* B */
      fputc(c, fp);             /* G */
      fputc(c, fp);             /* R */
	}
  }
	
  free(bitmapFileHeader);
  free(bitmapInfoHeader);
  fclose(fp);
  return(0);
}
