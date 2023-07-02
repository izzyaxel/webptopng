#include "pngFormat.hh"

#include <png.h>

PNG::PNG(unsigned int width, unsigned int height, char colorFormat, std::vector<unsigned char> &&imageData) :
  m_width(width), m_height(height), m_colorFormat(colorFormat), m_imageData(std::move(imageData))
{}

void PNG::writeToDisk(std::string const &filePath)
{
  unsigned char **data = new unsigned char *[this->m_height];
  int cpp = 0;
  switch(this->m_colorFormat)
  {
    case PNG::COLOR_FMT_GREY:
      cpp = 1;
      break;
    case PNG::COLOR_FMT_RGB:
      cpp = 3;
      break;
    case PNG::COLOR_FMT_RGBA:
      cpp = 4;
      break;
    default:
      break;
  }
  for(size_t i = 0; i < this->m_height; i++)
  {
    data[i] = this->m_imageData.data() + i * this->m_width * cpp;
  }
  FILE *output = fopen(filePath.data(), "wb");
  if(!output)
  {
    return;
  }
  png_structp pngPtr;
  png_infop infoPtr;
  pngPtr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
  if(!pngPtr)
  {
    fclose(output);
    return;
  }
  infoPtr = png_create_info_struct(pngPtr);
  if(!infoPtr)
  {
    fclose(output);
    return;
  }
  if(setjmp((png_jmpbuf(pngPtr))))
  {
    fclose(output);
    return;
  }
  png_init_io(pngPtr, output);
  if(setjmp(png_jmpbuf(pngPtr)))
  {
    fclose(output);
    return;
  }
  png_set_IHDR(pngPtr,
    infoPtr,
    this->m_width,
    this->m_height,
    8,
    this->m_colorFormat,
    PNG_INTERLACE_NONE,
    PNG_COMPRESSION_TYPE_BASE,
    PNG_FILTER_TYPE_BASE);
  png_write_info(pngPtr, infoPtr);
  if(setjmp(png_jmpbuf(pngPtr)))
  {
    fclose(output);
    return;
  }
  png_write_image(pngPtr, data);
  if(setjmp(png_jmpbuf(pngPtr)))
  {
    fclose(output);
    return;
  }
  png_write_end(pngPtr, nullptr);
  fclose(output);
  delete[] data;
}

PNG PNG::fromWEBP(WEBP webp)
{
  int colorFormat;
  if(webp.m_channels == 3) colorFormat = PNG::COLOR_FMT_RGB;
  else if(webp.m_channels == 4) colorFormat = PNG::COLOR_FMT_RGBA;
  return {(unsigned int)webp.m_width, (unsigned int)webp.m_height, (char)colorFormat, std::move(webp.m_decodedData)};
}
