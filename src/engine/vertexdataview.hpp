#ifndef ENGINE_VERTEXDATAVIEW_HPP
#define ENGINE_VERTEXDATAVIEW_HPP

#include <string>
#include <vector>

namespace engine {

/**
 * View class for data buffers to be loaded into GL buffer.
 */
class VertexDataView {
   public:
    using VertexLayout = std::vector<size_t>;

    /**
     * VertexDataView constructor. Throws a runtime_error if inputs are not
     * logically consistent.
     *
     * @param vertexLayout Description of the data layout. This is specified as
     *     a vector of pairs, each pair containing the name of the vertex
     *     property and the number of floats to represent it. For instance, the
     *     layout {3, 4} describes each vertex as containing 2 attributes of 3
     *     floats and 4 floats respectively.
     * @param vertexData Tightly packed vertex data.
     * @param ind Index buffer
     */
    VertexDataView(const VertexLayout& vertexLayout,
                   std::vector<float>& vertexData, std::vector<unsigned>& ind);

    VertexLayout layout;
    /*
     * Describes the relative position of an attribute. If layout is {3, 4, 2},
     * position would be {0, 3, 7}
     */
    VertexLayout position;
    size_t stride;
    std::vector<float>& data;
    std::vector<unsigned>& indices;

   private:
    /**
     * Validate the vertex layout, data and indices array are logically
     * consistent.
     *
     * @param errorMessage Description of error if one exists.
     * @return bool Valid or not.
     */
    bool validate(std::string& errorMessage);
};

}  // namespace engine

#endif
