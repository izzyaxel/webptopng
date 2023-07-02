#pragma once

#include "webpFormat.hh"

#include <vector>
#include <string>

struct PNG
{
  static int constexpr COLOR_FMT_GREY = 0;
  static int constexpr COLOR_FMT_PALETTE = 2 | 1;
  static int constexpr COLOR_FMT_RGB = 2;
  static int constexpr COLOR_FMT_RGBA = 2 | 4;
  static int constexpr COLOR_FMT_GREY_ALPHA = 4;
  
  static PNG fromWEBP(WEBP webp);
  
  PNG(unsigned int width, unsigned int height, char colorFormat, std::vector<unsigned char> &&imageData);
  void writeToDisk(std::string const &filePath);
  unsigned int m_width;
  unsigned int m_height;
  char m_colorFormat;
  std::vector<unsigned char> m_imageData;
};


