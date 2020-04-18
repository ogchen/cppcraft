#include "vertexdataview.hpp"

#include <algorithm>
#include <functional>
#include <iterator>
#include <numeric>
#include <stdexcept>

namespace engine {

VertexDataView::VertexDataView(const VertexLayout& vertexLayout,
                               std::vector<float>& vertexData,
                               std::vector<unsigned>& ind)
    : layout(vertexLayout), data(vertexData), indices(ind) {
    position.reserve(layout.size() + 1);
    position.push_back(0);
    std::partial_sum(layout.begin(), layout.end(),
                     std::back_inserter(position));
    position.pop_back();
    stride = std::accumulate(layout.begin(), layout.end(), 0);

    std::string errorMessage = "";
    if (!validate(errorMessage)) {
        throw std::runtime_error(errorMessage);
    }
}

bool VertexDataView::validate(std::string& errorMessage) {
    if (std::any_of(layout.begin(), layout.end(),
                    [](size_t i) { return i > 4 || i == 0; })) {
        errorMessage = "Invalid vertex attribute size provided";
        return false;
    };

    const size_t maxVertNum = data.size() / stride;
    if (std::any_of(indices.begin(), indices.end(),
                    [maxVertNum](size_t i) { return i >= maxVertNum; })) {
        errorMessage = "Vertex index in indices array is out of bounds.";
        return false;
    }

    return true;
}

}  // namespace engine
