#include "filters.hpp"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>

using namespace cv;

class FiltersZhiltsov : public Filters
{
private:
	typedef unsigned char Entry;

public:
	virtual void boxFilter(const Matrix &src, Matrix& dst, const int kSize = 3) {
		Matrix kernel(kSize, kSize);
		Entry value = static_cast<Entry>(1 / (kSize * kSize));
		for (auto i = 0; i != kSize; ++i) {
			for (auto j = 0; j != kSize; ++j) {
				kernel[i][j] = value;
			}
		}
		linearFilter(kernel, src, dst);
	}

	virtual void filter2d(const Matrix &src, Matrix& dst, const Matrix &kernel) {
		throw std::exception("Function in development.");
	}

	virtual void median(const Matrix &src, Matrix &dst, const int kSize = 3) {
		Matrix kernel(kSize, kSize);

		for (auto x = 0; x < src.rows(); x += kSize) {
			for (auto y = 0; y < src.cols(); y += kSize) {
				createMedianKernel(src, x, y, kernel);
				linearFilter(kernel, src, dst);
			}
		}
	}

	virtual void SobelOx(const Matrix &src, Matrix &dst) {
		throw std::exception("Function in development.");
	}

private:
	void checkInput(const Matrix& kernel, const Matrix& source);
	void linearFilter(const Matrix& kernel, const Matrix& source, Matrix& dest);
	Entry createEntryValue(const Matrix& source, unsigned int x, unsigned int y, const Matrix& kernel);

	void createMedianKernel(const Matrix& source, unsigned int x, unsigned int y, Matrix& kernel);
};

void FiltersZhiltsov::checkInput(const Matrix &kernel, const Matrix &src) {
	if (kernel.cols() <= 0 || kernel.rows() <= 0) {
		throw std::exception("Wrong kernel size.");
	}
}

void FiltersZhiltsov::linearFilter(const Matrix &kernel, const Matrix &source, Matrix& dest) {
	checkInput(kernel, source);
	for (auto i = 0; i != source.rows(); ++i) {
		for (auto j = 0; j != source.cols(); ++j) {
			dest[i][j] = createEntryValue(source, i, j, kernel);
		}
	}
}

FiltersZhiltsov::Entry FiltersZhiltsov::createEntryValue(const Matrix& source, unsigned int x, unsigned int y, const Matrix& kernel) {
	Entry result = 0;	
	for (auto i = 0; i != kernel.rows(); ++i) {
		for (auto j = 0; j != kernel.cols(); ++j) {
			if ((x + i < source.rows()) && (y + j < source.cols())) {
				result += source[x + i][y + j] * kernel[i][j];
			}
		}	
	}
	return result;
}

void FiltersZhiltsov::createMedianKernel(const Matrix& source, unsigned int x, unsigned int y, Matrix& kernel) {
	std::vector<Entry> values;
	values.reserve(kernel.rows() * kernel.cols());
	for (auto i = 0; i != kernel.rows(); ++i) {
		for (auto j = 0; j != kernel.cols(); ++j) {
			if ((x + i < source.rows()) || (y + j < source.cols())) {
				values.push_back(source[x + i][y + j]);
			}
		}
	}

	Entry value = values[values.size() / 2];
	for (auto i = 0; i != kernel.rows(); ++i) {
		for (auto j = 0; j != kernel.cols(); ++j) {
			kernel[i][j] = value;
		}
	}
}


Filters* createFiltersZhiltsov() {
	return new FiltersZhiltsov();
}