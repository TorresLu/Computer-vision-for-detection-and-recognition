#pragma once
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <vector>
#include <utility>

class RuneDetector {
public:
	struct Point2fWithIdx {
		cv::Point2f p;
		size_t idx;
		Point2fWithIdx(const cv::Point2f _p, size_t _idx) :p(_p), idx(_idx){}
	};

    typedef enum {RUNE_ORB, RUNE_GRAD, RUNE_CANNY} Methed_Type;

public:
    RuneDetector(int cell_width = 127, int cell_height = 71, bool perspective = false, Methed_Type m_type = RUNE_CANNY){
		sudoku_width = cell_width;
		sudoku_height = cell_height;
        use_perspective = perspective;
        type = m_type;
	}
	cv::RotatedRect getRect(int idx){
		return sudoku_rects[idx];
	}
	const cv::RotatedRect & getRect(int idx) const {
		return sudoku_rects[idx];
	}

    /**
     * @brief getTarget
     * @param image
     * @return ret.first is the index of the vector of sudoku rectangle,
     *         ret.second is the index of the obsolute position of target cell
     */
	std::pair<int, int> getTarget(const cv::Mat & image);

protected:
	std::pair<int, int> chooseTargetPerspective(const cv::Mat & image, const std::vector<cv::RotatedRect> & sudoku_rects);
    std::pair<int, int> chooseTarget(const cv::Mat & image, const std::vector<cv::RotatedRect> & sudoku_rects);

	int findTargetORB(cv::Mat * cells);
    int findTargetEdge(cv::Mat * cells);
    int findTargetCanny(cv::Mat * cells);

	cv::RotatedRect adjustRRect(const cv::RotatedRect & rect);
	bool checkSudoku(const std::vector<std::vector<cv::Point2i> > & contours,std::vector<cv::RotatedRect> & sudoku_rects);

private:
	std::vector<cv::RotatedRect> sudoku_rects;
	int sudoku_width;	 // pixel
	int sudoku_height;   // pixel
    bool use_perspective;
    Methed_Type type;
	cv::Mat src;
};
