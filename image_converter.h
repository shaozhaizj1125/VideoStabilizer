#pragma once

#include <opencv2/core.hpp>

#include <QDebug>
#include <QImage>
#include <QPixmap>


inline QImage toQImage(const cv::Mat& cv_image)
{
      switch (cv_image.type())
      {
         case CV_8UC1:   // 8-bit, 1 channel
         {
            QImage q_image(cv_image.data,
                         cv_image.cols, cv_image.rows,
                         static_cast<int>(cv_image.step),
                         QImage::Format_Grayscale8);

            return q_image;
         }
         case CV_8UC3: // 8-bit, 3 channel
         {
            QImage q_image(cv_image.data,
                         cv_image.cols, cv_image.rows,
                         static_cast<int>(cv_image.step),
                         QImage::Format_RGB888);

            return q_image.rgbSwapped();
         }
         case CV_8UC4: // 8-bit, 4 channel
         {
            QImage q_image(cv_image.data,
                         cv_image.cols, cv_image.rows,
                         static_cast<int>(cv_image.step),
                         QImage::Format_ARGB32);

            return q_image;
         }
         default:
         {
            qWarning() << "toQImage() - cv::Mat image type not handled in switch:" << cv_image.type();
            return QImage();
         }
      }
}

inline QPixmap toQPixmap(const cv::Mat& cv_image) {
    return QPixmap::fromImage(toQImage(cv_image));
}


// NOTE: in case of images/pixmap Format_RGB888 toCvMat always makes a clone

inline cv::Mat toCvMat(const QImage& q_image, bool make_clone = true)
{
  switch (q_image.format())
  {
      case QImage::Format_Indexed8: // 8-bit, 1 channel
      {
         cv::Mat cv_image(q_image.height(), q_image.width(),
                         CV_8UC1,
                         const_cast<uchar*>(q_image.bits()),
                         static_cast<size_t>(q_image.bytesPerLine()));

         return (make_clone ? cv_image.clone() : cv_image);
      }
      case QImage::Format_RGB32:   // 8-bit, 3 channel
      case QImage::Format_RGB888:  // 8-bit, 3 channel
      {
         if (!make_clone) {
            qWarning() << "toCvMat() - Conversion requires cloning because we use a temporary QImage";
         }

         QImage swapped = q_image;
         if (q_image.format() == QImage::Format_RGB32) {
            swapped = swapped.convertToFormat(QImage::Format_RGB888);
         }
         swapped = swapped.rgbSwapped();

         return cv::Mat(swapped.height(), swapped.width(),
                        CV_8UC3,
                        const_cast<uchar*>(swapped.bits()),
                        static_cast<size_t>(swapped.bytesPerLine())
                        ).clone();
      }
      case QImage::Format_ARGB32:               // 8-bit, 4 channel
      case QImage::Format_ARGB32_Premultiplied: // 8-bit, 4 channel
      {
         cv::Mat cv_image(q_image.height(), q_image.width(),
                          CV_8UC4,
                          const_cast<uchar*>(q_image.bits()),
                          static_cast<size_t>(q_image.bytesPerLine()));

         return (make_clone ? cv_image.clone() : cv_image);
      }
      default:
      {
          qWarning() << "toCvMat() - QImage format not handled in switch:" << q_image.format();
          return cv::Mat();
      }
  }
}

inline cv::Mat toCvMat(const QPixmap& q_pixmap, bool make_clone = true) {
  return toCvMat(q_pixmap.toImage(), make_clone);
}

/**
  Special thanks to Andy Maloney
  https://asmaloney.com/2013/11/code/converting-between-cvmat-and-qimage-or-qpixmap
**/
