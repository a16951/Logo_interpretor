#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <malloc.h>
#include "vc.h"



int main(void) {

	IVC* imageM[6];
	IVC* imageL[6];
	int numeroM[5];
	int numeroL[5];
	OVC* nobjetos;
	char* Image = "Imagens/Imagem01-8449FS.ppm";


#pragma region criaçao de imagens para matricula
	//imagem original
	imageM[0] = vc_read_image(Image);
	
	if (imageM[0] == NULL)
	{
		printf("Error -> vc_read_image():\tFile not found.\n");
		getchar();
		return 0;
	}

	//imagem para gray
	imageM[1] = vc_image_new(imageM[0]->width, imageM[0]->height, 1, imageM[0]->levels);
	if (imageM[1] == NULL)
	{
		printf("Error -> vc_image_new():\tFail to create file.\n");
		getchar();
		return 0;
	}

	imageM[2] = vc_image_new(imageM[0]->width, imageM[0]->height, 1, imageM[0]->levels);
	if (imageM[2] == NULL)
	{
		printf("Error -> vc_image_new():\tFail to create file.\n");
		getchar();
		return 0;
	}

	imageM[3] = vc_image_new(imageM[0]->width, imageM[0]->height, 1, imageM[0]->levels);
	if (imageM[3] == NULL)
	{
		printf("Error -> vc_image_new():\tFail to create file.\n");
		getchar();
		return 0;
	}

	imageM[4] = vc_image_new(imageM[0]->width, imageM[0]->height, 1, imageM[0]->levels);
	if (imageM[4] == NULL)
	{
		printf("Error -> vc_image_new():\tFail to create file.\n");
		getchar();
		return 0;
	}

	imageM[5] = vc_read_image(Image);
	if (imageM[5] == NULL)
	{
		printf("Error -> vc_image_new():\tFail to create file.\n");
		getchar();
		return 0;
	}

	
#pragma endregion

#pragma region Encontrar matricula

	//transformar rgb para hsv
	vc_rgb_to_hsv(imageM[0]);

	//segmentar para encontrar os blobs
	vc_hsv_segmentation(imageM[0], 0, 360, 0, 100, 75, 100);
	//vc_hsv_segmentation(imageM[0], 0, 360, 0, 100, 59, 100);// para a segunda imagem

	//erode-dilate
	vc_binary_open(imageM[1], imageM[2], 2, 9);
	//vc_binary_open(imageM[1], imageM[2],2, 6);// para a segunda imaggem

	//dilate-erode
	vc_binary_close(imageM[2], imageM[3], 9, 2);
	//vc_binary_close(imageM[2], imageM[3], 5, 2);//para a segunda imagem

	//dar lable aos blobs
	nobjetos = vc_binary_blob_labelling(imageM[3], imageM[4], &numeroM[0]);

	//informaçao
	vc_binary_blob_info(imageM[4], nobjetos, numeroM[0]);

	//desenhar os quadrados nos blobs
	vc_draw_image(nobjetos, imageM[5], numeroM[0]);

	

#pragma endregion

#pragma region criaçao de imagens para letras

	//imagem que é so a matricula
	imageL[0] = vc_read_image("t77.pgm");
	if (imageL[0] == NULL)
	{
		printf("Error -> vc_image_new():\tFail to create file.\n");
		getchar();
		return 0;
	}

	//imagem para gray
	imageL[1] = vc_image_new(imageL[0]->width, imageL[0]->height, 1, imageL[0]->levels);
	if (imageL[1] == NULL)
	{
		printf("Error -> vc_image_new():\tFail to create file.\n");
		getchar();
		return 0;
	}

	imageL[2] = vc_image_new(imageL[0]->width, imageL[0]->height, 1, imageL[0]->levels);
	if (imageL[2] == NULL)
	{
		printf("Error -> vc_image_new():\tFail to create file.\n");
		getchar();
		return 0;
	}

	imageL[3] = vc_image_new(imageL[0]->width, imageL[0]->height, 1, imageL[0]->levels);
	if (imageL[3] == NULL)
	{
		printf("Error -> vc_image_new():\tFail to create file.\n");
		getchar();
		return 0;
	}

	imageL[4] = vc_image_new(imageL[0]->width, imageL[0]->height, 1, imageL[0]->levels);
	if (imageL[4] == NULL)
	{
		printf("Error -> vc_image_new():\tFail to create file.\n");
		getchar();
		return 0;
	}

	imageL[5] = vc_read_image("t77.pgm");
	if (imageL[5] == NULL)
	{
		printf("Error -> vc_image_new():\tFail to create file.\n");
		getchar();
		return 0;
	}


#pragma endregion

#pragma region Encontrar letras
	//transformar rgb para hsv
	vc_rgb_to_hsv(imageL[0]);

	//segmentar para encontrar os blobs
	vc_hsv_segmentation(imageL[0], 0, 360, 0, 100, 0, 29);

	vc_rgb_to_gray(imageL[0], imageL[1]);

	//erode-dilate
	vc_binary_open(imageL[1], imageL[2], 1, 2);

	//dilate-erode
	vc_binary_close(imageL[2], imageL[3], 1, 1);

	//dar lable aos blobs
	nobjetos = vc_binary_blob_labelling(imageL[3], imageL[4], &numeroL[0]);

	//informaçao
	vc_binary_blob_info(imageL[4], nobjetos, numeroL[0]);

	//desenhar os quadrados nos blobs
	int x=vc_draw_imageL(nobjetos, imageL[5], numeroL[0]);

	printf("//////MATRICULA POSSUI %d CARACTERES//////", x);

#pragma endregion

system("cmd /c start FilterGear Imagens/Imagem01-8449FS.ppm"); //INPUT

#pragma region Mostrar as imagens matricula

	vc_write_image("tb1.pgm", imageM[0]);
	vc_write_image("tb2.pgm", imageM[1]);
	vc_write_image("tb3.pgm", imageM[2]);
	vc_write_image("tb4.pgm", imageM[3]);
	vc_write_image("tb5.pgm", imageM[4]);
	vc_write_image("tb6.pgm", imageM[5]);
	vc_image_free(imageM[0]);
	vc_image_free(imageM[1]);
	vc_image_free(imageM[2]);
	vc_image_free(imageM[3]);
	vc_image_free(imageM[4]);
	vc_image_free(imageM[5]);


	system("FilterGear tb1.pgm"); // Output
	system("FilterGear tb2.pgm"); // Output
	system("FilterGear tb3.pgm"); // Output
	system("FilterGear tb4.pgm"); // Output
	system("FilterGear tb5.pgm"); // Output
	system("FilterGear tb6.pgm"); // Output
	system("FilterGear t77.pgm"); // Output
	

#pragma endregion

#pragma region Mostrar as imagens para letras

	vc_write_image("tl1.pgm", imageL[0]);
	vc_write_image("tl2.pgm", imageL[1]);
	vc_write_image("tl3.pgm", imageL[2]);
	vc_write_image("tl4.pgm", imageL[3]);
	vc_write_image("tl5.pgm", imageL[4]);
	vc_write_image("tl6.pgm", imageL[5]);
	vc_image_free(imageL[0]);
	vc_image_free(imageL[1]);
	vc_image_free(imageL[2]);
	vc_image_free(imageL[3]);
	vc_image_free(imageL[4]);
	vc_image_free(imageL[5]);


	system("FilterGear tl1.pgm"); // Output
	system("FilterGear tl2.pgm"); // Output
	system("FilterGear tl3.pgm"); // Output
	system("FilterGear tl4.pgm"); // Output
	system("FilterGear tl5.pgm"); // Output
	system("FilterGear tl6.pgm"); // Output


#pragma endregion

	printf("\nPress any key to exit.\n");
	getchar();
	return 0;

}