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
	virtual void boxFilter(const Matrix& src, Matrix& dst, const int kSize = 3) {
		assert( (0 < kSize) && (kSize / 2 < std::min(src.rows(), src.cols())) );
		assert( src.cols() == dst.cols() && src.rows() == dst.rows() );


		double mid = 1.0 / (kSize * kSize);

		for (int y = 0; y < src.rows(); ++y) {
			for (int x = 0; x < src.cols(); ++x) {
				double cell = 0.0;

				for (int i = -(kSize + 1) / 2, iend = kSize / 2; i < iend; ++i) {
					for (int j = -(kSize + 1) / 2, jend = kSize / 2; j < jend; ++j) {
						int yPos = y + std::abs(i);
						if (src.rows() <= yPos) {
							yPos = src.rows() - std::abs(i);
						}
						int xPos = x + std::abs(j);
						if (src.cols() <= xPos) {
							xPos = src.cols() - std::abs(j);
						}
						cell += src[yPos][xPos];
					}
				}
				dst[y][x] = static_cast<Entry>(cell * mid);
			}
		}
	}

	virtual void filter2d(const Matrix& src, Matrix& dst, const Matrix& kernel) {
		assert(kernel.rows() * kernel.cols() != 0);
		assert(std::max(kernel.cols(), kernel.rows()) / 2 < std::min(src.rows(), src.cols()));
		assert( src.cols() == dst.cols() && src.rows() == dst.rows() );


		for (auto i = 0; i != src.rows(); ++i) {
			for (auto j = 0; j != src.cols(); ++j) {
				dst[i][j] = createEntryValue(src, i, j, kernel);
			}
		}		
	}

	virtual void median(const Matrix& src, Matrix& dst, const int kSize = 3) {
		assert( (0 < kSize) && (kSize / 2 < std::min(src.rows(), src.cols())) );
		assert( src.cols() == dst.cols() && src.rows() == dst.rows() );

		Matrix kernel(kSize, kSize);


		for (int y = 0; y < src.rows(); ++y) {
			for (int x = 0; x < src.cols(); ++x) {
				createMedianKernel(src, x, y, kernel);

				for (int i = -(kSize + 1) / 2, iend = kSize / 2; i < iend; ++i) {
					for (int j = -(kSize + 1) / 2, jend = kSize / 2; j < jend; ++j) {
						int yPos = y + std::abs(i);
						if (src.rows() <= yPos) {
							yPos = src.rows() - std::abs(i);
						}
						int xPos = x + std::abs(j);
						if (src.cols() <= xPos) {
							xPos = src.cols() - std::abs(j);
						}
						dst[y][x] = kernel[i][j];
					}
				}
				
			}
		}
	}

	virtual void SobelOx(const Matrix& src, Matrix& dst) {
		throw std::exception("Function in development.");
	}

private:
	Entry createEntryValue(const Matrix& source, unsigned int x, unsigned int y, const Matrix& kernel);

	void createMedianKernel(const Matrix& source, unsigned int x, unsigned int y, Matrix& kernel);
};

FiltersZhiltsov::Entry FiltersZhiltsov::createEntryValue(const Matrix& source, unsigned int x, unsigned int y, const Matrix& kernel) {
	unsigned int result = 0;	
	for (int i = -(kernel.rows() + 1) / 2, iend = kernel.rows() / 2; i < iend; ++i) {
		for (int j = -(kernel.cols() + 1) / 2, jend = kernel.cols() / 2; j < jend; ++j) {
			int yPos = y + std::abs(i);
			if (source.rows() <= yPos) {
				yPos = source.rows() - std::abs(i);
			}
			int xPos = x + std::abs(j);
			if (source.cols() <= xPos) {
				xPos = source.cols() - std::abs(j);
			}
			result += source[yPos][xPos] * kernel[i][j];
		}
	}
	return static_cast<Entry>(result);
}

void FiltersZhiltsov::createMedianKernel(const Matrix& source, unsigned int x, unsigned int y, Matrix& kernel) {
	std::vector<Entry> values;
	values.reserve(kernel.rows() * kernel.cols());
	for (int i = -(kernel.rows() + 1) / 2, iend = kernel.rows() / 2; i < iend; ++i) {
		for (int j = -(kernel.cols() + 1) / 2, jend = kernel.cols() / 2; j < jend; ++j) {
			int yPos = y + std::abs(i);
			if (source.rows() <= yPos) {
				yPos = source.rows() - std::abs(i);
			}
			int xPos = x + std::abs(j);
			if (source.cols() <= xPos) {
				xPos = source.cols() - std::abs(j);
			}
			values.push_back(source[yPos][xPos]);
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