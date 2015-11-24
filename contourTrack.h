#ifndef _CONTOUR_TRACK_H_
#define _CONTOUR_TRACK_H_

// sys
#include <string>
#include <vector>
// tools
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
// project
#include "segMisc.h"
#include "vectorSpace.h"
#include "CompressiveTracker.h"

// namespace
using :: std :: string;
using :: std :: vector;
using namespace Vector_Space;
using namespace Compressive_Tracker;

namespace Seg_Three
{
    
class ContourTrack
{    
public:
    ContourTrack(const int idx, const cv::Mat & in,
                 const int width, const int height, // image width/height
                 const int directionIn,        
                 const int lux, const int luy, // first appear coordinate
                 const int possibleWidth, const int possibleHeight);
    ~ContourTrack();
    // 1. important ones
    int processFrame(const cv::Mat & in, const cv::Mat & bgResult,
                     const cv::Mat & diffAnd, const cv::Mat & diffOr);
    int flushFrame();
    
    // 2. trival ones
    int getIdx() const {return m_idx;}
    int isAllIn() const {return m_bAllIn;}    
    cv::Rect & getCurBox() {return m_curBox;}
    cv::Rect & getLastBox() {return m_lastBox;}    
    bool canOutputRegion() {return m_bOutputRegion;}
    DIRECTION getInDirection(){return m_inDirection;}
    
private:
    const int m_idx;
    int m_imgWidth;
    int m_imgHeight;
    int m_inputFrames;
    
    bool m_bAllIn; // some objects may not always in.
    bool m_bAllOut;
    bool m_bOutputRegion;
    
    // 1. using CompressiveTrack as tracker
    cv::Rect m_lastBox;
    cv::Rect m_curBox; // changing every time with diffResults' influence
    CompressiveTracker m_ctTracker;    
    int m_largestWidth;
    int m_largestHeight;
    
    DIRECTION m_inDirection;
    DIRECTION m_outDirection;

    // 4. size changing function
    double m_aw; 
    double m_bw;
    double m_ah; 
    double m_bh;
    const static int m_c = -1; // y = ax^2 + bx + c

private: // inner helpers
    int updateTrackerUsingDiff(const cv::Mat & in, const cv::Mat & bgResult,
                               const cv::Mat & diffAnd, const cv::Mat & diffOr);
    int doShrinkBoxUsingImage(const cv::Mat & image, cv::Rect & box);
    // trival ones
    int curMaxChangeSize(int & x, int & y);
    double calcOverlapRate(cv::Rect & a, cv::Rect & b);
    cv::Rect calcOverlapArea(cv::Rect & a, cv::Rect & b);
    void boundBoxByMinBox(cv::Rect & maxBox, const cv::Rect & minBox);
};

}//namespace

#endif // _CONTOUR_TRACK_H_
