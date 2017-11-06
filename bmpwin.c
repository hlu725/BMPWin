#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
/*位图头文件数据结构*/
typedef struct tagBITMAPFILEHEADER { 
  unsigned char  bfType[2];			//位图文件类型，必须为'B' 'M'
  unsigned long  bfSize;			//位图文件大小（以字节为单位）
  unsigned short bfReserved1;		//位图文件保留字，必须为0
  unsigned short bfReserved2;		//位图文件保留字，必须为0
  unsigned long  bfOffBits;			//位图数据的起始位置，以相对位图文件头的偏移量（单位字节）
}BITMAPFILEHEADER ;		//共14Byte
/*位图信息数据结构*/
typedef struct tagBITMAPINFOHEADER{ 
  unsigned long  biSize;			//本结构所占用字节数
  long           biWidth;			//位图宽度，以像素为单位
  long           biHeight;    		//位图高度，以像素为单位
  unsigned short biPlanes;			//目标设备级别，必须为1
  unsigned short biBitCount;		//每个像素所需的位数，1（双色），4（16色），8（256色），24（真彩色）
  unsigned long  biCompression;		//位图的压缩类型，必须是0（示不压缩），1(BI_RLE8压缩类型)，2(BI_RLE4压缩类型)之一
  unsigned long  biSizeImage;		//位图大小以字节为单位
  long           biXPixPerMeter;	//图像水平分辨率，每米像素数
  long           biYPixPerMeter;	//图像垂直分辨率，每米像素数
  unsigned long  biClrUsed;			//位图实际使用的颜色表中的颜色数
  unsigned long  biClrImporant;		//位图显示过程中重要的颜色数
}BITMAPINFOHEADER;		//共40Byte

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
  
  /* 结构体指针初始化 */
  bitmapFileHeader=(BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));
  bitmapInfoHeader=(BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));
   printf("%d\n",sizeof( bitmapFileHeader->bfType[2]));
  /*定义位图头文件数据结构*/
  bitmapFileHeader->bfType[0] = 'B';
  bitmapFileHeader->bfType[1] = 'M';
  bitmapFileHeader->bfReserved1 = 0x0000; 
  bitmapFileHeader->bfReserved2 = 0x0000;
  //位图起始位置
  bitmapFileHeader->bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

  /*定义位图信息数据结构*/
  bitmapInfoHeader->biSize = sizeof(BITMAPINFOHEADER); 
  bitmapInfoHeader->biWidth = (long)128;	
  bitmapInfoHeader->biHeight = (long)128;	
  bitmapInfoHeader->biPlanes = 0x0001;
  bitmapInfoHeader->biBitCount = 0x0018;		//24位图
  bitmapInfoHeader->biCompression = 0x0000;		//不压缩
  /*每像素由RGB24位构成，即3字节*/
  bitmapInfoHeader->biSizeImage = bitmapInfoHeader->biWidth*bitmapInfoHeader->biHeight * 3; 
  bitmapInfoHeader->biXPixPerMeter = 3780;		/*96dpi*/
  bitmapInfoHeader->biYPixPerMeter = 3780;		/*96dpi*/
  bitmapInfoHeader->biClrUsed = 0;			
  bitmapInfoHeader->biClrImporant = 0;		
  
  /*位图文件大小*/
  bitmapFileHeader->bfSize = bitmapFileHeader->bfOffBits + bitmapInfoHeader->biSizeImage;
  
  /*位图头文件结构写入文件*/
  fwrite((unsigned char *)bitmapFileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
  /*位图信息结构写入文件*/
  fwrite((unsigned char *)bitmapInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
  
  /*RGB颜色写入文件*/
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
