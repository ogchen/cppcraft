#include <gtest/gtest.h>

#include <stdexcept>

#include "vertexdataview.hpp"

namespace engine {
namespace {

TEST(VertexDataView, CorrectPositionAndStride) {
    std::vector<float> data;
    std::vector<unsigned> indices;
    VertexDataView::VertexLayout layout = {3, 4, 2};
    VertexDataView view(layout, data, indices);
    VertexDataView::VertexLayout expectedPosition = {0, 3, 7};

    EXPECT_EQ(view.position, expectedPosition);
    EXPECT_EQ(view.stride, 9);
}

TEST(VertexDataView, ErrorOnInvalidVertexAttributeSize) {
    std::vector<float> data;
    std::vector<unsigned> indices;
    VertexDataView::VertexLayout layoutA = {5};
    VertexDataView::VertexLayout layoutB = {0};

    EXPECT_THROW(VertexDataView view(layoutA, data, indices),
                 std::runtime_error);
    EXPECT_THROW(VertexDataView view(layoutB, data, indices),
                 std::runtime_error);
}

TEST(VertexDataView, ErrorOnOutOfBoundIndex) {
    std::vector<float> data = {0, 0, 0};
    std::vector<unsigned> indicesA = {0, 2, 1};
    std::vector<unsigned> indicesB = {0, 3, 1};
    VertexDataView::VertexLayout layout = {1};

    EXPECT_NO_THROW(VertexDataView view(layout, data, indicesA));
    EXPECT_THROW(VertexDataView view(layout, data, indicesB),
                 std::runtime_error);
}

}  // namespace
}  // namespace engine
