#ifndef ENGINE_VERTEXBUFFER_HPP
#define ENGINE_VERTEXBUFFER_HPP

#include "vertexdataview.hpp"

#include <glad/glad.h>

#include <vector>

namespace engine {

class VertexBuffer {
   public:
    VertexBuffer(GLenum usage = GL_STATIC_DRAW);
    ~VertexBuffer();
    VertexBuffer(VertexBuffer&& from);
    VertexBuffer& operator=(VertexBuffer&& from);
    VertexBuffer(const VertexBuffer&) = delete;
    VertexBuffer& operator=(const VertexBuffer&) = delete;

    /**
     * Bind vertex buffer to current context.
     */
    void bind();

    /**
     * Load data into vertex buffer.
     */
    void loadData(const VertexDataView& vertexData);

   private:
    /**
     * Buffers the data into the corresponding buffer object. The GL buffer is
     * reallocated if the buffer size is larger than the current buffer
     * capacity, or smaller by a factor of s_shrinkFactor as a trade off between
     * reallocation overhead and memory usage.
     *
     * @param bufferType Type of buffer, e.g. GL_ARRAY_BUFFER
     * @param bufferObject Buffer object identifier
     * @param bufCapacity Current capacity of buffer. Taken in as a reference
     *     and modified if capacity changes.
     * @param data Data to be buffered.
     */
    template <typename T>
    void bufferData(GLenum bufferType, GLuint bufferObject, size_t& bufCapacity,
                    const std::vector<T>& data);

    bool d_isValid;
    GLuint d_vertexArrayObject;
    GLuint d_vertexBufferObject;
    GLuint d_elementBufferObject;
    GLenum d_usage;

    size_t d_vBufCapacity;
    size_t d_eBufCapacity;
    static constexpr size_t s_shrinkFactor = 5;
};

}  // namespace engine

#endif
