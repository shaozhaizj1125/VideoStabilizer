#pragma once

#include <QDebug>

#include <opencv2/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/videostab.hpp>

using namespace cv;
using namespace cv::videostab;

class VideoStabilizer
{
private:
    Ptr<IFrameSource> frames;
    Ptr<VideoFileSource> source;
    Ptr<MotionEstimatorRansacL2> motion_estimator;
    Ptr<KeypointBasedMotionEstimator> motion_estimator_builder;
    Ptr<StabilizerBase> stabilizer;

    double min_inlier_ratio = 0.1;
    int ransac_size         = 3;
    float ransac_eps        = 0.5f;
    float ransac_thresh     = 5.0f;

    int radius_pass         = 15;

    int radius              = 15;
    double trim_ratio       = 0.1;

public:
    VideoStabilizer()
    {
        motion_estimator = makePtr<MotionEstimatorRansacL2>(MM_AFFINE);
        motion_estimator_builder = makePtr<KeypointBasedMotionEstimator>(motion_estimator);

        // Prepare RANSAC motion estimator
        RansacParams params = motion_estimator->ransacParams();
        params.size = ransac_size;
        params.eps = ransac_eps;
        params.thresh = ransac_thresh;

        motion_estimator->setRansacParams(params);
        motion_estimator->setMinInlierRatio(min_inlier_ratio);

        motion_estimator_builder->setDetector(GFTTDetector::create(1000));
        motion_estimator_builder->setOutlierRejector(makePtr<NullOutlierRejector>());

        // Prepare the stabilizer

        Ptr<TwoPassStabilizer> two_pass_stabilizer = makePtr<TwoPassStabilizer>();
        two_pass_stabilizer->setEstimateTrimRatio(true);
        two_pass_stabilizer->setMotionStabilizer(makePtr<GaussianMotionFilter>(radius_pass));

        stabilizer = two_pass_stabilizer;
        stabilizer->setMotionEstimator(motion_estimator_builder);
        stabilizer->setRadius(radius);
        stabilizer->setTrimRatio(trim_ratio);
        stabilizer->setCorrectionForInclusion(false);
        stabilizer->setBorderMode(BORDER_REPLICATE);
    }

public:
    void Process(std::string file_path)
    {
        source = makePtr<VideoFileSource>(file_path);
        stabilizer->setFrameSource(source);
        frames =  stabilizer.dynamicCast<IFrameSource>();
    }

    void SaveResult(std::string absolute_file_path)
    {
        VideoWriter writer;
        double fps = 29;
        for(Mat frame = frames->nextFrame(); !frame.empty(); frame = frames->nextFrame())
        {
                if(!writer.isOpened()) {
                    writer.open(
                        absolute_file_path,
                        VideoWriter::fourcc('X','V','I','D'),
                        fps, frame.size());
                }
                writer << frame;
        }
    }

};


