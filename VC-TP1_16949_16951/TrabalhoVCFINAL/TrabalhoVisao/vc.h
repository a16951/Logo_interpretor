//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//           INSTITUTO POLITÉCNICO DO CáVADO E DO AVE          +
//                          2011/2012                          +
//             ENGENHARIA DE SISTEMAS INFORMÁTICOS             + 
//                    VISãO POR COMPUTADOR                     +
//                                                             +
//             [  DUARTE DUQUE - dduque@ipca.pt  ]             +
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


#define VC_DEBUG


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//								MACROS                   
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

				// Se a > b, define máximo 'a' senão (:) define b
#define MAX(a,b) (a > b ? a : b)
#define MIN(a,b) (a < b ? a : b)

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                   ESTRUTURA DE UMA IMAGEM                   +
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


typedef struct {
	unsigned char* data;
	int width, height;
	int channels;			// Binário/Cinzentos=1; RGB=3
	int levels;				// Binário=1; Cinzentos [1,255]; RGB [1,255]
	int bytesperline;		// width * channels
} IVC;

typedef struct {
	int x, y, width, height;	// Caixa Delimitadora (Bounding Box)
	int area;					// área
	int xc, yc;					// Centro-de-massa
	int perimeter;				// Perímetro
	int label;					// Etiqueta
} OVC;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                    PROTóTIPOS DE FUNÇÕES                    +
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

// FUNÇÕES: ALOCAR E LIBERTAR UMA IMAGEM
IVC* vc_image_new(int width, int height, int channels, int levels);
IVC* vc_image_free(IVC* image);

// FUNÇÕES: LEITURA E ESCRITA DE IMAGENS (PBM, PGM E PPM)
IVC* vc_read_image(char* filename);
int vc_write_image(char* filename, IVC* image);

// FUNÇÃO QUE CALCULA O NEGATIVO DE UMA IMAGEM GRAY
int vc_gray_negative(IVC* srcdst);

// FUNÇÃO QUE CALCULA O NEGATIVO DE UMA IMAGEM RGB
int vc_rgb_negative(IVC* srcdst);

// FUNÇÃO PARA EXTRAIR UMA COMPONENTE DA IMAGEM RGB PARA GRAY
int vc_rgb_get_red_gray(IVC* srcdst); // Red
int vc_rgb_get_green_gray(IVC* srcdst);	// Green
int vc_rgb_get_blue_gray(IVC* srcdst);	// Blue

// FUNÇÃO PARA CONVERTER DE RGB PARA GRAY
int vc_rgb_to_gray(IVC* src, IVC* dst);

// FUNÇÃO PARA CONVERTER UMA IMAGEM NO ESPAÇO RGB PARA O ESPAÇO HSV
int vc_rgb_to_hsv(IVC* srcdst);
int vc_hsv_segmentation(IVC* srcdst, int hmin, int hmax, int smin, int smax, int vmin, int vmax);

// FUNÇÃO PARA CONVERTER DE TONS DE CINZENTO PARA RGB
int vc_scale_gray_to_rgb(IVC* src, IVC* dst);

// FUN��ES PARA CONVERTER IMAGENS EM TONS DE CINZENTO PARA BINÁRIO
int vc_gray_to_binary(IVC* srcdst, int threshold);
int vc_gray_to_binary_global_mean(IVC* srcdst);

// FUNÇÃO PARA 
int vc_gray_to_binary_midpoint(IVC* src, IVC* dst, int tamKernel);

// FUNÇOES PARA EFETUAR DILATAÇÃO E EROSÃO
int vc_binary_dilate(IVC* src, IVC* dst, int kernel);
int vc_binary_erode(IVC* src, IVC* dst, int kernel);

// FUNÇÕES PARA FAZER ABERTURA E FECHO BINÁRIO
int vc_binary_open(IVC* src, IVC* dst, int sizeerode, int sizedilate);
int vc_binary_close(IVC* src, IVC* dst, int sizedilate, int sizeerode);

//labelling de blobs
OVC* vc_binary_blob_labelling(IVC* src, IVC* dst, int* nlabels);
int vc_binary_blob_info(IVC* src, OVC* blobs, int nblobs);

//Funções para desenhar
int vc_draw_image(OVC* blobs, IVC* src, int nblobs);
int vc_draw_imageL(OVC* blobs, IVC* src, int nblobs);


