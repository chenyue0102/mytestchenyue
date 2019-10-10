#pragma once
#include <QImage>
#include <opencv2/core/core.hpp>

namespace QtOpenCV
{
QImage Mat2QImage(const cv::Mat &mat);
cv::Mat QImage2Mat(const QImage &img);
};

