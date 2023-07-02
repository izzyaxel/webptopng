#pragma once

#include <vector>

struct WEBP
{
  static WEBP decode(std::vector<unsigned char> data);
  
  int m_width = 0;
  int m_height = 0;
  char m_channels = 0;
  std::vector<unsigned char> m_decodedData{};
};
