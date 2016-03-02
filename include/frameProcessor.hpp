#ifndef FRAME_PROCESSOR_HPP
#define FRAME_PROCESSOR_HPP

#include <opencv2/core.hpp>
#include <opencv2/aruco/charuco.hpp>
#include <opencv2/calib3d.hpp>
#include "calibCommon.hpp"

namespace calib
{
class FrameProcessor
{
protected:

public:
    virtual ~FrameProcessor();
    virtual cv::Mat processFrame(const cv::Mat& frame) = 0;
    virtual bool isProcessed() const = 0;
    virtual void resetState() = 0;
};

class CalibProcessor : public FrameProcessor
{
protected:
    Sptr<calibrationData> mCalibdata;
    TemplateType mBoardType;
    cv::Size mBoardSize;
    std::vector<cv::Point2f> mTemplateLocations;
    std::vector<cv::Point2f> mCurrentImagePoints;
    cv::Mat mCurrentCharucoCorners;
    cv::Mat mCurrentCharucoIds;

    cv::Ptr<cv::SimpleBlobDetector> mBlobDetectorPtr;
    cv::Ptr<cv::aruco::Dictionary> mArucoDictionary;
    cv::Ptr<cv::aruco::CharucoBoard> mCharucoBoard;

    int mNeededFramesNum;
    int mCapuredFrames;
    float mMaxTemplateOffset;

    bool detectAndParseChessboard(const cv::Mat& frame);
    bool detectAndParseChAruco(const cv::Mat& frame);
    bool detectAndParseACircles(const cv::Mat& frame);
    bool detectAndParseDualACircles(const cv::Mat& frame);
    void saveFrameData();

public:
    CalibProcessor(Sptr<calibrationData> data, TemplateType board, cv::Size boardSize);
    virtual cv::Mat processFrame(const cv::Mat& frame) override;
    virtual bool isProcessed() const override;
    virtual void resetState() override;
    ~CalibProcessor();
};

class ShowProcessor : public FrameProcessor
{
protected:
    Sptr<calibrationData> mCalibdata;
    void drawGridPoints(const cv::Mat& frame);
public:
    ShowProcessor(Sptr<calibrationData> data);
    virtual cv::Mat processFrame(const cv::Mat& frame) override;
    virtual bool isProcessed() const override;
    virtual void resetState() override;
    ~ShowProcessor();
};

}


#endif
