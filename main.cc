#include "pngFormat.hh"
#include "webpFormat.hh"
#include "stringTools.hh"

struct PathPair
{
  std::string webpPath;
  std::string pngPath;
};

std::vector<unsigned char> getRawFile(std::string const &path)
{
  FILE *in = fopen(path.c_str(), "rb");
  if(!in) return {};
  fseek(in, 0, SEEK_END);
  size_t len = ftell(in);
  rewind(in);
  std::vector<unsigned char> out;
  out.resize(len);
  fread(out.data(), len, 1, in);
  fclose(in);
  return out;
}

/// Converts an RGB or RGBA .webp image to .png
int main(int argc, char **argv)
{
  //Parse the pathes of all files dropped onto the EXE
  if(argc < 2) return 1; //First argument is always the program's name, the rest are user arguments
  std::vector<PathPair> pathPairs;
  for(int i = 1; i < argc; i++)
  {
    std::string webpPath = std::string{argv[i]}; //Get the next WEBP file path
    if(!endsWith(webpPath, ".webp")) continue; //Skip this file if it's not WEBP
    webpPath = replaceAll(webpPath, '\\', '/'); //Sanitize to a common slash format
    std::string pngFilePath = subString(webpPath, 0, webpPath.length() - webpPath.find_last_of('.')) + ".png";
    pathPairs.emplace_back(webpPath, pngFilePath);
  }
  
  //Read, decode and convert the WEBP files to PNGs, and write them to disk
  for(auto const &pathPair : pathPairs)
  {
    std::vector<unsigned char> webpData = getRawFile(pathPair.webpPath);
    if(webpData.empty()) continue; //Skip this file if it couldn't be read
    WEBP webpImg = WEBP::decode(webpData);
    PNG pngImg = PNG::fromWEBP(webpImg);
    pngImg.writeToDisk(pathPair.pngPath);
  }
  return 0;
}
