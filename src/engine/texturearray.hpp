#ifndef ENGINE_TEXTUREARRAY_HPP
#define ENGINE_TEXTUREARRAY_HPP

#include <glad/glad.h>

#include <string>
#include <vector>

namespace engine {

class ImageData {
   public:
    /**
     * Load image data from file. Throws a runtime_error on failure.
     */
    explicit ImageData(const std::string& filePath);
    ~ImageData();
    ImageData(ImageData&& imageData) noexcept;
    ImageData& operator=(ImageData&& imageData);
    ImageData(const ImageData&) = delete;
    ImageData& operator=(const ImageData&) = delete;

    int width;
    int height;
    int numChannels;
    unsigned char* rawData;
};

class TextureArray {
   public:
    /**
     * Construct a texture array object from a list of texture files. A
     * runtime_error is thrown if any texture file does not match the
     * width/height parameters, or if a texture file fails to load.
     *
     * @param relPaths Vector of paths to textures relative to
     * <PROJECT_SOURCE>/data/texture
     * @param width Width of texture
     * @param height Height of texture
     */
    TextureArray(const std::vector<std::string>& relPaths, size_t width,
                 size_t height);

   private:
    GLuint d_textureArrayObject;
};

/**
 * Loads each file specified in relPaths into a vector of image data. Verifies
 * that each image has the expected dimensions width * height. A runtime_error
 * is thrown if the dimensions are not matched, or the image data fails to load.
 *
 * @param relPaths Vector of paths relative to <PROJECT_SOURCE>/data/texture.
 * @param width Expected width of image.
 * @param height Expected height of image.
 * @return Vector of image data.
 */
std::vector<ImageData> generateImageDataVec(
    const std::vector<std::string>& relPaths, size_t width, size_t height);

}  // namespace engine

#endif
