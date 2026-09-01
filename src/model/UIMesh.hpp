#pragma once

#include "geometry/Mesh.hpp"

class UIMesh : public geometry::Mesh {
  public:
    void setFromMesh(geometry::Mesh&& mesh);

    /** For now the class is just a wrapper for Mesh class
    ** Later an abstract class for model will be created
    ** this UIMesh will inherit this abstract class
    ** the extraction, processing and defining layout of mesh vertices will be implemented
    ** outside classes like MeshRenderer will only see renderData()
    **/
};
