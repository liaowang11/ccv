#include "ccv.h"
#include "case.h"
#include "ccv_case.h"

TEST_CASE("sobel operation")
{
	ccv_dense_matrix_t* image = 0;
	ccv_unserialize("../samples/chessbox.png", &image, CCV_SERIAL_GRAY | CCV_SERIAL_ANY_FILE);
	ccv_dense_matrix_t* x = 0;
	ccv_sobel(image, &x, 0, 0, 1);
	REQUIRE_MATRIX_FILE_EQ(x, "data/chessbox.sobel.x.bin", "should be sobel of partial derivative on x");
	ccv_dense_matrix_t* y = 0;
	ccv_sobel(image, &y, 0, 1, 0);
	REQUIRE_MATRIX_FILE_EQ(y, "data/chessbox.sobel.y.bin", "should be sobel of partial derivative on y");
	ccv_dense_matrix_t* x3 = 0;
	ccv_sobel(image, &x3, 0, 0, 3);
	REQUIRE_MATRIX_FILE_EQ(x3, "data/chessbox.sobel.x.3.bin", "should be sobel of partial derivative on x within 3x3 window");
	ccv_dense_matrix_t* y3 = 0;
	ccv_sobel(image, &y3, 0, 3, 0);
	REQUIRE_MATRIX_FILE_EQ(y3, "data/chessbox.sobel.y.3.bin", "should be sobel of partial derivative on y within 3x3 window");
	ccv_dense_matrix_t* x5 = 0;
	ccv_sobel(image, &x5, 0, 0, 5);
	REQUIRE_MATRIX_FILE_EQ(x5, "data/chessbox.sobel.x.5.bin", "should be sobel of partial derivative on x within 5x5 window");
	ccv_dense_matrix_t* y5 = 0;
	ccv_sobel(image, &y5, 0, 5, 0);
	REQUIRE_MATRIX_FILE_EQ(y5, "data/chessbox.sobel.y.5.bin", "should be sobel of partial derivative on y within 5x5 window");
	ccv_matrix_free(image);
	ccv_matrix_free(x);
	ccv_matrix_free(y);
	ccv_matrix_free(x3);
	ccv_matrix_free(y3);
	ccv_matrix_free(x5);
	ccv_matrix_free(y5);
	ccv_garbage_collect();
}

TEST_CASE("resample operation of CCV_INTER_AREA")
{
	ccv_dense_matrix_t* image = 0;
	ccv_unserialize("../samples/chessbox.png", &image, CCV_SERIAL_ANY_FILE);
	ccv_dense_matrix_t* x = 0;
	ccv_resample(image, &x, 0, image->rows / 5, image->cols / 5, CCV_INTER_AREA);
	REQUIRE_MATRIX_FILE_EQ(x, "data/chessbox.resample.bin", "should be a image of color dot");
	ccv_matrix_free(image);
	ccv_matrix_free(x);
	ccv_garbage_collect();
}

TEST_CASE("sample down operation with source offset (10, 10)")
{
	ccv_dense_matrix_t* image = 0;
	ccv_unserialize("../samples/chessbox.png", &image, CCV_SERIAL_ANY_FILE);
	ccv_dense_matrix_t* x = 0;
	ccv_sample_down(image, &x, 0, 10, 10);
	REQUIRE_MATRIX_FILE_EQ(x, "data/chessbox.sample_down.bin", "should be down sampled (/2) image with offset from source (10, 10)");
	ccv_matrix_free(image);
	ccv_matrix_free(x);
	ccv_garbage_collect();
}

TEST_CASE("sample up operation with source offset (10, 10)")
{
	ccv_dense_matrix_t* image = 0;
	ccv_unserialize("../samples/chessbox.png", &image, CCV_SERIAL_ANY_FILE);
	ccv_dense_matrix_t* x = 0;
	ccv_sample_up(image, &x, 0, 10, 10);
	REQUIRE_MATRIX_FILE_EQ(x, "data/chessbox.sample_up.bin", "should be down sampled (/2) image with offset from source (10, 10)");
	ccv_matrix_free(image);
	ccv_matrix_free(x);
	ccv_garbage_collect();
}

