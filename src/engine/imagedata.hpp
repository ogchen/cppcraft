#ifndef ENGINE_IMAGEDATA_HPP
#define ENGINE_IMAGEDATA_HPP

#include <string>
#include <vector>

namespace engine {

class ImageData {
   public:
    /**
     * Load image data from file. Throws a runtime_error on failure.
     */
    explicit ImageData(const std::string& filePath);
    ImageData(int wd, int ht, int nc, unsigned char* data);
    ~ImageData();
    ImageData(ImageData&& imageData) noexcept;
    ImageData& operator=(ImageData&& imageData);
    ImageData(const ImageData&) = delete;
    ImageData& operator=(const ImageData&) = delete;

    int width;
    int height;
    int numChannels;
    unsigned char* rawData;

   private:
    bool isValid;
};

/**
 * Loads each file specified in filePaths into a vector of image data.
 *
 * @param filePaths Vector of paths to textures.
 * @return Vector of image data.
 */
std::vector<ImageData> generateImageDataVec(
    const std::vector<std::string>& filePaths);

/**
 * Verifies every ImageData object in imageDataVec has the dimensions width *
 * height with four channels.
 */
bool validateImageDataVec(const std::vector<ImageData>& imageDataVec,
                          size_t width, size_t height);

}  // namespace engine

#endif
