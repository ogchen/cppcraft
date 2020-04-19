#include "vertexbuffer.hpp"

namespace engine {

VertexBuffer::VertexBuffer(GLenum usage)
    : d_isValid(true), d_usage(usage), d_vBufCapacity(0), d_eBufCapacity(0) {
    glGenVertexArrays(1, &d_vertexArrayObject);
    glGenBuffers(1, &d_vertexBufferObject);
    glGenBuffers(1, &d_elementBufferObject);
}

VertexBuffer::~VertexBuffer() {
    if (d_isValid) {
        glDeleteVertexArrays(1, &d_vertexArrayObject);
        glDeleteBuffers(1, &d_vertexBufferObject);
        glDeleteBuffers(1, &d_elementBufferObject);
    }
}

VertexBuffer::VertexBuffer(VertexBuffer&& from)
    : d_isValid(std::exchange(from.d_isValid, false)) {}

VertexBuffer& VertexBuffer::operator=(VertexBuffer&& from) {
    d_isValid = std::exchange(from.d_isValid, false);
    return *this;
}

void VertexBuffer::bind() { glBindVertexArray(d_vertexArrayObject); }

void VertexBuffer::loadData(const VertexDataView& vertexData) {
    glBindVertexArray(d_vertexArrayObject);

    bufferData<float>(GL_ARRAY_BUFFER, d_vertexBufferObject, d_vBufCapacity,
                      vertexData.data);
    bufferData<unsigned>(GL_ELEMENT_ARRAY_BUFFER, d_elementBufferObject,
                         d_eBufCapacity, vertexData.indices);

    const VertexDataView::VertexLayout& layout = vertexData.layout;
    for (size_t i = 0; i != layout.size(); ++i) {
        glVertexAttribPointer(i, layout[i], GL_FLOAT, GL_FALSE,
                              vertexData.stride * sizeof(float),
                              (void*)(vertexData.position[i] * sizeof(float)));
        glEnableVertexAttribArray(i);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

template <typename T>
void VertexBuffer::bufferData(GLenum bufferType, GLuint bufferObject,
                              size_t& bufCapacity, const std::vector<T>& data) {
    glBindBuffer(bufferType, bufferObject);
    const size_t bufSize = data.size() * sizeof(T);
    if (bufSize > bufCapacity || bufSize < bufCapacity / s_shrinkFactor) {
        glBufferData(bufferType, bufSize, data.data(), d_usage);
        bufCapacity = bufSize;
    } else {
        glBufferSubData(bufferType, 0, bufSize, data.data());
    }
}

}  // namespace engine
