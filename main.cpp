#include<iostream>
#include <json.hpp>
#include <fstream>
#include <opencv2/opencv.hpp>

using json = nlohmann::json;

int main()
{
	std::ifstream f("C:/Users/111_r/Downloads/ComputerVisionBasedFlawDetection/Dependencies/dataForTraining/Aditional Dataset/Aditional Dataset/vott-json-export/Blades-export.json");
	
	nlohmann::json j;

	if (f.is_open())
	{
		f >> j;
		//std::cout << __LINE__ << std::endl;
		//std::string line;
		//while (std::getline(f,line))
		//{
		//	json += line;
		//	std::cout << line << std::endl;
		////}
		f.close();
	}
	std::string basePath = "C:/Users/111_r/Downloads/ComputerVisionBasedFlawDetection/Dependencies/dataForTraining/Aditional Dataset/Aditional Dataset/vott-json-export/";

	j = j["assets"];
	for (nlohmann::json::iterator it = j.begin(); it != j.end(); ++it) {
		json asset = it.value();
		cv::Mat image = cv::imread(basePath + asset["asset"]["name"].get<std::string>());
		std::cout << asset["regions"][0]["boundingBox"]["height"] << std::endl;
		cv::Rect boundingBox(asset["regions"][0]["boundingBox"]["left"].get<int>(), asset["regions"][0]["boundingBox"]["top"].get<int>(),
			asset["regions"][0]["boundingBox"]["width"].get<int>(), asset["regions"][0]["boundingBox"]["height"].get<int>());
		cv::rectangle(image, boundingBox, cv::Scalar(255, 0, 0), 5);
		std::cout << asset["asset"]["name"] << std::endl;
		std::cout << asset["regions"][0]["boundingBox"] << std::endl;
		std::cout << asset["regions"][0]["points"][0] << std::endl;
		cv::resize(image, image, cv::Size(), 0.15, 0.15);
		cv::imshow("image", image);
		cv::waitKey(0);
	}

	return 0;
}