TEST_CASE("blur operation with sigma 10")
{
	ccv_dense_matrix_t* image = 0;
	ccv_unserialize("../samples/nature.png", &image, CCV_SERIAL_ANY_FILE);
	ccv_dense_matrix_t* x = 0;
	ccv_blur(image, &x, 0, sqrt(10));
	REQUIRE_MATRIX_FILE_EQ(x, "data/nature.blur.bin", "should be image applied with Gaussian filter with sigma sqrt(10)");
	ccv_matrix_free(image);
	ccv_matrix_free(x);
	ccv_garbage_collect();
}

TEST_CASE("flip operation")
{
	ccv_dense_matrix_t* image = 0;
	ccv_unserialize("../samples/chessbox.png", &image, CCV_SERIAL_ANY_FILE);
	ccv_dense_matrix_t* x = 0;
	ccv_flip(image, &x, 0, CCV_FLIP_X);
	REQUIRE_MATRIX_FILE_EQ(x, "data/chessbox.flip_x.bin", "flipped x-axis (around y-axis)");
	ccv_dense_matrix_t* y = 0;
	ccv_flip(image, &y, 0, CCV_FLIP_Y);
	REQUIRE_MATRIX_FILE_EQ(y, "data/chessbox.flip_y.bin", "flipped y-axis (around x-axis)");
	ccv_dense_matrix_t* xy = 0;
	ccv_flip(image, &xy, 0, CCV_FLIP_X | CCV_FLIP_Y);
	REQUIRE_MATRIX_FILE_EQ(xy, "data/chessbox.flip_xy.bin", "flipped xy-axis (rotated 180)");
	ccv_matrix_free(image);
	ccv_matrix_free(x);
	ccv_matrix_free(y);
	ccv_matrix_free(xy);
	ccv_garbage_collect();
}

TEST_CASE("canny edge detector")
{
	ccv_dense_matrix_t* image = 0;
	ccv_unserialize("../samples/blackbox.png", &image, CCV_SERIAL_GRAY | CCV_SERIAL_ANY_FILE);
	ccv_dense_matrix_t* x = 0;
	ccv_canny(image, &x, 0, 3, 36, 36 * 3);
	REQUIRE_MATRIX_FILE_EQ(x, "data/blackbox.canny.bin", "Canny edge detector on artificial image");
	ccv_matrix_free(image);
	ccv_matrix_free(x);
	ccv_garbage_collect();
}

TEST_CASE("otsu threshold")
{
	ccv_dense_matrix_t* image = ccv_dense_matrix_new(6, 6, CCV_32S | CCV_C1, 0, 0);
	/* the test case is grabbed from: http://www.labbookpages.co.uk/software/imgProc/otsuThreshold.html */
	image->data.i[0] = image->data.i[1] = image->data.i[6] = image->data.i[22] = image->data.i[23] = image->data.i[28] = image->data.i[29] = image->data.i[35] = 0;
	image->data.i[2] = image->data.i[7] = image->data.i[12] = image->data.i[16] = image->data.i[21] = image->data.i[27] = image->data.i[34] = 1;
	image->data.i[15] = image->data.i[26] = 2;
	image->data.i[8] = image->data.i[10] = image->data.i[13] = image->data.i[17] = image->data.i[20] = image->data.i[33] = 3;
	image->data.i[3] = image->data.i[4] = image->data.i[9] = image->data.i[11] = image->data.i[14] = image->data.i[18] = image->data.i[19] = image->data.i[25] = image->data.i[32] = 4;
	image->data.i[5] = image->data.i[24] = image->data.i[30] = image->data.i[31] = 5;
	double var;
	int threshold = ccv_otsu(image, &var, 6);
	REQUIRE_EQ(threshold, 2, "threshold should be 2 (inclusive)");
	REQUIRE_EQ_WITH_TOLERANCE(var, 2.6287, 0.0001, "between class variance should be 2.6287");
	ccv_matrix_free(image);
	ccv_garbage_collect();
}

#include "case_main.h"
