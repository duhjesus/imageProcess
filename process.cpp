//#include <aws/core/Aws.h>
#include <iostream>
#include "image.h"

using namespace std;



int main()
{	
	// Test RGBA PNG classes
	//==========================================================
	//write/constructor works
	cout << "HELLO WORLD!";
	// Image image;
	// image.writeImage("blueImage.png");
	
	// //read works
	// Image wave;
	// wave.readImage("wave.png");
	// wave.manipulateImage();
	// wave.writeImage("changedWaveImage.png");
   	
	// Test Filter
	//=========================================================
	
	//before filter applied
	Image a1b4;
	a1b4.readImage("a1_b4.png");
	//CELL *b4Pixels = a1b4.getGrid();

	//check rgba values of b4 image
	//long gridSize = a1b4.getHeight() * a1b4.getWidth();

	//after filter applied
	Image a1f;
	a1f.readImage("a1_f.png");
	//CELL *afterPixels = a1f.getGrid();


	//applying the filter to the b4 image to get the after image
	Image temp;
	temp.readImage("a1_b4.png");//"a1_b4.png");
	//temp.filter();
	temp.manipulateImage();
	temp.writeImage("redBefore.png");

	Image temp1;
	temp1.readImage("a1_f.png");
	temp1.manipulateImage();
	temp1.writeImage("redAfter.png");

	//printing 1 color at a time for compare result 
	// for(long i =0; i <gridSize; i++){
	// 	//deviatePixels[i].red = 0;
	// 	//deviatePixels[i].green = 0;
	// 	//deviatePixels[i].blue =0;
	// 	//deviatePixels[i].alpha = 255;
	// 	if(i % deviate.getWidth()==0){
	// 		cout<<endl;
	// 	}
	// 	cout<<(int)deviatePixels[i].red <<" ";
	// 	//if((int)deviatePixels[i].green!=0)
	// 	//	cout<<"FLAG!";
	// }

	//aws sdk  
	// Aws::SDKOptions options;
    // options.loggingOptions.logLevel = Aws::Utils::Logging::LogLevel::Info;
	// Aws::InitAPI(options);
	// //sdk call here
	// Aws::ShutdownAPI(options);


	return 0;
}
