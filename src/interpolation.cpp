/**
 * @author      : Alexander Lloyd (axl639@student.bham.ac.uk)
 * @file        : interpolation
 * @created     : Thursday Jun 27, 2019 11:53:58 BST
 */

#ifndef interpolate_cpp
#define interpolate_cpp

float interpolate(const float &a, const float &b, const float &mix) {
	return b * mix + a * (1-mix);
}

#endif
