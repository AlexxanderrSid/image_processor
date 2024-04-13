#pragma once

#include "../Image/image.h"

#include <random>
#include <cmath>
#include <algorithm>

class BaseFilter {
public:
    BaseFilter() = default;
    virtual void ApplyFilter(Image& image) = 0;
    virtual ~BaseFilter() = default;

protected:
    template <typename T>
    void ApplyMatrix(const std::vector<std::vector<T>>& matrix_to_apply, Image& image) const;
};

class Crop : public BaseFilter {
public:
    Crop(int32_t width, int32_t height);
    void ApplyFilter(Image& image) override;

private:
    int32_t width_;
    int32_t height_;
};

class GrayScale : public BaseFilter {
public:
    void ApplyFilter(Image& image) override;
};

class Negative : public BaseFilter {
public:
    void ApplyFilter(Image& image) override;
};

class Sharpening : public BaseFilter {
public:
    void ApplyFilter(Image& image) override;

private:
    std::vector<std::vector<int>> sharpening_matrix_ = {{0, -1, 0}, {-1, constant::FIVE, -1}, {0, -1, 0}};
};

class EdgeDetection : public GrayScale {
public:
    explicit EdgeDetection(double threshold);

    void ApplyFilter(Image& image) override;

private:
    double threshold_;
    std::vector<std::vector<int>> edge_detection_matrix_ = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};
};

class GaussianBlur : public BaseFilter {
public:
    explicit GaussianBlur(double sigma);

    void ApplyFilter(Image& image) override;

private:
    double sigma_;

private:
    double GaussianFunction(int32_t x, double sigma) const;
};

class CustomFilter : public BaseFilter {
public:
    void ApplyFilter(Image& image) override;
};
