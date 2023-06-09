// test_opemCV.cpp : Defines the entry point for the console application.
//


#include "stdafx.h"
#include <windows.h>
#include <stdio.h>


// //Uncomment the following line if you are compiling this code in Visual Studio
// //#include "stdafx.h"



#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/photo.hpp>

//#include <opencv2/xphoto/tonemap.hpp>




#include <opencv2/core.hpp>
#include <vector>       // std::vector
int main_Clahe(void)
{
	// READ RGB color image and convert it to Lab
	cv::Mat GRAY_image = cv::imread("E:\\HDR_TESTES\\1001\\1001.BMP");
	

	// Verifica se as imagens foram carregadas corretamente
	if (GRAY_image.empty() )
	{
		std::cerr << "Não foi possível abrir as imagens de entrada!" << std::endl;
		getchar();
		return -1;
	}


	std::vector<cv::Mat> channels;
	cv::split(GRAY_image, channels);


	// apply the CLAHE algorithm to the L channel
	cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE(20,cv::Size(4,4));
	//clahe->setClipLimit(8);
	cv::Mat dst;
	clahe->apply(channels[0], channels[0]);
	clahe->apply(channels[1], channels[1]);
	clahe->apply(channels[2], channels[2]);

	cv::merge(channels, dst);




	// display the results  (you might also want to see lab_planes[0] before and after).
	cv::imshow("image original", GRAY_image);
	cv::imshow("image CLAHE", dst);
	cv::waitKey();
}


/***************************************
por favor, gere um codigo fonte c++ para carregar 3 imagens de origem bitmap e passar num filtro HDR, depois salvar em bitmap
****************************************/

#ifdef temp

int mainHDR()
{
	// Carrega as três imagens bitmap de origem
	cv::Mat image1 = cv::imread("input1.bmp");
	cv::Mat image2 = cv::imread("input2.bmp");
	cv::Mat image3 = cv::imread("input3.bmp");

	// Verifica se as imagens foram carregadas corretamente
	if (image1.empty() || image2.empty() || image3.empty())
	{
		std::cerr << "Não foi possível abrir as imagens de entrada!" << std::endl;
		return -1;
	}

	// Converte as imagens para HDR
	image1.convertTo(image1, CV_32FC3, 1.0 / 255.0);
	image2.convertTo(image2, CV_32FC3, 1.0 / 255.0);
	image3.convertTo(image3, CV_32FC3, 1.0 / 255.0);

	// Combina as três imagens HDR usando o método de fusão de exposição
	std::vector<cv::Mat> images = { image1, image2, image3 };
	cv::Mat hdr_image;
	cv::Ptr<cv::MergeMertens> exposure_fusion = cv::createMergeMertens();
	exposure_fusion->process(images, hdr_image);

	// Converte a imagem HDR combinada para LDR
	cv::Mat ldr_image;
	cv:: hdrImaging::TonemapDurand tonemapper;
	tonemapper(hdr_image, ldr_image);

	// Aplica o filtro HDR na imagem LDR
	cv::Mat filtered_image;
	cv::Ptr<cv::xphoto::TonemapDurand> hdr_filter = cv::xphoto::createTonemapDurand();
	hdr_filter->process(ldr_image, filtered_image);

	// Converte a imagem resultante de volta para bitmap
	cv::Mat final_image;
	filtered_image.convertTo(final_image, CV_8UC3, 255.0);

	// Salva a imagem resultante em um arquivo bitmap de saída
	cv::imwrite("output.bmp", final_image);

	return 0;
}


#endif
void FuncaoHDR()
{
	// Leitura das imagens de entrada
	cv::Mat img0 = cv::imread("E:\\HDR_TESTES\\1002\\1001.BMP");
	cv::Mat img1 = cv::imread("E:\\HDR_TESTES\\1003\\1001.BMP");
	cv::Mat img2 = cv::imread("E:\\HDR_TESTES\\1004\\1001.BMP");



}


std::string trim_ext(std::string filename) {
	return filename.substr(0, filename.find_last_of('.'));
}

int image_write(cv::Mat &image, std::string &filename, std::string extension) {
	std::cout << "Saving file " << filename << " with extension " << extension << "\n";
	bool isSuccess = imwrite(trim_ext(filename) + extension, image); //write the image to a file as JPEG
	if (isSuccess == false) {
		std::cout << "Failed to save the image " << filename << extension << std::endl;
		std::cin.get(); //wait for a key press
		return -1;
	}
	std::cout << "Image is successfully saved to file " << filename << extension << std::endl;
	return 0;
}

int image_write(cv::Mat &image, std::string &filename) {
	return image_write(image, filename, ".png");
}

