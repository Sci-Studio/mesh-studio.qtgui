#include "UIMesh.hpp"

#include <utility>

void UIMesh::setFromMesh(geometry::Mesh&& mesh) {
    static_cast<geometry::Mesh&>(*this) = std::move(mesh);
}
