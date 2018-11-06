#include "blob.hpp"

// blob::blob(){

// }


void blob::test_blob(cv::Mat frame)
{	
	cv::Mat im;



	// Setup SimpleBlobDetector parameters.
	cv::SimpleBlobDetector::Params params;
	 
	// Change thresholds
	params.minThreshold = 150;
	params.maxThreshold = 250;
	 
	// Filter by Area.
	params.filterByArea = true;
	params.minArea = 500;
	 
	// Filter by Circularity
	params.filterByCircularity = true;
	params.minCircularity = 0.2;
	 
	// Filter by Convexity
	params.filterByConvexity = true;
	params.minConvexity = 0.001;
	 
	// Filter by Inertia
	params.filterByInertia = true;
	params.minInertiaRatio = 0.01;
	 
	cv::SimpleBlobDetector detector(params);


		// while(1)
	 //    {
	    	
	  //       mask.generateMask(frame);
	  //       dilate(mask.blackMask, mask.blackMask,  MORPH_ELLIPSE);
	  // 	   bitwise_and(mask.blackMask, mask.whiteMask, frame);
			
	        im = frame;
	        cv::imshow("im", im );

			// Mat im_erode;
			// erode( im, im_erode, MORPH_ELLIPSE );
			// imshow("im_erode", im_erode );

			// // Set up the detector with default parameters.
			//cv::SimpleBlobDetector detector;

			// Detect blobs.
			std::vector<cv::KeyPoint> keypoints;
			detector.detect( im, keypoints);

			// Draw detected blobs as red circles.
			// DrawMatchesFlags::DRAW_RICH_KEYPOINTS flag ensures the size of the circle corresponds to the size of blob


			cv::Mat im_with_keypoints;

			cv::drawKeypoints( im, keypoints, im_with_keypoints, cv::Scalar(0,0,255), cv::DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

			// Show blobs
			cv::imshow("keypoints.", im_with_keypoints );
		
		
	    
		//}

}