int main(int argc, char** argv) {

	main_Clahe();
	return 0;

	if (argc < 0) {
		// Read the image file
		std::cout << "Nenhum arquivo da pasta ../img/ digitado como argumento (ex: > ./ChangeContrastOfImage ../img/CEREBRAL.bmp).\n";
		cv::Mat image = cv::imread("E:\\Work_NEW\\Test_OpenCV\\test_opemCV\\x64\\Release\\img\\COLUNA.BMP");
		//      Check for failure
		if (image.empty()) {
			std::cout << "Could not open or find the image" << std::endl;
			std::cin.get();
			return -1;
		}
		std::string windowName = "Cerebral";        // name of the window
		std::cin.get();
		return 0;
	}

	//printf("Image filename in path ../img/");
	for (int i = 2; i < argc; i++) {
		printf("%s ", argv[i]);
	}
	std::string path = ""; // "../img/";
	std::string filename;// = path + _strdup(argv[1]);
	filename = "E:\\Work_NEW\\Test_OpenCV\\test_opemCV\\x64\\Release\\img\\COLUNA.bmp";

	//          ORIGINAL IMAGE
	std::string window_name_original_image = "Original Image";
	cv::Mat image = cv::imread(filename);
	namedWindow(window_name_original_image, cv::WINDOW_NORMAL);        // create and open window for image
	imshow(window_name_original_image, image);                     // show image in the created window
	std::string filename_orig = filename.substr(0, filename.find_last_of('.')) + ".jpg";
	image_write(image, filename_orig);


	//
	//  OBTAIN THE GRAYSCALE FROM THE COLOR IMAGE
	//
	cvtColor(image, image, cv::COLOR_BGR2GRAY);     // converts the color image (format BGR) into Black&White image
	std::string windowNameOriginalBlackwhiteImage = "Original Black&White Image";
	namedWindow(windowNameOriginalBlackwhiteImage, cv::WINDOW_NORMAL);      // create window
	imshow(window_name_original_image, image);
	std::string filename_grayscale = filename.substr(0, filename.find_last_of('.')) + ".jpg";
	image_write(image, filename_grayscale);


	//
	//  OBTAIN THE GRAYSCALE WITH THE EQUALIZED HISTOGRAM
	//
	cv::Mat hist_equalized_image;


	int i;

	char nomeArquivo[128];
	char logText[512];
	char dateText[128];

	SYSTEMTIME lt = { 0 };
	GetLocalTime(&lt);


	sprintf_s(dateText, 128, "%d:%d:%d.%d:", lt.wHour, lt.wMinute, lt.wSecond, lt.wMilliseconds);
	printf("TEMPO  ANTES= %d \n", dateText);


	for(i=0;i<1000;i++)
	   equalizeHist(image, hist_equalized_image);

	GetLocalTime(&lt);


	sprintf_s(dateText, 128, "%d:%d:%d.%d:", lt.wHour, lt.wMinute, lt.wSecond, lt.wMilliseconds);
	printf("TEMPO  DEPOIS= %d \n", dateText);

	
	


	std::string window_name_histogram_equalized = "Histogram Equalized Image";
	namedWindow(window_name_histogram_equalized, cv::WINDOW_NORMAL);        // create window
	imshow(window_name_histogram_equalized, hist_equalized_image);
	std::string filename_grayscale_equalized_histogram = filename.substr(0, filename.find_last_of('.')) + "_equalized_histogram.jpg";
	image_write(hist_equalized_image, filename_grayscale_equalized_histogram);

	//
	//      Alpha blending of the images
	//
	float alpha[] = { 0, 0.2, 0.4, 0.6, 0.8, 1.0 };       // alpha values for the transparency of the first image (values should be in the interval [0,1])
	float beta[] = { 1 - alpha[0], 1 - alpha[1], 1 - alpha[2], 1 - alpha[3], 1 - alpha[4], 1 - alpha[5] };    // beta values for the transparency of the second image (values should be in the interval [0,1])

	//int n_elements = sizeof(alpha) / sizeof(alpha[0]);
	int const n_elements = 6 ;
	std::string window_name_blended_image[n_elements];
	cv::Mat blended_image[n_elements];
	std::string filename_grayscale_blended_image[n_elements];
	std::string extension = ".png";

	//  Generate n_elements image superpositions of 'image' (case alpha = 1) and 'hist_equalized_image' (case alpha = 0)
	for (int i = 0; i < n_elements; i++) {
		addWeighted(image, alpha[i], hist_equalized_image, beta[i], 0.0, blended_image[i]);     // Blends the image (with weight alpha[i]) and hist_equalized_image (with weight beta[i]=1-alpha[i])

		window_name_blended_image[i] = "Blended Image - alpha = " + std::to_string(alpha[i]);
		namedWindow(window_name_blended_image[i], cv::WINDOW_NORMAL);        // create window
		imshow(window_name_blended_image[i], blended_image[i]);
		filename_grayscale_blended_image[i] = filename.substr(0, filename.find_last_of('.')) + "_blended_alpha" + std::to_string(alpha[i]) + ".jpg";
		image_write(blended_image[i], filename_grayscale_blended_image[i], extension);
	}

	cv::waitKey(0);         // Wait for any keystroke in one of the windows
	cv::destroyAllWindows();        //Destroy all open windows

	return 0;
}