#include "webpFormat.hh"

#include <webp/decode.h>
#include <string.h>

WEBP WEBP::decode(std::vector<unsigned char> data)
{
  WEBP out;
  std::vector<unsigned char> mData = std::move(data);
  if(mData.empty())
  {
    return out;
  }
  WebPBitstreamFeatures features;
  if(WebPGetFeatures(mData.data(), mData.size(), &features) != VP8_STATUS_OK)
  {
    return out;
  }
  out.m_width = features.width;
  out.m_height = features.height;
  out.m_channels = features.has_alpha ? 4 : 3;
  size_t decodedSize = out.m_width * out.m_height * out.m_channels;
  out.m_decodedData.resize(decodedSize);
  unsigned char *arr;
  switch(out.m_channels)
  {
    case 3:
      arr = WebPDecodeRGB(mData.data(), out.m_decodedData.size(), &out.m_width, &out.m_height);
      break;
    case 4:
      arr = WebPDecodeRGBA(mData.data(), out.m_decodedData.size(), &out.m_width, &out.m_height);
      break;
    default:
      return {};
  }
  memcpy(out.m_decodedData.data(), arr, decodedSize);
  return out;
}
